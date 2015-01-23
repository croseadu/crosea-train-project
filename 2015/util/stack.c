#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/stack.h"

BOOL
initStack(LPStack *ppStack,
	  unsigned int elementSize,
	  PrintFunc printer)
{
  LPStack pStack;
  

  pStack = (LPStack)malloc(sizeof(Stack));
  if (NULL == pStack) {
    printf("Out Of Memory in %d %s", __LINE__, __func__);
    return False;
  }
  pStack->base = malloc(elementSize * INIT_STACK_SIZE);
  if (NULL == pStack->base) {
    printf("Out Of Memory in %d %s", __LINE__, __func__);
    free(pStack);
    return False;
  }
  pStack->top = 0;
  pStack->capacity = INIT_STACK_SIZE;
  pStack->elementSize = elementSize;
  pStack->printer = printer;
  *ppStack = pStack;
  return True;
}
BOOL
destroyStack(LPStack *ppStack)
{
  LPStack pStack;
  assert(ppStack && (pStack=*ppStack));
  
  free(pStack->base);
  free(pStack);
  *ppStack = NULL;  
}

static BOOL
reserveStack(LPStack pStack)
{
  if (pStack->top >= pStack->capacity) {
    pStack->base = realloc(pStack->base, pStack->elementSize*(pStack->capacity + INCRE_STACK_SIZE));
    if (NULL == pStack->base) {
      printf("Out Of Memory in %d %s", __LINE__, __func__);
      return False;
    }
    pStack->capacity += INCRE_STACK_SIZE;
  }
  return True;
}

BOOL
pushStack(LPStack pStack, const void *srcElementData)
{
  if (!reserveStack(pStack))
    return False;
  memcpy(pStack->base+pStack->elementSize*pStack->top,
	 srcElementData,
	 pStack->elementSize);
  ++pStack->top;
  return True;

}
void
popStack(LPStack pStack, void *dstElementData)
{
  assert(!isStackEmpty(pStack));
  --pStack->top;
  memcpy(dstElementData,
	 pStack->base+pStack->elementSize*pStack->top,
	 pStack->elementSize);
}
void
getTopStack(const LPStack pStack, void *dstElementData)
{
  assert(!isStackEmpty(pStack));
  memcpy(dstElementData,
	 pStack->base+pStack->elementSize*(pStack->top-1),
	 pStack->elementSize);
}
BOOL isStackEmpty(const LPStack pStack)
{
  return pStack->top == 0;
}
