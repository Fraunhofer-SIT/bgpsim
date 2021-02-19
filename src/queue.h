#pragma once

namespace BGPSim {
template <class T>
class Queue;
}

#include "graph.h"

namespace BGPSim {
template <class T>
class Queue {
 public:
  explicit Queue(uint32_t maxSize);
  ~Queue();
  T *Append(T asn);
  T *Pop();
  void Drop();
  T *GetLast();
  T *GetCurrent();
  bool IsEmpty();
  void Reset();

 private:
  T *init_;
  T *q_;
  T *end_;
};
}  // namespace BGPSim

#include "queue_impl.h"
