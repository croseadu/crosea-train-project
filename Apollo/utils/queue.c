


#include "common.h"
#include "utils.h"
#include "queue.h"

#include "memory.h"

#include <stdio.h>
#include <assert.h>





BOOL
createQueue(
	LPQueue *ppQueue,
	unsigned int elementSize,
	Printer printer)
{
	LPQueue pQueue;

	pQueue = myAlloc(sizeof(Queue));
	if (NULL == pQueue)
		return False;

	if (False == createDoubleLinkList(&pQueue->pList,
				 elementSize,
				 printer,
				 defaultLess)) {
		myFree(pQueue);
		return False;
	}

	*ppQueue = pQueue;

	return True;
}

void
destroyQueue(
	LPQueue *ppQueue)
{
	LPQueue pQueue = *ppQueue;

	assert(pQueue != NULL);

	destroyDoubleLinkList(&pQueue->pList);
	myFree(pQueue);

	*ppQueue = NULL;
}

BOOL
enQueue(
	LPQueue pQueue,
	const void *data)
{
	insertToTailOfDoubleLinkList(pQueue->pList, data);
}

void
deQueue(
	LPQueue pQueue,
	void *data)
{
	getFrontOfDoubleLinkList(pQueue->pList, data);
	removeHeadFromDoubleLinkList(pQueue->pList);

}

BOOL
isQueueEmpty(
	const LPQueue pQueue)
{
	return pQueue->pList->pHead->pNext == pQueue->pList->pHead ? True : False;
}

