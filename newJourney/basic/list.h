#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

template <class T>
struct List
{
  T *data;
  unsigned int size;
  unsigned int capacity;
  static const int init_size = 10;
  static const int incre_size = 5;
};

template <class T>
bool initList(List<T> **);

template <class T>
bool initList(List<T> **ppHead)
{
  List<T> * Head = new List<T>();
  if (Head == 0)
    return false;
  Head->data = new T[List<T>::init_size];
  if (Head->data == 0)
    {
      delete Head;
      return false;
    }

  Head->size = 0;
  Head->capacity = List<T>::init_size;
  *ppHead = Head;
  return true;
}

template <class T>
bool ListInsert(List<T> *pHead, T val, int Idx = -1)
{
  if (pHead->size >= pHead->capacity)
    {
      T * data = new T[pHead->capacity + List<T>::incre_size];
      if (data == 0)
	return false;
      std::copy(pHead->data, pHead->data+pHead->size, data);
      delete pHead->data;
      pHead->data = data;
      pHead->capacity += List<T>::incre_size;
    }
  if (Idx == -1)
    pHead->data[pHead->size++] = val;
  else
    {
      for (int i = pHead->size-1; i >= Idx; i--)
	pHead->data[i+1] = pHead->data[i];
      pHead->data[Idx] = val;
      pHead->size++;
    }
  return true;
}

template <class T>
bool PrintList(const List<T> *pHead)
{
  cout<<"List Size :"<<pHead->size<<endl;
  int cnt = 0;
  for (int i = 0; i < pHead->size; i++)
    {
      cout<<pHead->data[i]<<" ";
      cnt++;
      if (cnt%5 == 0)
	cout<<endl;
    }
  if (cnt%5)
    cout<<endl;
}

template <class T>
bool clearList(List<T> *pHead)
{
  for (int i = 0; i < pHead->size; i++)
    pHead->data[i].T::~T();
  delete pHead->data;
  pHead->size = 0;
  return true;
}

template <class T>
bool destroyList(List<T> **ppHead)
{
  if ((*ppHead)->size)
    clearList(*ppHead);
  delete *ppHead;
  *ppHead = 0;
  return true;
}

template <class T, class Pred>
int locateItem(const List<T> *pHead, Pred p)
{
  int i = 0;
  for (i = 0; i < pHead->size; i++)
    if (p(pHead->data[i]))
      return i;
  return -1;
}


template <class T>
bool getItem(const List<T> *pHead, int Idx, T & val)
{
  if (Idx < 0 || Idx >= pHead->size)
    return false;
  val = pHead->data[Idx];
  return true;
}

template <class T>
bool ListDelete(List<T> *pHead, int Idx, T &val)
{
  int i;
  if (Idx < 0 || Idx >= pHead->size)
    return false;
  val = pHead->data[Idx];
  for (i = Idx; i < pHead->size-1; i++)
    pHead->data[i] = pHead->data[i+1];
  pHead->data[i].T::~T();
  pHead->size--;
  return true;
}

template <class T, class Pred>
bool ListDeleteVal(List<T> *pHead, Pred p)
{
  int i = 0, k = 0;
  for (k = 0; k < pHead->size; k++)
    if (!p(pHead->data[k]))
      {
	if (k != i)
	  {
	    pHead->data[i] = pHead->data[k];
	  }
	i++;
      }

      
  pHead->size = i;
  while(i < k)
    pHead->data[i++].T::~T();
  
  return true;
      
}

template <class T>
void ListSort(List<T> *pHead)
{
  for (int i = 1; i < pHead->size; i++)
    {
      if (pHead->data[i] < pHead->data[i-1])
	{
	  int temp = pHead->data[i];

	  j = i;
	  while (j > 0 && temp < pHead->data[j-1])
	    pHead->data[j] = pHead->data[j-1];
	  pHead->data[j] = temp;
	}
    }
}
