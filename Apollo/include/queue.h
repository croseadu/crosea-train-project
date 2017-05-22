#ifndef _MY_QUEUE_H
#define _MY_QUEUE_H


#include "common.h"
#include "doubleLinkList.h"


typedef struct _Queue
{
	LPDoubleLinkList pList;
}Queue, *LPQueue;


BOOL
createQueue(
	LPQueue *ppQueue,
	unsigned int elementSize,
	Printer printer);

void
destroyQueue(
	LPQueue *ppQueue);

BOOL
enQueue(
	LPQueue pQueue,
	const void *data);

void
deQueue(
	LPQueue pQueue,
	void *data);

BOOL
isQueueEmpty(
	const LPQueue pQueue);





#endif
