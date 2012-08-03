#ifndef _STATIC_LIST_H_
#define _STATIC_LIST_H_
#include "array.h"
#include <assert.h>

namespace MyUtil
{

  static const int END_OF_LIST = -1;
  template <class U>
  class Node
  {
  public:
    U data_;
    int prev;
    int next;
  };


  template <class U>
  class ConstStaticListIterator
  {
  public:
    Node<U> *ptr;
    int idx;
  public:
    ConstStaticListIterator(Node<U> *in, int index):ptr(in), idx(index){};
  
    const U & operator*() const 
    {
      return ptr[idx].data_;
    }
  
    const U * operator->() const
    {
      return &**this;
    }
    ConstStaticListIterator & operator++()
    {
      idx = ptr[idx].next;
    }

    ConstStaticListIterator  operator++(int)
    {
      ConstStaticListIterator i(ptr, idx);
      idx = ptr[idx].next;
      return i;
    }

    ConstStaticListIterator & operator--()
    {
      idx = ptr[idx].prev;
    }
    int getNodeIdx() const
    {
      return idx;
    }
  };

  template <class U>
  class StaticListIterator: public ConstStaticListIterator<U>
  {
  public:
    StaticListIterator(Node<U> *in, int index):ConstStaticListIterator<U>(in, index){}

    U & operator * ()
    {
      return (this->ptr)[this->idx].data_;
    }
    U * operator->()
    {
      return &**this;
    }
  };

template <class T>
bool operator!=(ConstStaticListIterator<T> lhs, ConstStaticListIterator<T> rhs)
{
  return lhs.getNodeIdx() != rhs.getNodeIdx();
}
template <class T>
bool operator==(ConstStaticListIterator<T> lhs, ConstStaticListIterator<T> rhs)
{
  return !(lhs != rhs);
}


template <class T, int N>
class StaticList
{
public:

  typedef ConstStaticListIterator<T> const_iterator;
  typedef StaticListIterator<T> iterator;

private:
  Array< Node<T>, N> list_;
  int freeIdx;
  int size_;
public:
  StaticList()
  {
    init();
  }
  iterator insert(const_iterator pos, const T & in)
  {
    int newNodeIdx = getFreeNode();
    int insertIdx = pos.getNodeIdx();
    list_[newNodeIdx].data_ = in;
    list_[newNodeIdx].next = insertIdx;
    list_[newNodeIdx].prev = list_[insertIdx].prev;
    list_[list_[insertIdx].prev].next = newNodeIdx;
    list_[insertIdx].prev = newNodeIdx;
    size_++;
    return iterator(&list_[0], newNodeIdx);
  }

  bool push_back(const T & in)
  {
    insert(end(), in);
    return true;
  }
  
  bool push_before(const T & in)
  {
    insert(begin(), in);
    return true;
  }
  iterator begin()
  {
    return iterator(&list_[0], list_[0].next);
  }

  iterator end()
  {
    return iterator(&list_[0], 0);
  }
  
  void clear()
  {
    init();
  }

  iterator find(const T & in)
  {
    iterator RI = begin();
    for (; RI != end(); ++RI)
      if (*RI == in)
        break;
    return RI;
  }


  void erase(iterator RI)
  {
    int idx = RI.getNodeIdx();
    list_[list_[idx].prev].next = list_[idx].next;
    list_[list_[idx].next].prev = list_[idx].prev;
    
    list_[idx].next = freeIdx;
    freeIdx = idx;
    size_--;
  }

  unsigned int size() const { return size_; }
  
  void sort();

  
private:

  int getFreeNode()
  {
    int allocIdx;
    assert (freeIdx != END_OF_LIST);
    allocIdx = freeIdx;
    freeIdx = list_[freeIdx].next;
    return allocIdx;
  }

  void init()
  {
    list_[0].next = list_[0].prev = 0;
    for (int i = 1; i < N-1; i++)
    {
      list_[i].next = i+1;
    }
    list_[N-1].next = END_OF_LIST;
    size_ = 0;
    freeIdx = 1;
  }

};




}




#endif
