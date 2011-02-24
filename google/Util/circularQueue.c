#include "../include/circularQueue.h"




STATUS createCircularQueue(LP_CIRCULAR_QUEUE *ppQueue, int maxSize, int elementSize)
{
  LP_CIRCULAR_QUEUE pQueue;
  
  pQueue = (LP_CIRCULAR_QUEUE)malloc(sizeof(CIRCULAR_QUEUE));
  if (NULL == pQueue)
    {
      printf("Out Of Memory in line %d, function %s", __LINE__, __FUNCTION__);
      return OVERFLOW;
    }

  pQueue->pData = (char *)malloc((maxSize+1)*elementSize);
  if (NULL == pQueue->pData)
    {
      printf("Out Of Memory in line %d, function %s", __LINE__, __FUNCTION__);
      free(pQueue);
      return OVERFLOW;
    }
  
  pQueue->elementSize = elementSize;
  pQueue->maxSize = maxSize+1;
  pQueue->head = pQueue->tail = 0;

  *ppQueue = pQueue;
  return OK;
}

void destroyCircularQueue(LP_CIRCULAR_QUEUE pQueue)
{
  assert(pQueue && pQueue->pData);
  free(pQueue->pData);
  free(pQueue);
}

BOOL isQueueEmpty(const LP_CIRCULAR_QUEUE pQueue)
{
  return (pQueue->head == pQueue->tail)?TRUE:FALSE;
}

BOOL isQueueFull(const LP_CIRCULAR_QUEUE pQueue)
{
  return (((pQueue->tail+1)%pQueue->maxSize) == pQueue->head)?TRUE:FALSE;
}

void getFromHead(LP_CIRCULAR_QUEUE pQueue, void *pOut)
{
  char *pCur;

  assert(isQueueEmpty(pQueue) == FALSE);

  pCur = pQueue->pData + pQueue->head * pQueue->elementSize;
  memcpy((char *)pOut, pCur, pQueue->elementSize);

  pQueue->head++;
}

void insertToTail(LP_CIRCULAR_QUEUE pQueue, void *pIn)
{
  char *pCur;

  assert(isQueueFull(pQueue) == FALSE);

  pCur = pQueue->pData + pQueue->tail * pQueue->elementSize;
  memcpy(pCur, (char *)pIn, pQueue->elementSize);

  pQueue->tail++;
}
