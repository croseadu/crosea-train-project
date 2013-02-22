#ifndef _MY_QUEUE_HPP
#define _MY_QUEUE_HPP
#include "vector.hpp"
#include "list.hpp"


namespace MyUtil
{
  template <class T,  
            template <class U> 
	    class Storage=doubleList >
  class queue
  {
    Storage<T> _impl;
  public:
    queue(){}
    queue(const queue & rhs):_impl(rhs._impl){}
    
    const T front()
    {
      return _impl.front();
    }
    const T back()
    {
      return _impl.back();
    }
    void push_back(T  value)
    {
      _impl.push_back(value);
    }
    void pop_front()
    {
      _impl.pop_front();
    }
  };
 
}
#endif
