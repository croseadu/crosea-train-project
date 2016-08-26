#include "circularQueue.h"

#include "memory.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


BOOL
createCircularQueue(LPCircularQueue *ppQueue, unsigned int elementSize, unsigned int max, Printer printer)
{
	LPCircularQueue pQueue;
	void *data;

	data = myAlloc(elementSize * (max+1));
	pQueue = (LPCircularQueue)myAlloc(sizeof(CircularQueue));
	if (NULL == data ||
	    NULL == pQueue)
		goto Fail;

	pQueue->buffer = data;
	pQueue->front = pQueue->back = 0;
	pQueue->elementSize = elementSize;
	pQueue->max = max;

	*ppQueue = pQueue;


	return True;
Fail:
	if (data)
		myFree(data);
	if (pQueue)
		myFree(pQueue);

	return False;
}

void
destroyCircularQueue(LPCircularQueue *ppQueue)
{
	LPCircularQueue pQueue;
	pQueue = *ppQueue;
	myFree(pQueue->buffer);
	myFree(pQueue);

	*ppQueue = NULL;
}

BOOL
enCircularQueue(LPCircularQueue pQueue, const void *data)
{
		
	assert(isCircularQueueFull(pQueue) == False);
	memcpy( (char*)pQueue->buffer + pQueue->elementSize * pQueue->back, data, pQueue->elementSize);

	++pQueue->back;
	if (pQueue->back == pQueue->max + 1)
		pQueue->back = 0;

} 

BOOL
isCircularQueueFull(const LPCircularQueue pQueue)
{
	return ( ((pQueue->back + 1) % (pQueue->max + 1) ) == pQueue->front) ? True : False;
}

BOOL
isCircularQueueEmpty(const LPCircularQueue pQueue)
{
	return pQueue->back == pQueue->front ? True : False;
}

void
deCircularQueue(LPCircularQueue pQueue, void *data)
{
	assert(isCircularQueueEmpty(pQueue) == False);
	memcpy(data, (char*)pQueue->buffer + pQueue->elementSize * pQueue->front, pQueue->elementSize);

	++pQueue->front;
	if (pQueue->front == pQueue->max + 1)
		pQueue->front = 0;
}
void
clearCircularQueue(LPCircularQueue pQueue)
{
	pQueue->front = pQueue->back = 0;
}


void
getFrontOfCircularQueue(const LPCircularQueue pQueue, void *data)
{
	
	memcpy(data, (char*)pQueue->buffer + pQueue->elementSize * pQueue->front, pQueue->elementSize);
}

void
getBackOfCircularQueue(const LPCircularQueue pQueue, void *data)
{
	int back= pQueue->back - 1;
	if (back < 0)
		back = pQueue->max;
	memcpy( (char*)pQueue->buffer + pQueue->elementSize * back, data, pQueue->elementSize);
}

