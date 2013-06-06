#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>


template <class T>
struct Queue
{
  struct Node
  {
    T data;
    Node *pNext;
  };
  Node *pHead;
  Node *pTail;
};

tempalte <class T>
bool initQueue(Queue<T> **ppQueue)
{
  Queue<T> *pQueue;
  
  pQueue = new Queue<T>();
  if (pQueue == 0)
    return false;
  pQueue->pHead = pQueue->pTail = 0;
  *ppQueue = pQueue;
  return true;
}

template <class T>
void clearQueue(Queue<T> *pQueue)
{
  Queue::Node *pIter = pQueue->pHead;
  while (pIter != pQueue->pTail)
    {
      Queue::Node *pTemp = pIter->pNext;
      delete pIter;
      pIter = pTemp;
    }
  
  delete pIter;
  pQueue->pHead = pQueue->pTail = 0;
}

template <class T>
void destroyQueue(Queue<T> **ppQueue)
{
  if ((*ppQueue)->pHead)
    clearQueue(*ppQueue);
  delete (*ppQueue);
  *ppQueue = 0;
}

template <class T>
bool enQueue(Queue<T> *pQueue, const T &element)
{
  Queue::Node *pNode = new Queue::Node();
  if (pNode == 0)
    return false;

  pNode->data = element;
  if (pQueue->pTail)
    {
      pQueue->pTail->pNext = pNode;
      pQueue->pTail = pNode;
    }
  else
    {
      pQueue->pHead = pQueue->pTail = pNode;
      pNode->pNext = 0;
    }
  return true;
}

template <class T>
void deQueue(Queue<T> *pQueue, T &element)
{
  if (isEmpty(pQueue))
    throw "Dequeue on empty Queue";
  
  element = pQueue->pHead->data;

  if (pQueue->pHead == pQueue->pTail)
    {
      delete pQueue->pHead;
      pQueue->pHead = pQueue->pTail = 0;
    }
  else
    {
      Queue::Node *pNode = pQueue->pHead;
      pQueue->pHead = pNode->pNext;
      delete pNode;
    }
}
