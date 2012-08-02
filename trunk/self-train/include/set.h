#ifndef _SET_H_
#define _SET_H_

#include "list.h"
namespace MyUtil
{

template <typename T>
class Set
{
  List<T> set_;
  
public:
  typedef typename List<T>::iterator iterator;
  typedef typename List<T>::const_iterator const_iterator;
public:
  Set(){};
  ~Set(){};
  bool insert(const T & in)
  {
    iterator insertPos = begin();
    while (insertPos != end() && *insertPos < in)
      ++insertPos;
    
    if (insertPos == end())
    {
      set_.push_back(in);
      return true;
    }
    else if(*insertPos == in)
    {
      return false;
    }
    else
    {
      set_.insert(insertPos, in);
      return true;
    }
  }

  void erase(const T & in)
  {
    typename List<T>::iterator RI = set_.find(in);
    assert(RI != set_.end());
    set_.erase(RI);
  }

  void erase(iterator pos)
  {
    set_.erase(pos);
  }

  const_iterator find(const T & in) const
  {
    const_iterator RI = begin();
    for (; RI != end(); ++RI)
      if (*RI == in)
        break;
    return RI;
  }

  iterator find(const T & in) 
  {
    iterator RI = begin();
    for (; RI != end(); ++RI)
      if (*RI == in)
        break;
    return RI;
  }
  
  iterator begin()
  {
    return set_.begin();
  }
  iterator end()
  {
    return set_.end();
  }
  
  void clear() { set_.clear(); }

  unsigned int size() const { return set_.size(); }
};




}

#endif
