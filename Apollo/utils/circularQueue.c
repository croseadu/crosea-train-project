
#include "common.h"

#include "memory.h"

#include <stdio.h>
#include <assert.h>



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
	unsigned int max,
	Printer printer)
{
	LPCircularQueue pQueue = NULL;


	pQueue = myAlloc(sizeof(CircularQueue));
	if (NULL == pQueue) {
		return False;
	}

	pQueue->buffer = myAlloc((max+1) * elementSize);
	if (NULL == pQueue->buffer) {
		myFree(pQueue);
		return False;
	}

	pQueue->head = pQueue->tail = 0;
	pQueue->elementSize = elementSize;
	pQueue->max = max;

	*ppQueue = pQueue;
	return True;
}


void clearCirCularQueue(
	LPCircularQueue pQueue)
{
	pQueue->head = pQueue->tail = 0;
}

void
destroyCircularQueue(
	LPCircularQueue *ppQueue)
{
	LPCircularQueue pQueue;

	pQueue = *ppQueue;
	assert(pQueue != NULL);

	myFree(pQueue->buffer);
	myFree(pQueue);

	*ppQueue = NULL;
}

static BOOL
isCircularQueueFull(
	const LPCircularQueue pQueue)
{
	return ((pQueue->tail + 1) % (pQueue->max + 1) == pQueue->pHead) ? True : False;
}

BOOL
enCircularQueue(
	LPCircularQueue pQueue,
	const void *data)
{
	if (True == isCircularQueueFull(pQueue))
		return False;

	memcpy((char *)pQueue->buffer + pQueue->elementSize * pQueue->tail, data, pQueue->elementSize);
	++pQueue->tail;
	if (pQueue->tail > pQueue->max)
		pQueue->tail = 0;
	return True;
}

void
deCircularQueue(
	LPCircularQueue pQueue,
	void *data)
{
	assert(isCircularQueueEmpty(pQueue) == False);

	mempcy(data, (char *)pQueue->buffer + pQueue->head * pQueue->elementSize, pQueue->elementSize);
	++pQueue->head;
	if (pQueue->head > pQueue->max)
		pQueue->head = 0;
}

BOOL
isCircularQueueEmpty(
	const LPCircularQueue pQueue)
{
	return pQueue->head == pQueue->tail ? True : False;
}





