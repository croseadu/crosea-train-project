#ifndef _LIST_H
#define _LIST_H
#include <assert.h>

namespace MyUtil
{
template <class T>
class List;
template <class T>
class ConstListIterator;
template <class T>
class ListIterator;

template <typename T>
class ListNode
{
  ListNode * next;
  ListNode * prev;
  T data_;
  friend class List<T>;
  friend class ListIterator<T>;
  friend class ConstListIterator<T>;
public:
  ListNode():next(this), prev(this){}
  ListNode(const T & in): next(0), prev(0), data_(in){};
  void insert(ListNode * newNode)
  {
    newNode->next = next;
    newNode->prev = this;
    next->prev= newNode;
    next = newNode;
  }
 void insertBefore(ListNode * newNode)
  {
    prev->insert(newNode);
  }
 void remove()
 {
   assert(next != this);
   next->prev = prev;
   prev->next = next;
 }
};

template <class T>
class ConstListIterator
{
public:
  ListNode<T> *node_;

public:
  explicit ConstListIterator(ListNode<T> *node):node_(node){}

  const T & operator * () const
  {
    return node_->data_;
  }

  const T * operator->() const
  {
    return &*this;
  }

  ConstListIterator & operator++()
  {
    node_ = node_->next;
    return *this;
  }
  
  ConstListIterator & operator--()
  {
    node_ = node_->prev;
    return *this;
  }

  ConstListIterator operator++(int)
  {
    ConstListIterator temp(node_);
    node_ = node_->next;
    return temp;
  }
  
  ListNode<T> * getNode() 
  {
    return node_;
  }
  
};


template <class T>
class ListIterator: public ConstListIterator<T>
{
public:
  explicit ListIterator(ListNode<T> *node):ConstListIterator<T>(node){}
 
  T & operator * ()
  {
    return this->node_->data_;
  }

  T * operator->()
  {
    return &(this->node_->data_);
  }

  ListIterator & operator++()
  {
    this->node_ = this->node_->next;
    return *this;
  }
  
  ListIterator & operator--()
  {
    this->node_ = this->node_->prev;
    return *this;
  }

  ListIterator operator++(int)
  {
    ListIterator temp(this->node_);
    this->node_ = this->node_->next;
    return temp;
  }

};


template <class T>
bool operator!=(ConstListIterator<T> lhs, ConstListIterator<T> rhs)
{
  return lhs.getNode() != rhs.getNode();
}



template <typename T>
class List
{
  ListNode<T> *pHead;
  
public:
  typedef ListIterator<T> iterator;
  typedef ConstListIterator<T> const_iterator;
public:
  List():pHead(new ListNode<T>()){}
  ~List()
  {
    clear();
    delete pHead;
  }
  
  bool push_back(const T & in)
  {
    ListNode<T> * newNode = new ListNode<T>(in);
    pHead->prev->insert(newNode);
  }

  bool push_before(const T & in)
  {
    ListNode<T> * newNode = new ListNode<T>(in);
    pHead->insert(newNode);
  }
  iterator begin()
  {
    return iterator(pHead->next);
  }

  iterator end()
  {
    return iterator(pHead);
  }
  
  void clear()
  {
    ListNode<T> *pIter, *pNext;
    pIter = pHead->next;
    while (pIter != pHead)
      {
        pNext = pIter->next;
        delete pIter;
        pIter = pNext;
      }
    pHead->next = pHead;
    pHead->prev = pHead;
  }

  
  void erase(iterator RI)
  {
    ListNode<T> *node, *prev;
    node = RI.getNode();
    prev = node->prev;
    node->remove();
    delete node;
    //return iterator(prev);
  }
  
};


}
#endif
