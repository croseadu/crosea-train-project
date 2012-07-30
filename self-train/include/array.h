#ifndef _ARRAY_H
#define _ARRAY_H
#include <assert.h>
#include <cstring>
#include <iostream>

namespace MyUtil
{
template <class T, unsigned int N> 
class Array;
template <class T, unsigned int N>
std::ostream & operator<<(std::ostream &out, const Array<T, N> &in);


template <class T, unsigned int N>
class Array
{
  T data_[N];

public:
  Array()
  {
    memset((void *)data_, 0, N*sizeof(T));
  }
  Array(const Array & in)
  {
    memcpy((void *)data_, (void *)in.data_, N*sizeof(T));
  }

  template <class U, unsigned int K>
  Array(const Array<U, K> & in)
  {
    unsigned int length = N > K?K:N;
    for (unsigned int i = 0;i < length; i++)
      data_[i] = in[i];
  }


  T & operator[](int idx)
  {
    assert (idx >= 0 && idx < N);
    return data_[idx];
  }
  const T & operator[](int idx) const
  {
    assert (idx >= 0 && idx < N);
    return data_[idx];
  }

  unsigned int size() const { return N; }
  friend std::ostream & operator<< <> (std::ostream &out, const Array<T, N> &);
};

template <class T, unsigned int N>
std::ostream & operator<<(std::ostream &out, const Array<T, N> & in)
{
  
  for (unsigned int i = 0; i < N; i++)
    out <<in.data_[i]<<" ";
  return out;
}



template <class T> 
class Vector;
template <class T>
std::ostream & operator<<(std::ostream &out, const Vector<T> &in);

template <class T>
class Vector
{
  T * data_;
  unsigned int size_;
  unsigned int capacity_;
public:
  Vector():data_(0), size_(0){}
  
  Vector(const Vector &in)
  {
    data_ = new T[in.size()];
    if (!data_)
      throw std::bad_alloc();
    memcpy((void *)data_, (void *)in.data_, sizeof(T)*in.size());
    size_ = in.size();
  }
  
  template <unsigned int N>
  Vector(const Array<T, N> &in)
  {
    data_ = new T[N];
    if (!data_)
      throw std::bad_alloc();
    
    for (unsigned int i = 0; i < N; i++)
      data_[i] = in[i];    
    size_ = N; 
    }
  
  ~Vector()
  {
    if (data_)
      delete [] data_;
  }

  T & operator[](int idx)
  {
    assert (idx >= 0 && idx < size_);
    return data_[idx];
  }
  const T & operator[](int idx) const
  {
    assert (idx >= 0 && idx < size_);
    return data_[idx];
  }

  void reserve(unsigned int size)
  {
    if (size <= capacity_)
      return true;
    T * newData = new T[size];
    if (!newData)
      throw std::bad_alloc();
    
    memcpy((void *)newData, (void *)data_, sizeof(T)*size_);
    
    delete [] data_;
    capacity_ = size;
  }

  bool push_back(const T & in)
  {
    if (size_ == capacity_)
      {
        reserve(capacity_*2);
        capacity_ *= 2;
      }
    data_[size_] = in;
    size_++;
  }

  void erase(const unsigned int idx)
  {
    assert(idx < size_);
    for (unsigned int i = idx; i < size_; i++)
      data_[i] = data_[i+1];
    size_--;
  }

  unsigned int capacity() const { return capacity_; }
  unsigned int size() const { return size_; }
  friend std::ostream & operator<< <> (std::ostream &out, const Vector<T> &);

};

template <class T>
std::ostream & operator<<(std::ostream &out, const Vector<T> & in)
{
  
  for (unsigned int i = 0; i < in.size(); i++)
    out <<in.data_[i]<<" ";
  return out;
}


}

#endif
