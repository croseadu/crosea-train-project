#ifndef _MY_CIRCULAR_QUEUE_H
#define _MY_CIRCULAR_QUEUE_H


#include "common.h"



typedef struct _CircularQueue
{
  char *buffer;
  unsigned int head;
  unsigned int tail;

  unsigned int maxElements;
  unsigned int elementSize;
}CircularQueue, *LPCircularQueue;

bool createCircularQueue(LPCircularQueue *ppQueue, 
			 unsigned int elementSize,
			 unsigned int maxElements);
void destroyCircularQUeue(LPCircularQueue *ppQueue);



bool enqueueCircular(LPCircularQueue pQueue, const void *data);
void dequeueCircular(LPCircularQueue pQueue, void *data);


bool isCircularQueueEmpty(const LPCircularQUeue);
unsigned int sizeOfCircularQueue(const LPCircularQueue);


#endif
