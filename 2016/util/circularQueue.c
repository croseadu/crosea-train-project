#include "circularQueue.h"
#include <assert.h>
#include "myMemory.h"

enum BOOL
createCircularQueue(LPCircularQueue *ppQueue,
		    unsigned int elementSize,
		    unsigned int maxElements)
{
	LPCircularQueue pQueue;

	pQueue = (LPCircularQueue)myAlloc(sizeof(CircularQueue));
	if (NULL == pQueue) {
		printf("Out Of Memory!");
		return False;
	
	}

	pQueue->base = (char *)myAlloc(elementSize * (maxElements + 1));
	if (NULL == pQueue->base) {
		printf("Out Of memory!");
		myFree(pQueue);
		return False;

	}
	pQueue->front = 0;
	pQueue->back = 0;

	*ppQueue = pQueue;
	return True;

}
void
destroyCircularQueue(LPCircularQueue *ppQueue)
{
	LPCircularQueue pQueue = *ppQueue;

	myFree(pQueue->base);
	myFree(pQueue);

	*ppQueue = NULL;

}

enum BOOL
isCircularQueueEmpty(const LPCircularQueue pQueue)
{
	return (pQueue->front == pQueue->back)?True:False;	

}

enum BOOL
isCircularQueueFull(const LPCircularQueue pQueue)
{
	if ((pQueue->back+1) % (pQueue->maxElements+1) == pQueue->front)
		return True;
	else
		return False;

}

unsigned int
getSizeOfCircularQueue(const LPCircularQueue pQueue)
{
	return (pQueue->back - pQueue->front + pQueue->maxElements + 1) % (pQueue->maxElements+1);

}
void
getFrontOfCircularQueue(const LPCircularQueue pQueue,
	   	        void *data)
{
	assert(isCircularQueueEmpty(pQueue) == False);
	memcpy(data, pQueue->base + pQueue->front * pQueue->elementSize, pQueue->elementSize);	

}
void
getBackOfCircularQueue(const LPCircularQueue pQueue,
			    void *data)
{
	assert(isCircularQueueEmpty(pQueue) == False);
	memcpy(data, pQueue->base + ((pQueue->back + pQueue->maxElements + 1 - 1) % (pQueue->maxElements + 1)) * pQueue->elementSize, pQueue->elementSize);	

}

enum BOOL
pushBackToCircularQueue(LPCircularQueue pQueue, const void *data)
{
	if (isCircularQueueFull(pQueue) == True)
		return False;
	memcpy(pQueue->base + pQueue->back * pQueue->elementSize, data, pQueue->elementSize);
	pQueue->back++;
	pQueue->back = pQueue->back % (pQueue->maxElements + 1);
	return True;	
}
enum BOOL
popFrontFromCircularQueue(LPCircularQueue pQueue, void *data)
{
	if(isCircularQueueEmpty(pQueue) == True)
		return False;
	memcpy(data, pQueue->base + pQueue->front * pQueue->elementSize, pQueue->elementSize);
	pQueue->front++;
	pQueue->front = pQueue->front % (pQueue->maxElements + 1);
	return True;	
}

