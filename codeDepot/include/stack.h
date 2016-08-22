#ifndef _MY_STACK_H
#define _MY_STACK_H

#include "common.h"

typdef struct _Stack
{
	void *base;
	
	unsigned int top;

	unsigned int capacity;

	unsigned int elementSize;
}Stack, *LPStack;


BOOL
createStack(LPStack *ppStack,
	    unsigned int elementSize);

void
clearStack(LPStack);

void
destroyStack(LPStack *ppStack);



BOOL
pushToStack(LPStack, const void *data);

BOOL
isStackEmpty(const LPStack);

void getTopOfStack(const LPStack, void *data);
void popFromStack(LPStack);


#endif
