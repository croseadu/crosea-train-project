#ifndef _MY_VECTOR_HPP
#define _MY_VECTOR_HPP
#include <iostream>
#include <assert.h>
#include "iterator.hpp"
#include "algorithm.hpp"
namespace MyUtil
{

  const int initSize = 5;

template <class T>
class vector
{
public:
  typedef unsigned int size_type;
  typedef random_iterator<T> iterator;
  typedef random_const_iterator<T> const_iterator;

private:
  T * _data;
  unsigned int _size;
  unsigned int _capacity;
  
public:
  vector():_data(0), _size(0), _capacity(0){
    _data = new T[initSize];
    if (_data == 0)
      throw "Out Of Memory";

    _capacity = initSize;
  }
  vector(int size)
  {
    assert (size > 0);
    _data = new T[size];
    if (_data == 0)
      throw "Out Of Memory";
    
    _capacity = _size = size;

  }
  vector(const vector &rhs)
  {
    unsigned int i = 0;
    _data = new T[rhs.capacity()];
    if (_data == 0)
      throw "Out Of Memory";
    for (i = 0; i < rhs.size(); i++)
      _data[i] = rhs._data[i];

    _size = rhs._size;
    _capacity = rhs._capacity;
  }

  template <class iter>
  vector(const iter start, const iter end)
  {
    unsigned int size = distance(start, end);
    if (size){
      _data = new T[size];
      if (_data == 0)
	throw "Out of Memory";
      std::cout<<"Create a vector, size is :"<<size<<std::endl;
      _size = size;
      _capacity = size;
      
      int i = 0;
      iter cur = start;
      while(cur != end)
	_data[i++] = *cur++;
    }
      
  }

  size_type size() const { return _size; }
  size_type capacity()const { return _capacity; }
  
  const T & operator[](int i) const
  {
    assert (i >= 0 && i < size);
    return _data[i];
  }
  T & operator[](int i)
  {
    assert (i >= 0 && i < size);
    return _data[i];
  }

  iterator begin() { return iterator(_data); }
  const_iterator begin() const { return const_iterator(_data); }
  iterator end() { return iterator(_data + _size); }
  const_iterator end() const { return const_iterator(_data + _size); }

  
  void reserve(unsigned int cap)
  {
    if (cap <= _capacity)
      return;
    
    T * newData = new T[cap*2];
    if (newData == 0)
      throw "Out Of Memory";
    
    for (int i = 0; i < _size; i++)
      newData[i] = _data[i];
    delete _data;
    _data = newData;
    _capacity = cap*2;
  }
 
  T & front ()
  {
    return _data[0];
  }
  const T & front() const
  {
    return _data[0];
  }
  T & back ()
  {
    return _data[_size - 1];
  }
  const T & back () const
  {
    return _data[_size - 1];
  }

  void push_back(T value)
  {
    reserve(_size+1);
    _data[_size] = value;
    ++_size;
  }

  void pop_back()
  {
    --_size;
  }

  bool empty() const
  {
    return _size == 0;
  }
  
};










}
#endif
