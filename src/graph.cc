/*
 This is an open source non-commercial project. Dear PVS-Studio, please check
 it. PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
 http://www.viva64.com
*/

#include "graph.h"
#include <algorithm>
#include "queue.h"

namespace BGPSim {

AS Graph::operator[](const int index) { return nodes_[index]; }

void Graph::AddProviderToCustomerRelation(ASN provider, ASN customer) {
  if (!IsExcluded(provider) && !IsExcluded(customer)) {
    CreateNode(provider);
    CreateNode(customer);
    nodes_[provider].customers.push_back(customer);
    nodes_[customer].providers.push_back(provider);
    num_edges_ += 1;
  }
}

void Graph::AddPeerToPeerRelation(ASN peer1, ASN peer2) {
  if (!IsExcluded(peer1) && !IsExcluded(peer2)) {
    CreateNode(peer1);
    CreateNode(peer2);
    nodes_[peer1].peers.push_back(peer2);
    nodes_[peer2].peers.push_back(peer1);
    num_edges_ += 1;
  }
}

void Graph::CreateNode(ASN node) {
  AS as;

  if (nodes_.find(node) != nodes_.end()) {
    return;
  }

  asns_.push_back(node);

  as.number = node;
  as.rir = RIR::UNASSIGNED;

  rirs_[as.rir] += 1;
  nodes_[node] = as;

  if (node > max_asn_) {
    max_asn_ = node;
  }
}

void Graph::PrintStats() {
  printf(">> Graph stats:\n");
  printf(">>         # of nodes: %zu\n", nodes_.size());
  printf(">>         # of edges: %u\n", num_edges_);
  printf(">>            max ASN: %u\n>>\n", max_asn_);
  printf(">>\n");
}

void Graph::PrintNodes() {
  printf(">> Nodes:\n");
  for (auto &node : nodes_) {
    printf(">> Node: %u\n", node.second.number);
  }
  printf(">>\n");
}

std::size_t Graph::GetNumNodes() { return nodes_.size(); }

ASN Graph::GetMaxASN() { return max_asn_; }

ASNVec Graph::GetAllASNs() { return asns_; }

ASNVec Graph::GetAllNodeWithCustomers(uint32_t min, uint32_t max) {
  ASNVec asns;
  
  for (auto const& it : nodes_) {
    AS const& as = it.second;
    size_t customers = as.customers.size();
    if (customers > min && customers < max) {
      asns.push_back(as.number);
    }
  }

  return asns;
}

bool Graph::HasNode(ASN node) { return nodes_.count(node) > 0; }

void Graph::ExcludeNodes(ASNVec exclude) { exclude_ = exclude; }

bool Graph::IsExcluded(ASN node) {
  return std::find(exclude_.begin(), exclude_.end(), node) != exclude_.end();
}
}  // namespace BGPSim
