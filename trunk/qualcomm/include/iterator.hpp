#ifndef _MY_ITERATOR_HPP
#define _MY_ITERATOR_HPP
namespace MyUtil
{
template <class T>
class random_const_iterator
{
  const T* _ptr;
public:
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
  random_iterator():_ptr(0){}
  random_iterator(T* p):_ptr(p){}
  random_iterator(const random_iterator &rhs):_ptr(rhs._ptr){}

  T & operator*() { return *_ptr; }
  T* operator->() { return _ptr; }

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
  bool operator==(const random_iterator & rhs) const
  {
    return _ptr == rhs._ptr;
  }
  bool operator!=(const random_iterator &rhs) const
  {
    return _ptr != rhs._ptr;
  }

};

template <class T>
random_iterator<T> operator+(const random_iterator<T> & rhs, int offset)
{
  random_iterator<T> tmp(rhs);
  tmp+=offset;
  return tmp;
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
