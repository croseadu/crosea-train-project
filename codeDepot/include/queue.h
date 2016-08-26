#ifndef _MY_QUEUE_H
#define _MY_QUEUE_H


#include "common.h"

struct QueueImpl;

typedef struct _Queue
{
	struct QueueImpl *pImpl;
	
	unsigned int elementSize;	
}Queue, *LPQueue;


BOOL
createQueue(LPQueue *ppQueue, unsigned int elementSize, Printer printer);




void
destroyQueue(LPQueue *ppQueue);

BOOL
enQueue(LPQueue, const void *data);

BOOL
isQueueEmpty(const LPQueue pQueue);

void
deQueue(LPQueue, void *data);

void
clearQueue(LPQueue);


void
getFrontOfQueue(const LPQueue , void *data);

void
getBackOfQueue(const LPQueue, void *data);

#endif
