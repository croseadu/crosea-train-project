#include "queue.h"

#include "utils.h"
#include "doubleLinkList.h"
#include "memory.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


struct QueueImpl
{
	LPDoubleLinkList pList;
};


BOOL
createQueue(LPQueue *ppQueue,
            unsigned int elementSize,
            Printer printer)

{
	LPQueue pQueue = NULL;
	struct QueueImpl *pImpl = NULL;
	LPDoubleLinkList pList = NULL;


	pQueue = (LPQueue)myAlloc(sizeof(Queue));
	pImpl = (struct QueueImpl *)myAlloc(sizeof(struct QueueImpl));
	if (NULL == pQueue ||
            NULL == pImpl ||
	    False == createDoubleLinkList(&pList, elementSize, defaultLess, printer) ) {
		goto Fail;
	}

	pQueue->pImpl = pImpl;
	pImpl->pList = pList;
	pQueue->elementSize = elementSize;

	*ppQueue = pQueue;
	return True;

Fail:
	if (pQueue != NULL)
		myFree(pQueue);
	if (pImpl != NULL)
		myFree(pImpl);
	if (pList != NULL)
		destroyDoubleLinkList(&pList);
	
	return False;
}


void
destroyQueue(LPQueue *ppQueue) 
{
	LPQueue pQueue = *ppQueue;
	assert(pQueue != NULL);

	destroyDoubleLinkList(&pQueue->pImpl->pList);
	
	myFree(pQueue->pImpl);
	myFree(pQueue);
}

BOOL
enQueue(LPQueue pQueue, const void *data)
{
	return insertToTailOfDoubleLinkList(pQueue->pImpl->pList, data);
}

BOOL
isQueueEmpty(const LPQueue pQueue)
{
	return isDoubleLinkListEmpty(pQueue->pImpl->pList);
}


void
deQueue(LPQueue pQueue, void *data)
{
	LPDoubleLinkList pList = pQueue->pImpl->pList;
	LPDoubleLinkListNode pHead;

	assert(isQueueEmpty(pQueue) == False);	
	assert(isDoubleLinkListEmpty(pList) == False);

	pHead = pList->pHead->pNext;
	
	memcpy(data, pHead->data, pQueue->elementSize);
	
	removeHeadFromDoubleLinkList(pQueue->pImpl->pList);

}


void
clearQueue(LPQueue pQueue)
{
	clearDoubleLinkList(pQueue->pImpl->pList);

}

void
getFrontOfQueue(LPQueue pQueue, void *data)
{
	getHeadOfDoubleLinkList(pQueue->pImpl->pList, data);
}

void
getBackOfQueue(LPQueue pQueue, void *data)
{
	getTailOfDoubleLinkList(pQueue->pImpl->pList, data);
}


