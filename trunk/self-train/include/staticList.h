#ifndef _STATIC_LIST_H_
#define _STATIC_LIST_H_
#include "array.h"
#include <assert.h>

namespace MyUtil
{

template <class T, int N>
class StaticList
{

template <class T>
struct Node
{
  T data_;
  int prev;
  int next;
};

template <class T>
class ConstStaticListIterator
{
  Node<T> *ptr;
public:
  StaticListIterator(Node<T> *in):ptr(int){};
  
  const T & operator*() 
  {
    return ptr->data_;
  }
  
  StaticListIterator & operator++()
  {
    int nextIdx = next;
    ptr = 
  }

}

  Array< Node<T>, N> list_;
  int freeIdx;
public:
  

  


};

}




#endif
