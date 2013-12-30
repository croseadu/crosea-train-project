#ifndef _MY_PRIORITY_QUEUE_H
#define _MY_PRIORITY_QUEUE_H

//implement a min PriorityQueue

#include "binaryHeap.h"

typedef struct _Priority_Queue {
  LPBinaryHeap pHeap;
}PriorityQueue, *LPPriorityQueue;


bool initPriorityQueue(LPPriorityQueue *ppQueue, unsigned int elementSize,
		       CompareFunc less, CompareFunc equal)
{
  LPPriorityQueue pQueue;
  pQueue = (LPPriorityQueue)malloc(sizeof(PriorityQueue));
  if (NULL == pQueue) {
    return false;
  }
  initBinaryHeap(&pQueue->pHeap, elementSize, less, equal);
  *ppQueue = pQueue;
}

void destroyPriorityQueue(LPPriorityQueue *ppQueue)
{
  destroyBinaryHeap(&(*ppQueue)->pHeap);
  free(*ppQueue);
  *ppQueue = NULL;
}

void findMin(LPPriorityQueue pQueue, void *out)
{
  peekBinaryHeap(pQueue->pHeap, out);
}

void deleteMin(LPPriorityQueue pQueue, void *out)
{
  peekBinaryHeap(pQueue->pHeap, out);
  removeRootFromBinaryHeap(pQueue->pHeap);
}

void insertToPriorityQueue(LPPriorityQueue pQueue, void *in)
{
  insertKeyToBinaryHeap(pQueue->pHeap, in);
  validateBinaryHeap(pQueue->pHeap);
}

void boostPriority(LPPriorityQueue pQueue, void *key, void *new)
{
  increaseRankOnBinaryHeap(pQueue->pHeap, key, new);
  validateBinaryHeap(pQueue->pHeap);
}

bool isPriorityQueueEmpty(LPPriorityQueue pQueue)
{
  return isBinaryHeapEmpty(pQueue->pHeap);
}


#endif
