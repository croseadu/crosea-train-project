#ifndef _MY_STACK_HPP
#define _MY_STACK_HPP
#include "assert.h"
#include "list.hpp"
#include "vector.hpp"

namespace MyUtil
{

  template <class T, 
	    template <class U>
            class Storage = doubleList >
  class stack
  {
    Storage<T> _impl;
  public:
    stack(){};
    stack(const stack &rhs){}


    const T & top () const
    {
      return _impl.back();
    }
    void pop ()
    {
      _impl.pop_back();
    }
    
    void push(T value)
    {
      _impl.push_back(value);
    }
    bool empty() const
    {
      return _impl.empty();
    }
    unsigned int size() const
    {
      return _impl.size();
    }
    
  };









}
#endif
