#ifndef _MY_STACK_H
#define _MY_STACK_H

#include "mytype.h"

typedef struct _STACK
{
  char *base;
  char *top;
  unsigned int elementSize;
  unsigned int capacity;
}Stack, *LPStack;

#define INIT_STACK_SIZE 10
#define INCRE_STACK_SIZE 5

bool initStack(LPStack *ppStack, unsigned int elementSize);
bool isStackEmpty(LPStack pStack);
bool getTop(LPStack pStack, void *out);
bool push(LPStack pStack, void * in);
bool pop(LPStack pStack, void *out);
void clearStack(LPStack pStack);
void destroyStack(LPStack *ppStack);
#endif
