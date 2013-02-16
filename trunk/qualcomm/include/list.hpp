#ifndef _MY_LIST_HPP
#define _MY_LIST_HPP
#include "assert.h"

#include "iterator.hpp"
#include "algorithm.hpp"

namespace MyUtil
{

  
  template <class T>
  class singleList
  {
    template <class U>
    struct singleNode
    {
      U  _data;
      singleNode *next;
      singleNode():_data(0), next(0){}
      singleNode(U data):_data(data), next(0){};
      singleNode(const singleNode &rhs):_data(rhs._data),next(rhs.next){}
    };

    singleNode<T> * pHead;
    unsigned int _size;

  public:
    template <class V>
    class list_iterator
    {
      singleNode<V> *_node;
    public:
      typedef forward_iter_tag iter_tag;

      list_iterator():_node(0){}
      explicit list_iterator(singleNode<V> *node):_node(node){}
      list_iterator & operator++() 
      {
	_node = _node->next;
	return *this;
      }
      const list_iterator operator++(int)
      {
	list_iterator tmp(_node);
	_node = _node->next;
	return tmp;
      }
      
      V & operator*() const
      {
	return _node->_data;
      }
      V * operator->() const
      {
	return &_node->_data;
      }

      bool operator==(const list_iterator &rhs) const
      {
	return _node == rhs._node;
      }
      bool operator!=(const list_iterator &rhs) const
      {
	return _node != rhs._node;
      }
      friend class singleList;
    };

    template <class V>
    class list_const_iterator
    {
      const singleNode<V> *_node;
    public:
      typedef forward_iter_tag iter_tag;
      list_const_iterator():_node(0){}
      explicit list_const_iterator(const singleNode<V> *node):_node(node){}
      list_const_iterator & operator++() 
      {
	_node = _node->next;
	return *this;
      }
      const list_const_iterator operator++(int)
      {
	list_const_iterator tmp(_node);
	_node = _node->next;
	return tmp;
      }
      
      const V & operator*() const
      {
	return _node->_data;
      }
      const V * operator->() const
      {
	return &_node->_data;
      }
      bool operator==(const list_const_iterator &rhs) const
      {
	return _node == rhs._node;
      }
      bool operator!=(const list_const_iterator &rhs) const
      {
	return _node != rhs._node;
      }
    };

    typedef list_iterator<T> iterator;
    typedef list_const_iterator<T> const_iterator;

    singleList():pHead(0), _size(0){}
    singleList(const singleList &rhs)
    {
      iterator start = rhs.begin();
      iterator end = rhs.end();
      singleNode<T> *pCur = pHead;
      while (start != end)
	{
	  singleNode<T> *node = new singleNode<T>(*start);
	  if (pCur)
	    {
	      pCur->next = node;
	      pCur = node;
	    }
	  else
	    pCur = pHead = node;
	  ++start;
	}
      _size = rhs._size;
    }

    unsigned int size() const { return _size; }
    iterator begin ()
    {
      return iterator(pHead);
    }
    const_iterator begin () const
    {
      return const_iterator(pHead);
    }

    iterator end()
    {
      return iterator(0);
    }
    const_iterator end() const
    {
      return const_iterator(0);
    }

    void erase(iterator erasePt)
    {
      assert(erasePt._node);
      singleNode<T> *pDelete = erasePt._node;
      if (pHead == pDelete)
	{
	  singleNode<T> *pNext = pHead->next;
	  delete pHead;
	  pHead = pNext;
	}
      else
	{
	  singleNode<T> *pNext = pHead;
	  while (pNext && pNext->next != pDelete)
	    pNext = pNext->next;
	  assert(pNext);
	  pNext->next = pDelete->next;
	  delete pDelete;
	}
      --_size;
    }

    iterator insert(iterator insertPt, T value)
    {
      singleNode<T> *insertPos = insertPt._node;
      singleNode<T> *newNode = new T(value);

      if (newNode == 0)
	throw "Out Of Memory";

      if (insertPos)
	{
	  newNode->next = insertPos->next;
	  insertPos->next = newNode;
	}
      else
	{
	  if (pHead)
	    {
	      singleNode<T> *pCur = pHead;
	      while (pCur->next)
		pCur = pCur->next;
	      pCur->next = newNode;
	    }
	  else
	    pHead = newNode;
	}

      ++_size;
      return iterator(newNode);
    }
    
    iterator push_front(T value)
    {
      singleNode<T> *newNode = new singleNode<T>(value);

      if (newNode == 0)
	throw "Out Of Memory";

      newNode->next = pHead;
      pHead = newNode;
 
      ++_size;
      return iterator(newNode);
    }

    iterator push_back(T value)
    {
      singleNode<T> *newNode = new singleNode<T>(value);

      if (newNode == 0)
	throw "Out Of Memory";

      if (pHead)
        {
	  singleNode<T> *pCur = pHead;
	  while (pCur->next)
	    pCur = pCur->next;
	  pCur->next = newNode;
	}
      else
	pHead = newNode;

      ++_size;
      return iterator(newNode);
    }

    const T & front() const
    {
      assert(!empty());
      return pHead->_data;
    }
  
    T & front()
    {
      assert(!empty());
      return pHead->_data;
    }

    const T & back() const
    {
      assert(!empty());
      singleNode<T> *pNode = pHead;
      while (pNode->next)
	pNode = pNode->next;
      return pNode->_data;
    }
  
    T & back()
    {
      assert(!empty());
      singleNode<T> *pNode = pHead;
      while (pNode->next)
	pNode = pNode->next;
      return pNode->_data;
    }

    void pop_front ()
    {
      erase(iterator(pHead));
    }
    void pop_back ()
    {
      assert (!empty());
      singleNode<T> **ppDelete = &pHead;
      while ((*ppDelete)->next)
	ppDelete = &(*ppDelete)->next;
      delete (*ppDelete);
      *ppDelete = 0;
    }

    bool empty()const { return !pHead; }

  };


  //-------------------------------------------------------------//
  template <class T>
  class doubleList
  {
    template <class U>
    struct doubleNode
    {
      U  _data;
      doubleNode *next;
      doubleNode *prev;
      doubleNode():_data(0), next(0), prev(0){}
      doubleNode(U data):_data(data), next(0), prev(0){};
      doubleNode(const doubleNode &rhs):_data(rhs._data),next(rhs.next),
					prev(rhs.prev){}
    };

    doubleNode<T> * pHead;
    unsigned int _size;

  public:
    template <class V>
    class list_iterator
    {
      doubleNode<V> *_node;
    public:
      typedef bidirection_iter_tag iter_tag;

      list_iterator():_node(0){}
      explicit list_iterator(doubleNode<V> *node):_node(node){}
      list_iterator & operator++() 
      {
	_node = _node->next;
	return *this;
      }
      const list_iterator operator++(int)
      {
	list_iterator tmp(_node);
	_node = _node->next;
	return tmp;
      }

      list_iterator & operator--() 
      {
	_node = _node->prev;
	return *this;
      }
      const list_iterator operator--(int)
      {
	list_iterator tmp(_node);
	_node = _node->prev;
	return tmp;
      }
      
      V & operator*() const
      {
	return _node->_data;
      }
      V * operator->() const
      {
	return &_node->_data;
      }

      bool operator==(const list_iterator &rhs) const
      {
	return _node == rhs._node;
      }
      bool operator!=(const list_iterator &rhs) const
      {
	return _node != rhs._node;
      }
      friend class doubleList;
    };

    template <class V>
    class list_const_iterator
    {
      const doubleNode<V> *_node;
    public:
      typedef bidirection_iter_tag iter_tag;
      list_const_iterator():_node(0){}
      explicit list_const_iterator(const doubleNode<V> *node):_node(node){}
      list_const_iterator & operator++() 
      {
	_node = _node->next;
	return *this;
      }
      const list_const_iterator operator++(int)
      {
	list_const_iterator tmp(_node);
	_node = _node->next;
	return tmp;
      }
      
      list_const_iterator & operator--() 
      {
	_node = _node->prev;
	return *this;
      }
      const list_const_iterator operator--(int)
      {
	list_const_iterator tmp(_node);
	_node = _node->prev;
	return tmp;
      }
      
      const V & operator*() const
      {
	return _node->_data;
      }
      const V * operator->() const
      {
	return &_node->_data;
      }
      bool operator==(const list_const_iterator &rhs) const
      {
	return _node == rhs._node;
      }
      bool operator!=(const list_const_iterator &rhs) const
      {
	return _node != rhs._node;
      }
      friend class doubleList;
    };

    typedef list_iterator<T> iterator;
    typedef list_const_iterator<T> const_iterator;

    doubleList():_size(0)
    {
      initHead();
    }
    doubleList(const doubleList &rhs)
    {
      iterator start = rhs.begin();
      iterator end = rhs.end();
      doubleNode<T> *pCur = pHead;
      while (start != end)
	{
	  doubleNode<T> *node = new doubleNode<T>(*start);
	  if (pCur)
	    {
	      pCur->next = node;
	      pCur = node;
	    }
	  else
	    pCur = pHead = node;
	  ++start;
	}
      _size = rhs._size;
    }

    unsigned int size() const { return _size; }
    iterator begin ()
    {
      return iterator(pHead->next);
    }
    const_iterator begin () const
    {
      return const_iterator(pHead->next);
    }

    iterator end()
    {
      return iterator(pHead);
    }
    const_iterator end() const
    {
      return const_iterator(pHead);
    }

    void erase(iterator erasePt)
    {
      assert(erasePt._node);
      doubleNode<T> *pDelete = erasePt._node;
      
      pDelete->prev->next  = pDelete->next;
      pDelete->next->prev = pDelete->prev;
      delete pDelete;
      --_size;
    }

    iterator insert(iterator insertPt, T value)
    {
      doubleNode<T> *insertPos = insertPt._node;
      doubleNode<T> *newNode = new doubleNode<T>(value);

      if (newNode == 0)
	throw "Out Of Memory";

      newNode->next = insertPos->next;
      newNode->prev = insertPos;
      insertPos->next = newNode;
      newNode->next->prev = newNode;

      ++_size;
      return iterator(newNode);
    }
    
    iterator push_front(T value)
    {
      return insert(iterator(pHead), value);
    }

    iterator push_back(T value)
    {
      return insert(iterator(pHead->prev), value);
    }

    const T & front() const
    {
      assert(!empty());
      return pHead->next->_data;
    }
  
    T & front()
    {
      assert(!empty());
      return pHead->next->_data;
    }

    const T & back() const
    {
      assert(!empty());

      return pHead->prev->_data; 
    }
  
    T & back()
    {
      assert(!empty());

      return pHead->prev->_data; 
    }

    void pop_front ()
    {
      erase(iterator(pHead));
    }
    void pop_back ()
    {
      assert (!empty());
      
      erase(iterator(pHead->prev));
    }

    bool empty()const { return pHead->next == pHead; }

   private:
    void initHead()
    {
      pHead = new doubleNode<T>();
      pHead->next = pHead;
      pHead->prev = pHead;
    }
  };


}


#endif
