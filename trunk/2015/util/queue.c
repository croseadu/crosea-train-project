#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "../include/queue.h"



BOOL
initQueue(LPQueue *ppQueue,
	  unsigned int elementSize,
          unsigned int maxElementCount,
	  PrintFunc printer)
{
  LPQueue pQueue = (LPQueue)malloc(sizeof(Queue));
  

  if (NULL == pQueue) {
    printf("Out Of Memory %d %s", __LINE__, __func__);
    return False;
  }
  pQueue->base = malloc(elementSize * (maxElementCount+1));
  if (NULL == pQueue->base) {
    printf("Out Of Memory %d %s", __LINE__, __func__);
    free(pQueue);
    return False;
  }

  pQueue->tail = pQueue->head;
  pQueue->elementSize = elementSize;
  pQueue->maxElementCount = maxElementCount;
  pQUeue->printer = printer;
  *ppQueue = pQueue;
  return True;
}
void
destroyQueue(LPQueue *ppQueue)
{
  LPQueue pQueue = *ppQueue;
  free(pQueue->base);
  free(pQueue);
  *ppQueue = pQueue;
}
BOOL
enQueue(LPQueue pQueue, const void *srcElementData)
{
  assert(!isQueueFull(pQueue));
  memcpy(pQueue->tail*pQueue->elementSize + pQueue->base,
	 srcElementData,
	 pQueue->elementSize);
  if (pQueue->tail == maxElementCount) {
    pQueue->tail = 0;
  } else {
    ++pQueue->tail;
  }
  return True;
}
BOOL
deQueue(LPQueue pQueue, void *dstElementData)
{
  assert(!isQueueEmpty(pQueue));
  memcpy(dstElementData,
	 pQueue->head*pQueue->elementSize + pQueue->base,
	 pQueue->elementSize);
  if (pQueue->head == maxElementCount) {
    pQueue->head = 0;
  } else {
    ++pQueue->head;
  }
  return True;
}
BOOL
isQueueEmpty(const LPQueue pQueue)
{
  return pQueue->head == pQueue->tail;
}

BOOL
isQueueFull(const LPQueue pQueue)
{
  return pQueue->tail 
}
