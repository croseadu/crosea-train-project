#ifndef _LIST_H_
#define _LIST_H_
#include <assert.h>
#include "algo.h"
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
    return &(**this);
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
  bool sorted_;
public:
  typedef ListIterator<T> iterator;
  typedef ConstListIterator<T> const_iterator;
public:
  List():pHead(new ListNode<T>()), size_(0), sorted_(false){}
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
    if (*pos < in)
      sorted_ = false;
    newNode->next = next;
    newNode->prev = next->prev;
    newNode->prev->next = newNode;
    next->prev = newNode;
    return iterator(newNode);
  }

  bool push_back(const T & in)
  {
    ListNode<T> * newNode = new ListNode<T>(in);
    if (in < *(--end()))
      sorted_ = false;
    pHead->prev->insert(newNode);
    size_++;
    return true;
  }
  
  bool push_before(const T & in)
  {
    ListNode<T> * newNode = new ListNode<T>(in);
    pHead->insert(newNode);
    size_++;
    if (*begin() < in)
      sorted_ = false;
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
    sorted_ = false;
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

  void remove(const T & in)
  {
    iterator RI = begin();
    while (RI != end())
      {
        iterator nextI = RI;
        ++nextI;
        if (*RI == in)
          erase(RI);
      }
  }

  template <class pred>
  void remove_if(pred p)
  {
    iterator RI = begin();
    while (RI != end())
      {
        iterator nextI = RI;
        ++nextI;
        if (p(*RI))
          erase(RI);
      }
  }

  void reverse()
  {
    ListNode<T> *next, * temp;
    next = pHead->next;
    pHead->next = pHead;
    pHead->prev = pHead;

    while (next != pHead)
      {
        temp = next->next;
        next->next = pHead->next;
        next->prev = pHead;
        pHead->next = next;
        next->next->prev = next;
        next = temp;
      }
    sorted_ = false;
  }

  unsigned int size() const { return size_; }
  
  void sort(enum SORT_TYPE sortMethod = INSERT_SORT)
  {
    if (sortMethod == BUBBLE_SORT)
      {
        bubbleSort();
      }
    else if (sortMethod == INSERT_SORT)
      {
        insertSort();
      }
    else
      quickSort();

    sorted_ = true;
  }

  void merge(const List<T> &rhs, bool sorted)
  {
    if (sorted && rhs.sorted_ && sorted_)
      doMerge(rhs);
    else
      {
        for(iterator RI = rhs.begin(); RI != rhs.end(); ++RI)
          push_before(*RI);
      }
  }


private:
  void doMerge(const List<T> &rhs)
  {
    iterator lRI = begin(), rRI = rhs.begin();
    pHead->next = pHead;
    pHead->prev = pHead;
    while (lRI != end() && rRI != rhs.end())
      {
        if (*lRI < *rRI)
          {
            ++lRI;
          }
        else
          {
            push_back(*rRI);
            ++rRI;
          }
      }
    if (lRI != end())
      {
        
      }

  }
  void bubbleSort(){}
  void insertSort()
  {
    if (size() <= 1)
      return;

    ListNode<T> * leftNode = pHead->next->next;
    pHead->next->next = pHead;
    pHead->prev = pHead->next;

    while (leftNode != pHead)
      {
        ListNode<T> *insertPos = pHead->next, *nextNode=leftNode->next;
        
        while (insertPos != pHead && leftNode->data_ > insertPos->data_)
          insertPos = insertPos->next;
        
        nextNode = leftNode->next;
        leftNode->next = insertPos;
        leftNode->prev = insertPos->prev;
        insertPos->prev->next = leftNode;
        insertPos->prev = leftNode;

        leftNode = nextNode;
      }

  }
  void quickSort(){}
};


}
#endif
