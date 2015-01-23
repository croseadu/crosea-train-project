#ifndef _MY_QUEUE_H
#define _MY_QUEUE_H

#include "common.h"

typedef struct _MY_QUEUE
{
  void *base
  unsigned int head;
  unsigned int tail;
  unsigned int elementSize;
  unsigned int maxElementCount;
  PrintFunc printer;
}Queue, *LPQueue;

BOOL initQueue(LPQueue *ppQueue,
	       unsigned int elementSize,
	       unsigned int maxElementCount,
	       PrintFunc printer);
void destroyQueue(LPQueue *ppQueue);
BOOL enQueue(LPQueue pQueue, const void *srcElementData);
BOOL deQueue(LPQueue pQueue, void *dstElementData);
BOOL isQueueEmpty(const LPQueue pQueue);
BOOL isQueueFull(const LPQueue pQueue);

#endif
