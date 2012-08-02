#ifndef _STACK_H_
#define _STACK_H_
#include "list.h"
#include "array.h"


namespace MyUtil
{

template <class T>
class Stack
{
private:
  List<T> storage_;
public:
  Stack(){}
  ~Stack(){}
  void pop(T &out)
  {
    assert (!empty());
    out = *storage_.begin();
    storage_.erase(storage_.begin());
  }
  void push(const T & in)
  {
    storage_.push_before(in);
  }
  bool empty() 
  {
    return !(storage_.begin() != storage_.end());
  }
  const T getTop() const
  {
    assert (!empty());
    T result = *storage_.begin();
    return result;
  }
  
};

}
#endif
