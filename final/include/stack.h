#ifndef _MY_STACK_H
#define _MY_STACK_H

#include "common.h"

typedef struct _Stack
{
	char *base;
	unsigned int top;


	unsigned int capacity;
	unsigned int elementSize;
	Printer printer;
}Stack, *LPStack;




bool createStack(LPStack *ppStack, unsigned int elementSize, Printer printer);
void destroyStack(LPStack *ppStack);



bool push(LPStack pStack, const void *data);
void pop(LPStack pStack, void *data);

void getTop(LPStack pStack, void *data);
bool isStackEmpty(const LPStack pStack);

unsigned int sizeOfStack(const LPStack pStack);






#endif
