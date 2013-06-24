#include "../include/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool initStack(LPStack *ppStack, unsigned int elementSize)
{
  LPStack pStack;

  pStack = (LPStack)malloc(sizeof(Stack));
  if (NULL == pStack) {
    printf("Out Of Memory in %s",__func__);
    return false;
  }

  pStack->base = (char *)malloc(elementSize * INIT_STACK_SIZE);
  if (NULL == pStack->base) {
    free(pStack);
    printf("Out Of Memory in %s", __func__);
    return false;
  }

  pStack->top = pStack->base;
  pStack->elementSize = elementSize;
  pStack->capacity = INIT_STACK_SIZE;
  *ppStack = pStack;
  return true;
}

bool isStackEmpty(LPStack pStack)
{
  return pStack->base == pStack->top;
}

bool getTop(LPStack pStack, void *out)
{
  if (isStackEmpty(pStack))
    return false;
  memcpy(out, pStack->top - pStack->elementSize, pStack->elementSize);
  return true;
}

bool push(LPStack pStack, void * in)
{
  if (pStack->top - pStack->base >= pStack->elementSize * pStack->capacity) {
    char *pNew;
    pNew = realloc(pStack->base, 
			   pStack->elementSize*(pStack->capacity+INCRE_STACK_SIZE));
    if (NULL == pNew) {
      printf("Out Of Memory in %s", __func__);
      return false;
    } 
    pStack->base = pNew;
    pStack->top = pStack->base + pStack->capacity * pStack->elementSize; 
    pStack->capacity += INCRE_STACK_SIZE;
  }

  memcpy(pStack->top, in, pStack->elementSize);
  pStack->top += pStack->elementSize;
  return true;
}

bool pop(LPStack pStack, void *out)
{
  if (isStackEmpty(pStack))
    return false;
  memcpy(out, pStack->top - pStack->elementSize, pStack->elementSize);
  pStack->top -= pStack->elementSize;
  return true;
}

void clearStack(LPStack pStack)
{
  pStack->top = pStack->base;
}

void destroyStack(LPStack *ppStack)
{
  free((*ppStack)->base);
  free(*ppStack);
  *ppStack = NULL;
}

unsigned int sizeOfStack(LPStack pStack)
{
  return (pStack->top-pStack->base)/pStack->elementSize;
}
