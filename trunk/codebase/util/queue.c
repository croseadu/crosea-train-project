#include "../include/my.h"
#include "../include/util.h"
#include "../include/queue.h"

STATUS createQueue(LP_QUEUE *ppQueue, unsigned int elementSize, unsigned int maxElements)
{
	LP_QUEUE pQueue;

	pQueue = (LP_QUEUE)malloc(sizeof(QUEUE));
	if (NULL == pQueue)
	{
		Print(("Out of memory when create queue\n"));
		return -1;
	}
	
	pQueue->pData = (char *)malloc((maxElements + 1) * elementSize);
	
	if(NULL == pQueue->pData)
	{
		Print(("Out of memory when create queue\n"));
		free(pQueue);
		return -1;
	}

	pQueue->maxElements = maxElements + 1;
	pQueue->head = pQueue->tail = 0;
	pQueue->elementSize = elementSize;
	*ppQueue = pQueue;
	return OK;
}



void destoryQueue(LP_QUEUE pQueue)
{
	if (pQueue->pData)
		free(pQueue->pData);
	if (pQueue)
		free(pQueue);
}

BOOL isQueueEmpty(LP_QUEUE pQueue)
{
	if (pQueue->head == pQueue->tail)
		return TRUE;
	return FALSE;
}

STATUS getFromHead(LP_QUEUE pQueue, char *data)
{
	if(isQueueEmpty(pQueue))
		return ERROR;
	memcpy(data, pQueue->pData+pQueue->head*pQueue->elementSize, pQueue->elementSize);
	pQueue->head++;
	if(pQueue->head >= pQueue->maxElements)
		pQueue->head = 0;
	return OK;
}

static BOOL isQueueFull(LP_QUEUE pQueue)
{
	if ((pQueue->tail+1)%pQueue->maxElements == pQueue->head)
		return TRUE;
	return FALSE;
}
STATUS insertToTail(LP_QUEUE pQueue, char *data)
{
	if (isQueueFull(pQueue))
	{
		Print(("Circular Queue is Full\n"));
		return ERROR;
	}
	memcpy(pQueue->pData+pQueue->tail*pQueue->elementSize, data, pQueue->elementSize);
	pQueue->tail++;
	if (pQueue->tail >= pQueue->maxElements)
		pQueue->tail = 0;
	return OK;
}