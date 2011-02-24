#ifndef _STACK_H
#define _STACK_H

#include "common.h"

#define INIT_STACK_SIZE 10
#define INCRE_STACK_SIZE 5
typedef struct _STACK
{
	char *pData;
	int elementSize;
	int maxElement;
	int top;
}STACK, *LP_STACK;

STATUS createStack(LP_STACK *ppStack, int elementSize);
void destroyStack(LP_STACK pStack);

BOOL isStackEmpty(const LP_STACK pStack);
void getTop(const LP_STACK pStack, void *pOut);

void pop(LP_STACK pStack, void *pOut);
void push(LP_STACK pStack, const void *pIn);
#endif
