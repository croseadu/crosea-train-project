
#ifndef _MY_CIRCULAR_QUEUE_H
#define _MY_CIRCULAR_QUEUE_H


#include "common.h"


typedef struct _CircularQueue
{
	void *buffer;
	unsigned int front;
	unsigned int back;
	
	unsigned int elementSize;	
	unsigned int max;

}CircularQueue, *LPCircularQueue;


BOOL
createCircularQueue(LPCircularQueue *ppQueue, unsigned int elementSize, unsigned int max, Printer printer);


void
destroyCircularQueue(LPCircularQueue *ppQueue);

BOOL
enCircularQueue(LPCircularQueue, const void *data);

BOOL
isCircularQueueFull(const LPCircularQueue pQueue);
BOOL
isCircularQueueEmpty(const LPCircularQueue pQueue);

void
deCircularQueue(LPCircularQueue, void *data);

void
clearCircularQueue(LPCircularQueue);


void
getFrontOfCircularQueue(const LPCircularQueue , void *data);
void
getBackOfCircularQueue(const LPCircularQueue, void *data);

#endif
