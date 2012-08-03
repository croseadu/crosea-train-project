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
    return &**this;
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
    return &(**this_);
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
template <class T>
bool operator==(ConstListIterator<T> lhs, ConstListIterator<T> rhs)
{
  return !(lhs != rhs);
}



template <typename T>
class List
{
  ListNode<T> *pHead;
  unsigned int size_;

public:
  typedef ListIterator<T> iterator;
  typedef ConstListIterator<T> const_iterator;
public:
 List():pHead(new ListNode<T>()), size_(0){}
  ~List()
  {
    clear();
    delete pHead;
  }

  iterator insert(const_iterator pos, const T & in)
  {
    size_++;
    ListNode<T> * newNode = new ListNode<T>(in);
    ListNode<T> * next = pos.getNode();
    newNode->next = next;
    newNode->prev = next->prev;
    newNode->prev->next = newNode;
    next->prev = newNode;
    return iterator(newNode);
  }

  bool push_back(const T & in)
  {
    ListNode<T> * newNode = new ListNode<T>(in);
    pHead->prev->insert(newNode);
    size_++;
    return true;
  }
  
  bool push_before(const T & in)
  {
    ListNode<T> * newNode = new ListNode<T>(in);
    pHead->insert(newNode);
    size_++;
    return true;
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
    size_ = 0;
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
    ListNode<T> *node, *prev;
    node = RI.getNode();
    prev = node->prev;
    node->remove();
    delete node;
    size_--;
    //return iterator(prev);
  }

  unsigned int size() const { return size_; }
  
  void sort();
  
};


}
#endif
