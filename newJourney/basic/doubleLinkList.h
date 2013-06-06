#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;


template <class T>
struct DoubleLinkList
{
  T data;
  DoubleLinkList *pPrev;
  DoubleLinkList *pNext;
};


template <class T>
bool initDoubleLinkList(DoubleLinkList<T> **ppList)
{
  DoubleLinkList<T> *pList = new DoubleLinkList<T>();
  
  if (pList == 0)
    return false;
  
  pList->pPrev = pList;
  pList->pNext = pList;
  **ppList = pList;
  return true;
}

template <class T>
void clearDoubleLinkList(DoubleLinkList<T> *pList)
{
  if (pList == 0 || pList->pNext == pList)
    return;

  DoubleLinkList<T> *pIter = pList->pNext;
  while (pIter != pList)
    {
      DoubleLinkList<T> *pTemp = pIter->pNext;
      delete pIter;
      pIter = pTemp;
    }
  pList->pNext = pList;

}

template <class T>
void destroyDoubleLinkList(DoubleLinkList<T> **ppList)
{
  if (*ppList)
    clearDoubleLinkList(*ppList);
  delete *ppList;
  *ppList = 0;
}

template <class T>
bool DoubleLinkListInsertToHead(DoubleLinkList<T> *pList, const T &val);

template <class T>
bool DoubleListInsert(DoubleLinkList<T> *pList, DoubleListList<T> *pInsertPos, const T & val)
{
  if (pInsertPos == 0)
    return DoubleLinkListInsertToHead(pList, val);

  DoubleLinkList<T> *pNode = new DoubleLinkList<T>();
  pNode->data = val;
  pNode->pNext = pInsertPos->next;
  pNode->pPrev = pInsertPos;
  pNode->pNext->pPrev = pNode;
  pInsertPos->pNext = pNode;
  return true;
}

template <class T>
bool DoubleLinkListInsertToHead(DoubleLinkList<T> *pList, const T &val)
{
  
  DoubleLinkList<T> *pNode = new DoubleLinkList<T>();
  pNode->data = val;

  pNode->pNext = pList;
  pList->pPrev = pNode;
  pNode->pPrev = pList;
  pList->pNext = pNode;
  return true;
} 


template <class T>
bool DoubleLinkListInsertToTail(DoubleLinkList<T> *pList, const T &val)
{
  if (pList->pNext == pList)
    return DoubleLinkListInsertToHead(pList, val);

  return DoubleLinkListInsert(pList, pList->pPrev, val);
} 

