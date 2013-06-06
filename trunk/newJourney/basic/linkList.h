#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;


template <class T>
struct LinkList
{
  T data;
  LinkList *pNext;
};

template <class T>
bool destroyLinkList(LinkList<T> **ppHead);

template <class T>
bool initLinkList(LinkList<T> **ppHead)
{
  if (*ppHead)
    destroyLinkList(ppHead);
  return true;
}

template <class T>
bool LinkListInsert(LinkList<T> **ppHead, T val, LinkList<T> *insertPos = 0)
{
  if (!insertPos)
    return LinkListInsertToHead(ppHead, val);
  
  LinkList<T> *pNode = new LinkList<T>();
  pNode->data = val;
  pNode->pNext = insertPos->pNext;
  insertPos->pNext = pNode;
  return true;
}

template <class T>
bool LinkListInsertToHead(LinkList<T> **ppHead, T val)
{
  LinkList<T> *pNode = new LinkList<T>();
  pNode->data = val;

  if (*ppHead)
    pNode->pNext = (*ppHead);
  else
    pNode->pNext = 0;
  *ppHead = pNode;
    
  return true;
}

template <class T>
bool LinkListInsertToTail(LinkList<T> **ppHead, T val)
{
  if (**ppHead == 0)
    return LinkListInsertToHead(ppHead, val);
  
  LinkList<T> *pNode = new LinkList<T>();
  pNode->data = val;

  LinkList<T> *pInsertAfter = *ppHead;
  while (pInsertAfter->pNext)
    pInsertAfter = pInsertAfter->pNext;
  pInsertAfter->pNext = pNode;
  return true;
}

template <class T>
void reverseLinkList(LinkList<T> **ppHead)
{
  LinkList<T> *pHead = *ppHead;
  if (!pHead)
    return;
  LinkList<T> *pLeftNode = pHead->pNext;
  pHead->pNext = 0;
  while (pLeftNode)
    {
      LinkList<T> * pTemp = pLeftNode->pNext;
      pLeftNode->pNext = pHead;
      pHead = pLeftNode;
      pLeftNode = pTemp;
    }
  *ppHead = pHead;
}

template <class T>
bool clearLinkList(LinkList<T> *pHead)
{
  LinkList<T> *pNode;
  while (pHead)
    {
      pNode = pHead->pNext;
      delete pHead;
      pHead = pNode;
    }
}

template <class T>
bool destroyLinkList(LinkList<T> **ppHead)
{
  if (*ppHead)
    clearLinkList(*ppHead);
  *ppHead = 0;
  return true;
}


template <class T>
void PrintLinkList(const LinkList<T> *pHead)
{
  int cnt = 0;
  cout<<endl;
  while (pHead)
    {
      cout<<pHead->data<<" ";
      if (!(++cnt % 4))
	cout<<endl;
      pHead = pHead->pNext;
    }
  
  if (cnt == 0)
    cout << "Empty List"<<endl;
  else if (cnt%4)
    cout<<endl;
}

template <class T, class Pred>
void LinkListDeleteVal(LinkList<T> **ppHead, Pred p)
{
  LinkList<T> *pHead = *ppHead;
  LinkList<T> *pPrev = 0;
  while (pHead)
    {
      LinkList<T> *pTemp = pHead->pNext;

      if (p(pHead->data))
	{
	  if (pPrev == 0)
	    {
	      *ppHead = pHead->pNext;
	      delete pHead;
	    }
	  else
	    {
	      delete pHead;
	      pPrev->pNext = pTemp;
	    }
	}
      else
	{
	  pPrev = pHead;
	}
      pHead = pTemp;
    }
}


