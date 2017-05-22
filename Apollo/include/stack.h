#ifndef _MY_STACK_H
#define _MY_STACK_H

#include "common.h"


typedef struct _Stack
{
	void *base;
	unsigned int top;


	unsigned int capacity;
	Printer printer;
}Stack, *LPStack;



BOOL
createStack(
	LPStack pStack,
	unsigned int elementSize,
	Printer printer);


void
destroyStack(
	LPStack *ppStack);


BOOL
pushToStack(
	LPStack pStack,
	const void *data);

void
getTopFromStack(
	LPStack pStack,
	void *data);

void popFromStack(
	LPStack pStack);



#endif
