#ifndef _MY_STATIC_LIST_HPP
#define _MY_STATIC_LIST_HPP
#include "assert.h"
#include "vector.hpp"
#include "iterator_traits.h"

namespace MyUtil
{
  template <class T>
  class staticList
  {
    template <class U>
    struct Node
    {
      T _data;
      int nextIdx;
    };

    vector< Node<T> > _impl;
    unsigned int maxSize;
    unsigned int freeIdx;
    unsigned int headIdx;
    Node<T> *base;

  public:
    explicit staticList(unsigned int max):_impl(max)
    {
      base = &_impl[0];
      freeIdx = 0;
      maxSize = max;
    }

    template <class V>
    class static_iterator
    {
      Node<V> * base;
      unsigned int cur;
    public:
      typedef forward_iter_tag iter_tag;

      static_iterator(Node<V> *p, unsigned int idx):base(p), cur(idx){}
      static_iterator(const static_iterator &rhs):base(rhs.base), cur(rhs.cur){}
      
      V & operator*() const
      {
	return base[cur]._data;
      }
      
      V * operator->() const
      {
	return &base[cur]._data;
      }

      static_iterator & operator++()
      {
	cur = base[cur].nextIdx;
	return *this;
      }
      
      const static_iterator operator++(int)
      {
	static_iterator tmp(*this);
	++*this;
	return tmp;
      }



    };

    typedef static_iterator<T> iterator;

  }




}
#endif
