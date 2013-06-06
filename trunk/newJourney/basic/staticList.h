#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>


template <class T, unsigned int N>
struct StaticList
{
  struct Node
  {
    T data;
    unsigned int Idx;
  };
  Node data[N];
  unsigned int freeIdx;
};


template <class T, unsigned int N>
bool initStaticList(StaticList<T, N> **ppList)
{
  StaticList<T, N> *pList = new StaticList<T,N>();
  for (int i = 1; i < N; i++)
    data[i].Idx = i+1;
  data[0].Idx = 0;

  freeIdx = 1;
  return true;
}

template <class T, unsigned int N>
void deleteStaticList(StaticList<T, N> **ppList)
{
  if (*ppList)
    delete *ppList;
  *ppList = 0;
}

template <class T, unsigned int N>
bool getFreeItem(StaticList<T, N> *pList, unsigned int &allocIdx)
{
  allocIdx = pList->freeIdx;
  if (allocIdx == N)
    return false;
  freeIdx = pList->data[freeIdx].Idx;
  return true;
}

template <class T, unsigned int N>
void freeItem(Static<T, N> *pList, unsigned int itemIdx)
{
  pList->data[itemIdx] = pList->freeIdx;
  pList->freeIdx = itemIdx;
}



