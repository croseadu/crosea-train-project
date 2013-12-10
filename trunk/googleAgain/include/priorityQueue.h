#ifndef _MY_PRIORITY_QUEUE_H
#define _MY_PRIORITY_QUEUE_H

//implement a min PriorityQueue

#include "heap.h"

typedef struct _Priority_Queue {
  LPHeap pHeap;
  

}PriorityQueue, *LPPriorityQueue;


bool initPriorityQueue(LPPriorityQueue *ppQueue)
{

}
void destroyPriorityQueue(LPPriorityQueue *ppQueue)
{

}
void findMin(LPPriorityQueue pQueue, void *out);
void deleteMin(LPPriorityQueue pQUeue, void *out);
void insertToPriorityQueue(LPPriorityQueue pQueue, void *in)
void boostPriority(LPPr);
void isPriorityQueueEmpty();


#endif
