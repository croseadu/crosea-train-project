#ifndef _LIST_H
#define _LIST_H
#include <assert.h>

namespace MyUtil
{

template<class T>
class ListNode
{
  T* pNext;
  T* pPrev;

public:
 ListNode():pNext(0), pPrev(0){}
  ~ListNode(){}
  const T* getNext() const
  {
    return pNext;
  }
  const T* getPrev() const
  {
    return pPrev;
  }
  
  T* getNext() 
  {
    return pNext;
  }
  T* getPrev() 
  {
    return pPrev;
  }

  void setNext(T * next){ pNext = next; }
  void setPrev(T * prev){ pPrev = prev; }
  void insertAfter(T * node)
  {
    node->pNext = pNext;
    node->pPrev = pPrev->pNext;

    pNext->pPrev = node;
    pNext = node;
  }

  void erase()
  {
    assert(pNext != this);
    pPrev->pNext = pNext;
    pNext->pPrev = pPrev;
  }
 };

}

#endif
