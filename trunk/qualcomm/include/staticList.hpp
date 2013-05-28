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
    int freeIdx;
    int headIdx;
    Node<T> *base;

  public:
    explicit staticList(unsigned int max):_impl(max)
    {
      base = &_impl[0];
      freeIdx = 0;
      maxSize = max;
      headIdx = -1;

      for (unsigned i = 0; i < max -1; i++)
	_impl[i].nextIdx = i+1;
      _impl[i].nextIdx = -1;
    }

    template <class V>
    class static_iterator
    {
      Node<V> * base;
      unsigned int cur;
      friend class staticList;

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

    iterator begin ()
    {
      return iterator(base, headIdx);
    }


    iterator end()
    {
      return iterator(base, -1);
    }

    iterator insert(iterator insertPt, T value)
    {
      assert (freeIdx != -1);
      int newIdx = freeIdx;
      freeIdx = _impl[freeIdx].nextIdx;
      _impl[newIdx]._data = value;
      _impl[newIdx].nextIdx = _impl[insertPt.cur].nextIdx;
      _impl[insertPt.cur].nextIdx = newIdx;
      return iterator(base, newIdx);
    }

    iterator push_front(T value)
    {
      assert (freeIdx != -1);
      int newIdx = freeIdx;
      freeIdx = _impl[freeIdx].nextIdx;

      _impl[newIdx]._data = value;
      _impl[newIdx].nextIdx = headIdx;
      headIdx = newIdx;
      return iterator(base, newIdx);
    }

    iterator push_back(T value)
    {
      assert (freeIdx != -1);
      int newIdx = freeIdx;
      freeIdx = _impl[freeIdx].nextIdx;

      _impl[newIdx]._data = value;
      _impl[newIdx].nextIdx = -1;
      
      int insertPtIdx = headIdx;
      if (headIdx == -1)
	headIdx = newIdx;
      else
	{
	  while (insertPtIdx)
	}

      return iterator(base, newIdx);

  }




}
#endif
