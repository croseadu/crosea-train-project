#ifndef _CIRCULAR_QUEUE_H_
#define _CIRCULAR_QUEUE_H_

#include "array.h"
#include <assert.h>

namespace MyUtil
{
template <typename T, unsigned int N>  
class CircularQueue
{
  Array<T, N+1> queue_;
  unsigned int head;
  unsigned int tail;
  
  bool full() const { return (tail+1) % (N+1) == head; }

public:
  CircularQueue():head(0), tail(0){}
  ~CircularQueue(){}
  
  void push(const T & in)
  {
    assert (!full());
    queue_[tail] = in;
    tail++;
    tail = tail % (N+1);
  }

  void pop(T &in)
  {
    assert (!empty());
    in = queue_[head];
    head++;
    head = head % (N+1);
  }

  bool empty() const
  {
    return head == tail;
  }

  unsigned int size() const { return (tail + N + 1 - head ) % (N+1); }

};





}




#endif
