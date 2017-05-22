
#ifndef _MY_CIRCULAR_QUEUE_H
#define _MY_CIRCULAR_QUEUE_H


#include "common.h"


typedef struct _CircularQueue
{
	void *buffer;
	
	unsigned int head;
	unsigned int tail;

	unsigned int max;
	Printer printer;
}CircularQueue, *LPCircularQueue;


BOOL
createCircularQueue(
	LPCircularQueue *ppQueue,
	unsigned int elementSize,
	Printer printer);

void
destroyCircularQueue(
	LPCircularQueue *ppQueue);

BOOL
enCircularQueue(
	LPCircularQueue pQueue,
	const void *data);

void
deCircularQueue(
	LPCircularQueue pQueue,
	void *data);

BOOL
isCircularQueueEmpty(
	const LPCircularQueue pQueue);





#endif
