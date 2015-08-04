#ifndef _MY_CIRCULAR_QUEUE_H
#define _MY_CIRCULAR_QUEUE_H

#include "common.h"

typedef struct _CircularQueue
{
	char *base;
	int front;
	int back;
	unsigned int elementSize;
	unsigned int maxElements; 

}CircularQueue, *LPCircularQueue;

enum BOOL createCircularQueue(LPCircularQueue *ppQueue,
			      unsigned int elementSize,
			      unsigned int maxElements);
void destroyCircularQueue(LPCircularQueue *ppQUeue);


enum BOOL isCircularQueueEmpty(const LPCircularQueue pQueue);
unsigned int getSizeOfCircularQueue(const LPCircularQueue pQueue);

void getFrontOfCircularQueue(const LPCircularQueue pQueue,
			     void *data);
void getBackOfCircularQueue(const LPCircularQueue pQueue,
			    void *data);

enum BOOL pushBackToCircularQueue(LPCircularQueue pQueue, const void *data);
enum BOOL popFrontFromCircularQueue(LPCircularQueue pQueue, void *data);

#endif
