#ifndef _MY_QUEUE_H
#define _MY_QUEUE_H

#include "mytype.h"
#include <stdlib.h>
#include <string.h>

typedef struct _QueueNode
{
  char *pData;
  struct _QueueNode *pNext;
  struct _QueueNode *pPrev;
}QueueNode, *QueueNodePtr;

typedef struct _Queue
{
  QueueNodePtr pHead;
  QueueNodePtr pTail;
  unsigned int elementSize;
}Queue, *LPQueue;

bool isQueueEmpty(LPQueue pQueue)
{
  return pQueue->pHead == NULL;
}
bool initQueue(LPQueue *ppQueue, unsigned int elementSize)
{
  LPQueue pQueue;

  pQueue = malloc(sizeof(Queue));
  if (NULL == pQueue) {
    printf("Out Of Memory in %s", __func__);
    return false;
  }
  pQueue->pHead = pQueue->pTail = NULL;
  pQueue->elementSize = elementSize;
  *ppQueue = pQueue;
  return true;
}

bool front(LPQueue pQueue, void * out)
{
  if (NULL == pQueue->pHead)
    return false;

  memcpy(out, pQueue->pHead->pData, pQueue->elementSize);
  return true;
}

bool rear(LPQueue pQueue, void *out)
{
  if (NULL == pQueue->pTail)
    return false;

  memcpy(out, pQueue->pTail->pData, pQueue->elementSize);
  return true;
}

bool enQueue(LPQueue pQueue, void * in)
{
  QueueNodePtr pNew;

  pNew = malloc(sizeof(QueueNode));
  if (NULL == pNew) {
    printf("Out Of Memory in %s", __func__);
    return false;
  }
  pNew->pData = malloc(pQueue->elementSize);
  if (NULL == pNew->pData) {
    printf("Out of Memory in %s", __func__);
    return false;
  }
  
  memcpy(pNew->pData, in, pQueue->elementSize);
  if (pQueue->pTail) {
    pNew->pPrev = pQueue->pTail;
    pNew->pNext = NULL;
    pQueue->pTail->pNext = pNew;
    pQueue->pTail = pNew;
  }
  else {
    pQueue->pHead = pQueue->pTail = pNew;
    pNew->pNext = pNew->pPrev = NULL;
  }
  return true;
}

bool deQueue(LPQueue pQueue, void *out)
{
  if (NULL == pQueue->pHead)
    return false;

  memcpy(out, pQueue->pHead->pData, pQueue->elementSize);
  free(pQueue->pHead->pData);
  if (pQueue->pHead == pQueue->pTail) {
    free(pQueue->pHead);
    pQueue->pHead = pQueue->pTail = NULL;
  }
  else {
    QueueNodePtr pNext = pQueue->pHead->pNext;
    free(pQueue->pHead);
    pQueue->pHead = pNext;
    pQueue->pHead->pPrev = NULL;
  }
  
  return true;
}

void clearQueue(LPQueue pQueue)
{
  QueueNodePtr pIter = pQueue->pHead;
  while (pIter) {
    QueueNodePtr pNext = pIter->pNext;
    free(pIter->pData);
    free(pIter);
    pIter = pNext;
  }
  pQueue->pHead = pQueue->pTail = NULL;
}

void destroyQueue(LPQueue *ppQueue)
{
  LPQueue pQueue = *ppQueue;
  if (NULL != pQueue->pHead)
    clearQueue(pQueue);
  free(pQueue);
  *ppQueue = NULL;
}

#endif
