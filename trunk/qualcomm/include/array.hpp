#ifndef _MY_ARRAY_HPP
#define _MY_ARRAY_HPP
#include <assert.h>
#include "iterator.hpp"

namespace MyUtil
{


template <class T, unsigned int N = 32>
class array
{
public:
  typedef  unsigned int size_type;
  typedef random_iterator<T> iterator;
  typedef random_const_iterator<T> const_iterator;

private:
  T _data[N];
  
public:
  array(){}
  array(const array &rhs)
  {
    unsigned int i = 0;
    for (i = 0; i < N; i++)
      _data[i] = rhs._data[i];
  }

  template <unsigned int M>
  array(const array<T, M> &rhs)
  {
    unsigned int i = 0, size;
    size = (M > N)?N:M;
    for (i = 0; i < size; i++)
      _data[i] = rhs._data[i];
  }

  size_type size() const { return N; }
  
  const T & operator[](int i) const
  {
    assert (i >= 0 && i < N);
    return _data[i];
  }
  T & operator[](int i)
  {
    assert (i >= 0 && i < N);
    return _data[i];
  }

  iterator begin() { return iterator(_data); }
  const_iterator begin() const { return const_iterator(_data); }
  iterator end() { return iterator(_data+N); }
  const_iterator end() const { return const_iterator(_data+N); }


 
  
  
};










}
#endif
