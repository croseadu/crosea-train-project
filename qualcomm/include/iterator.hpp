#ifndef _MY_ITERATOR_HPP
#define _MY_ITERATOR_HPP
#include "iterator_traits.hpp"

namespace MyUtil
{
  template <class T>
  class random_iterator;

  template <class T>
  int operator-(const random_iterator<T> & start, const random_iterator<T> & end);


template <class T>
class random_const_iterator
{
  const T* _ptr;
public:
  typedef random_iter_tag iter_tag;
  typedef T value_type;


  random_const_iterator():_ptr(0){}
  random_const_iterator(T* p):_ptr(p){}
  random_const_iterator(const random_const_iterator &rhs):_ptr(rhs._ptr){}

  const T & operator*() { return *_ptr; }
  const T* operator->() { return _ptr; }

  random_const_iterator & operator++() 
  {
    ++_ptr;
    return *this;
  }
  const random_const_iterator operator++(int)
  {
    random_const_iterator tmp(*this);
    ++_ptr;
    return tmp;
  }
  random_const_iterator & operator--() 
  {
    --_ptr;
    return *this;
  }
  const random_const_iterator operator--(int)
  {
    random_const_iterator tmp(*this);
    --_ptr;
    return tmp;
  }

  random_const_iterator & operator+=(int offset)
  {
    _ptr += offset;
    return *this;
  }
  bool operator==(const random_const_iterator & rhs) const
  {
    return _ptr == rhs._ptr;
  }
  bool operator!=(const random_const_iterator &rhs) const
  {
    return _ptr != rhs._ptr;
  }

};


template <class T>
class random_iterator
{
  T* _ptr;
public:
  typedef random_iter_tag iter_tag;
  typedef T value_type;

  random_iterator():_ptr(0){}
  random_iterator(T* p):_ptr(p){}
  random_iterator(const random_iterator &rhs):_ptr(rhs._ptr){}

  T & operator*() const  { return *_ptr; } 
  T* operator->() const { return _ptr; } 

  random_iterator & operator++() 
  {
    ++_ptr;
    return *this;
  }
  const random_iterator operator++(int)
  {
    random_iterator tmp(*this);
    ++_ptr;
    return tmp;
  }
  random_iterator & operator--() 
  {
    --_ptr;
    return *this;
  }
  const random_iterator operator--(int)
  {
    random_iterator tmp(*this);
    --_ptr;
    return tmp;
  }

  random_iterator & operator+=(int offset)
  {
    _ptr += offset;
    return *this;
  }
  random_iterator & operator-=(int offset)
  {
    _ptr -= offset;
    return *this;
  }
  bool operator==(const random_iterator & rhs) const
  {
    return _ptr == rhs._ptr;
  }
  bool operator!=(const random_iterator &rhs) const
  {
    return _ptr != rhs._ptr;
  }

  
  friend int operator-<>(const random_iterator & lhs, const random_iterator &rhs);

};

template <class T>
random_iterator<T> operator+(const random_iterator<T> & rhs, int offset)
{
  random_iterator<T> tmp(rhs);
  tmp+=offset;
  return tmp;
}
template <class T>
random_iterator<T> operator-(const random_iterator<T> & rhs, int offset)
{
  random_iterator<T> tmp(rhs);
  tmp-=offset;
  return tmp;
}

template <class T>
int operator-(const random_iterator<T> & lhs, const random_iterator<T> & rhs)
{
  return lhs._ptr - rhs._ptr;
}

template <class T>
random_const_iterator<T> operator+(const random_const_iterator<T> & rhs, int offset)
{
  random_const_iterator<T> tmp(rhs);
  tmp+=offset;
  return tmp;
}



}
#endif
