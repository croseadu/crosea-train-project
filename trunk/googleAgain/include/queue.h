#ifndef _MY_QUEUE_H
#define _MY_QUEUE_H

#include "mytype.h"

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

bool initQueue(LPQueue *ppQueue, unsigned int elementSize);
bool front(LPQueue pQueue, void * out);
bool rear(LPQueue pQueue, void *out);
bool enQueue(LPQueue pQueue, void * in);
bool deQueue(LPQueue pQueue, void *out);
void clearQueue(LPQueue pQueue);
void destroyQueue(LPQueue *ppQueue);

bool isQueueEmpty(LPQueue pQueue)
{
  return pQueue->pHead == NULL;
}
#endif
