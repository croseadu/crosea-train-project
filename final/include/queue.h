#ifndef _MY_QUEUE_H
#define _MY_QUEUE_H


#include "doubleLinkList.h"


typedef struct _Queue
{
	LPDoubleLinkList pList;

	unsigned int elementSize;
	Less         less;
	Printer		printer;
}Queue, *LPQueue;





#include "common.h"

bool createQueue(LPQueue *ppQueue, unsigned int elementSize, Less less, Printer printer);

void destroyQueue(LPQueue *ppQueue);



void clearQueue(LPQueue);

void getHeadOfQueue(LPQueue, void *);
void getTailOfQueue(LPQueue, void *);

bool enQueue(LPQueue, const void *);
void deQueue(LPQueue, void *);

unsigned int sizeOfQueue(const LPQueue);
bool isQueueEmpty(const LPQueue);


#endif
