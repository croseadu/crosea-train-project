#include "queue.h"

#include "doubleLinkList.h"

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
	QueueImpl *pImpl = NULL
	LPSingleLinkList pList = NULL;


	pQueue = (LPQueue)myAlloc(sizeof(Queue));
	pImpl = (QueueImpl *)myAlloc(sizeof(QueueImpl));
	if (NULL == pQueue ||
            NULL == pImpl ||
	    False == createDoubleLinkList(&pList, elementSize, defaultLess, Printer) ) {
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
		destroyDoubleinkList(&pList);
	
	return False;
}


void
destroyQueue(LPQueue *ppQueue) 
{
	LPQueue pQueue = *ppQueue;
	assert(pQueue != NULL);

	destroySingleLinkList(&pQueue->pImpl->pList);
	
	myFree(pQueue->pImpl);
	myFree(pQueue);
}

BOOL
enQueue(LPQueue pQueue, const void *data)
{
	return insertToTailOfSingleLinkList(pQueue->pImpl->pList, data);
}

BOOL
isQueueEmpty(const LPQueue pQueue)
{
	return isSingleLinkListEmpty(pQueue->pImpl->pList);
}


void
deQueue(LPQueue pQueue, void *data)
{
	LPDoubleLinkList pList = pQueue->pImpl->pList;
	assert(isQueueEmpty(pQueue) == False);	
	assert(isDoubleLinkListEmpty(pList) == False);

	
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















