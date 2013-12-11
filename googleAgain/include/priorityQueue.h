#ifndef _MY_PRIORITY_QUEUE_H
#define _MY_PRIORITY_QUEUE_H

//implement a min PriorityQueue

#include "heap.h"

typedef struct _Priority_Queue {
  LPHeap pHeap;
}PriorityQueue, *LPPriorityQueue;


bool initPriorityQueue(LPPriorityQueue *ppQueue, unsigned int elementSize,
		       CompareFunc less, CompareFunc equal)
{
  initHeap(&pHeap, elementSize, less, equal);
}

void destroyPriorityQueue(LPPriorityQueue *ppQueue)
{
  destroyHeap(&pHeap);
}

void findMin(LPPriorityQueue pQueue, void *out)
{
  peek(pHeap, out);
}

void deleteMin(LPPriorityQueue pQueue, void *out)
{
  peek(pHeap, out);
  removeRoot(pHeap);
}

void insertToPriorityQueue(LPPriorityQueue pQueue, void *in)
{
  insertKeyToHeap(pHeap, in);
}

void boostPriority(LPPriorityQueue pQueue, void *key, void *new)
{
  increaseRank(pHeap, key, new);
}

void isPriorityQueueEmpty(LPPriorityQueue pQueue)
{
  return isHeapEmpty(pHeap);
}


#endif
