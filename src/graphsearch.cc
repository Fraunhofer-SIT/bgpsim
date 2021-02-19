/*
 This is an open source non-commercial project. Dear PVS-Studio, please check
 it. PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
 http://www.viva64.com
*/

#include "graphsearch.h"
#include <algorithm>
#include <cstring>
#include <utility>

namespace BGPSim {

GraphSearch::GraphSearch(Graph *graph) {
  g_ = graph;
  arraySize_ = graph->GetMaxASN() + 1;
  queueSize_ = graph->GetNumNodes() + 1;
  excluding_ = new uint8_t[arraySize_];
  InitSearchData(&curr_);
  InitSearchData(&next_);
}

GraphSearch::~GraphSearch() { delete excluding_; }

void GraphSearch::InitSearchData(SearchData **data) {
  (*data) = new SearchData();
  (*data)->queue = new Queue<NodeData>(queueSize_);
  (*data)->visitedProviders = new NodeData *[arraySize_];
  (*data)->visitedPeers = new NodeData *[arraySize_];
}

void GraphSearch::Setup() {
  memset(excluding_, 0, arraySize_);
  SetupSearchData(&curr_, 1);
  SetupSearchData(&next_, 2);
}

void GraphSearch::SetupSearchData(SearchData **data, uint8_t id) {
  memset((*data)->visitedProviders, 0, arraySize_ * sizeof(NodeData *));
  memset((*data)->visitedPeers, 0, arraySize_ * sizeof(NodeData *));
  (*data)->queue->Reset();
  (*data)->segment = NULL;
  (*data)->depth = 0;
  (*data)->id = id;
}

void GraphSearch::DeleteSearchData(SearchData **data) {
  delete (*data)->queue;
  delete[](*data)->visitedProviders;
  delete[](*data)->visitedPeers;
  delete (*data);
}

ASNPath GraphSearch::GetPath(ASN source, ASN target) {
  static ASNVec empty;
  return GetPathExcluding(empty, source, target);
}

ASNPath GraphSearch::GetPathExcluding(ASNVec _excluding, ASN source,
                                      ASN target) {
  ASNPath path;
  uint16_t totalLength = 0xffff;
  uint8_t passes = 2;

  if (!g_->HasNode(source) || !g_->HasNode(target)) {
    return path;
  }

  if (source == target) {
    path.push_back(source);
    return path;
  }

  Setup();

  for (auto as : _excluding) {
    if (as <= arraySize_ - 1) {  // arraySize = max_asn + 1
      excluding_[as] = true;
    }
  }

  if ((excluding_[source]) || (excluding_[target])) {
    printf("%s: hit excluding source or target\n", __func__);
    return path;
  }

  curr_->visitedProviders[source] = curr_->queue->Append({source, 0, 0, NULL});
  next_->visitedProviders[target] = next_->queue->Append({target, 0, 0, NULL});

  while (1) {
    NodeData *node = curr_->queue->GetCurrent();

    if (curr_->queue->IsEmpty() || node->depth > curr_->depth) {
      if (curr_->segment) {
        if (passes == 0) {
          if (curr_->id == 1) {
            std::swap(curr_, next_);
          }
          while ((curr_->segment = curr_->segment->previous)) {
            path.insert(path.begin(), curr_->segment->asn);
          }
          do {
            path.push_back(next_->segment->asn);
            next_->segment = next_->segment->previous;
          } while (next_->segment);

          return path;
        }

        passes--;

      } else if (curr_->queue->IsEmpty() && next_->queue->IsEmpty()) {
        break;
      }
      std::swap(curr_, next_);
      next_->depth = node->depth;

      continue;
    } else {
      curr_->queue->Drop();
    }

    if (node->depth > max_depth_) {
      return path;
    }

    NodeData *found = next_->visitedProviders[node->asn];
    if (found && !(node->had_peer && found->had_peer)) {
      uint16_t length = node->depth + found->depth;

      if (length < totalLength) {
        totalLength = length;
        curr_->segment = found;
        next_->segment = node;
      }
    }

    found = next_->visitedPeers[node->asn];
    if (found && !(node->had_peer && found->had_peer)) {
      uint16_t length = node->depth + found->depth;

      if (length < totalLength) {
        totalLength = length;
        curr_->segment = found;
        next_->segment = node;
      }
    }

    if (node->had_peer == 0) {
      for (auto &p : (*g_)[node->asn].providers) {
        if (curr_->visitedProviders[p] || excluding_[p]) continue;

        curr_->visitedProviders[p] = curr_->queue->Append(
            {p, 0, static_cast<uint8_t>(node->depth + 1), node});
      }

      for (auto &p : (*g_)[node->asn].peers) {
        if (curr_->visitedPeers[p] || excluding_[p]) continue;

        curr_->visitedPeers[p] = curr_->queue->Append(
            {p, 1, static_cast<uint8_t>(node->depth + 1), node});
      }
    }
  }

  return path;
}

void GraphSearch::SetMaxDepth(uint8_t depth) { max_depth_ = depth; }
}  // namespace BGPSim
