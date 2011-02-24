#include "../include/stack.h"

	
STATUS createStack(LP_STACK *ppStack, int elementSize)
{
  LP_STACK pStack = NULL;
  
  pStack = (LP_STACK)malloc(sizeof(STACK));
  if (NULL == pStack)
    {
      printf("Out Of Memory in Line %d, Function  %s\n", __LINE__, __FUNCTION__);
      return OVERFLOW;
    }

  pStack->pData = (char *)malloc(INIT_STACK_SIZE * elementSize);
  if (NULL == pStack->pData)
    {
      printf("Out Of Memory in Line %d, Function  %s\n", __LINE__, __FUNCTION__);
      return OVERFLOW;
    }

  pStack->elementSize = elementSize;
  pStack->maxElement = INIT_STACK_SIZE;
  pStack->top = 0;
  
  *ppStack = pStack;
  return OK;
}


void destroyStack(LP_STACK pStack)
{
  free(pStack->pData);
  free(pStack);
}

BOOL isStackEmpty(const LP_STACK pStack)
{
  return (pStack->top)?FALSE:TRUE;
}


void getTop(const LP_STACK pStack, void *pOut)
{
  char *pCur;

  assert(pStack->top);

  pCur = pStack->pData + (pStack->top-1)*pStack->elementSize;
  memcpy((char *)pOut, pCur, pStack->elementSize);
  
}


void pop(LP_STACK pStack, void *pOut)
{
  char *pCur;

  assert(pStack->top);

  pCur = pStack->pData + (pStack->top-1)*pStack->elementSize;
  memcpy((char *)pOut, pCur, pStack->elementSize);
  
  pStack->top--;
}

void push(LP_STACK pStack, const void *pIn)
{
  char *pCur;

  if (pStack->top >= pStack->maxElement)
    {
      pStack->pData = (char *)realloc(pStack->pData, (pStack->maxElement + INCRE_STACK_SIZE)*pStack->elementSize);
      if (NULL == pStack->pData)
	{
	  printf("Out Of Memory in Line %d Function %s\n", __LINE__, __FUNCTION__);
	  exit(OVERFLOW);
	}
      pStack->maxElement += INCRE_STACK_SIZE;
    }

  pCur = pStack->pData + pStack->top*pStack->elementSize;
  memcpy(pCur, (char *)pIn, pStack->elementSize);
  
  pStack->top++;
}



