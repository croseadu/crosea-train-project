
#ifndef _MY_PRIORITY_QUEUE_H
#define _MY_PRIORITY_QUEUE_H


#include "common.h"



typedef struct _PriorityQueue
{
  char *buffer;
  unsigned int head;
  unsigned int tail;

  unsigned int elementSize;
  Less         less;
}PriorityQueue, *LPPriorityQueue;

bool createPriorityQueue(LPPriorityQueue *ppQueue, 
			 unsigned int elementSize,
			 Less less);
void destroyPriorityQUeue(LPPriorityQueue *ppQueue);



bool enqueuePriority(LPPriorityQueue pQueue, const void *data);
void dequeuePriority(LPPriorityQueue pQueue, void *data);


bool isPriorityQueueEmpty(const LPPriorityQUeue);
unsigned int sizeOfPriorityQueue(const LPPriorityQueue);


#endif
