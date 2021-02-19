#pragma once

#include "queue.h"

namespace BGPSim {

template <class T>
Queue<T>::Queue(uint32_t maxSize) {
  init_ = new T[maxSize]();
  Reset();
}

template <class T>
Queue<T>::~Queue() {
  delete[] init_;
}

template <class T>
T *Queue<T>::Append(T asn) {
  *++end_ = asn;
  return end_;
}

template <class T>
T *Queue<T>::Pop() {
  return ++q_ - 1;
}

template <class T>
void Queue<T>::Drop() {
  ++q_;
}

template <class T>
T *Queue<T>::GetLast() {
  return end_;
}

template <class T>
T *Queue<T>::GetCurrent() {
  return q_;
}

template <class T>
bool Queue<T>::IsEmpty() {
  return q_ > end_;
}

template <class T>
void Queue<T>::Reset() {
  q_ = init_;
  end_ = init_ - 1;
}

}  // namespace BGPSim
