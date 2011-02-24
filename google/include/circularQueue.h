#ifndef _CIRCULARQUEUE_H
#define _CIRCULARQUEUE_H
#include "common.h"

/* circular Queue should only used for those case which max element is known */

typedef struct _CIRCULAR_QUEUE
{
  char *pData;
  int head;
  int tail;
  int maxSize;
  int elementSize;
}CIRCULAR_QUEUE, *LP_CIRCULAR_QUEUE;


STATUS createCircularQueue(LP_CIRCULAR_QUEUE *ppQueue, int maxSize, int elementSize);
void destroyCircularQueue(LP_CIRCULAR_QUEUE pQueue);

BOOL isQueueEmpty(const LP_CIRCULAR_QUEUE pQueue);
BOOL isQueueFull(const LP_CIRCULAR_QUEUE pQueue);

void getFromHead(LP_CIRCULAR_QUEUE pQueue, void *pOut);
void insertToTail(LP_CIRCULAR_QUEUE pQueue, void *pIn);

#endif
