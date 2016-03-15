#ifndef _MY_CIRCULAR_QUEUE_H
#define _MY_CIRCULAR_QUEUE_H


#include "common.h"



typedef struct _CircularQueue
{
	char *base;
	unsigned int head;
	unsigned int tail;

	unsigned int maxItem;
	unsigned int elementSize;

	Less less;
	Printer printer;
}CircularQueue, *LPCircularQueue;




bool createCircularQueue(LPCircularQueue *ppQueue, unsigned int elementSize, unsigned int maxItem, Less less, Printer printer);

void destroyCircularQueue(LPCircularQueue *ppQueue);


void clearCircularQUeue(LPCircularQueue pQueue);




void getHeadOfCircularQueue(LPCircularQueue, void *);
void getTailOfCircularQueue(LPCircularQueue, void *);



bool enCircularQueue(LPCircularQueue, const void *);

void deCircularQueue(LPCircularQueue, void *);




unsigned int getSizeOfCircularQueue(const LPCircularQueue);
bool isCircularQueueEmpty(const LPCircularQueue);


#endif
