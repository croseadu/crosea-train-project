#ifndef _MY_CIRCULAR_QUEUE_H
#define _MY_CIRCULAR_QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mytype.h"

typedef struct _CIRCULAR_QUEUE
{
  char *data;
  unsigned int head, tail;
  unsigned int elementSize;
  unsigned int max;
}CircularQueue, *LPCircularQueue;


bool initCircularQueue(LPCircularQueue *ppQueue, unsigned int elementSize, unsigned int max)
{
  LPCircularQueue pQueue;
  pQueue = (LPCircularQueue)malloc(sizeof(CircularQueue));
  if (NULL == pQueue) {
    printf ("Out Of Memory in %s", __func__);
    return false;
  }
  pQueue->data = (char *)malloc(elementSize * (max + 1));
  if (NULL == pQueue->data) {
    printf ("Out Of Memory in %s", __func__);
    free(pQueue);
    return false;
  }
  
  pQueue->head = pQueue->tail = 0;
  pQueue->elementSize = elementSize;
  pQueue->max = max;
  *ppQueue = pQueue;
  return true;
}

bool isQueueFull(LPCircularQueue pQueue)
{
  return (pQueue->tail+1)%(pQueue->max+1) == pQueue->head;
}

bool isQueueEmpty(LPCircularQueue pQueue)
{
  return pQueue->tail == pQueue->head;
}



bool enCircularQueue(LPCircularQueue pQueue, void *in)
{
  if (isQueueFull(pQueue)) 
    return false;

  memcpy(pQueue->data+pQueue->elementSize*pQueue->tail, in, pQueue->elementSize);
  ++pQueue->tail;
  return true;
}

bool deCircularQueue(LPCircularQueue pQueue, void *out)
{
  if (isQueueEmpty(pQueue))
    return false;

  memcpy(out, pQueue->data+pQueue->elementSize*pQueue->head, pQueue->elementSize);
  ++pQueue->head;
  return true;
}

void destroyCircularQueue(LPCircularQueue *ppQUeue)
{
  free((*ppQueeu)->data);
  free(*ppQueue);
}




#endif
