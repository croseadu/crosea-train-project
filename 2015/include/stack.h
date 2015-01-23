#ifndef _MY_STACK_H
#define _MY_STACK_H

#include "common.h"

typedef struct _MY_STACK
{
  void *base;
  unsigned int top;
  unsigned int capacity;
  unsigned int elementSize;
  PrintFunc printer;
}Stack, *LPStack;

#define INIT_STACK_SIZE 10
#define INCRE_STACK_SIZE 5


BOOL initStack(LPStack *ppStack,
	       unsigned int elementSize,
	       PrintFunc printer);
BOOL destroyStack(LPStack *ppStack);

BOOL pushStack(LPStack pStack, const void *srcElementData);
void  popStack(LPStack pStack, void *dstElementData);
void getTopStack(const LPStack pStack, void *dstElementData);
BOOL isStackEmpty(const LPStack pStack);

#endif
