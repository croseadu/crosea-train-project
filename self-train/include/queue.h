#ifndef _QUEUE_H_
#define _QUEUE_H_
#include "list.h"
#include <assert.h>

namespace MyUtil
{

template <typename T>
class Queue
{
  List<T> queue_;

public:
  Queue(){}
  ~Queue(){}
  
  void push(const T & in)
  {
    queue_.push_back(in);
  }
  void pop(T &in)
  {
    in = *queue_.begin();
    queue_.erase(queue_.begin());
  }
  bool empty() const
  {
    return queue_.size() == 0;
  }
  unsigned int size() const { return queue_.size(); }
};



}


#endif
