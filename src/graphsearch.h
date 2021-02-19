#pragma once

#include "graph.h"
#include "queue.h"

namespace BGPSim {
class GraphSearch {
 public:
  explicit GraphSearch(Graph *graph);
  ~GraphSearch();
  ASNPath GetPath(ASN source, ASN target);
  ASNPath GetPathExcluding(ASNVec excluding, ASN source, ASN target);
  void SetMaxDepth(uint8_t depth);

 private:
  struct NodeData {
    ASN asn;
    uint8_t had_peer;
    uint8_t depth;
    NodeData *previous;
  };
  struct SearchData {
    Queue<NodeData> *queue;
    NodeData **visitedProviders;
    NodeData **visitedPeers;
    NodeData *segment;
    uint8_t depth;
    uint8_t id;
  };
  void InitSearchData(SearchData **data);
  void Setup();
  void SetupSearchData(SearchData **data, uint8_t id);
  void DeleteSearchData(SearchData **data);
  uint32_t arraySize_;
  size_t queueSize_;
  uint8_t max_depth_ = 40;
  Graph *g_;
  SearchData *curr_;
  SearchData *next_;
  uint8_t *excluding_;
};
}  // namespace BGPSim
