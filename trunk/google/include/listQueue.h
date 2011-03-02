#ifndef _LIST_QUEUE_H
#define _LIST_QUEUE_H
#include "common.h"
#include "singleList.h"

typedef struct _LIST_QUEUE
{
  LP_SINGLE_LIST_NODE pListHead;
}LIST_QUEUE, *LP_LIST_QUEUE;


STATUS createListQueue(LP_LIST_QUEUE *ppQueue, unsigned int elementSize);
void destroyListQueue(LP_LIST_QUEUE pQueue);

BOOL isQueueEmpty(const LP_LIST_QUEUE pQueue);

void getFromQueueHead(LP_LIST_QUEUE pQueue, void *pOut);
STATUS insertToQueueTail(LP_LIST_QUEUE pQueue, void *pIn);



#endif
