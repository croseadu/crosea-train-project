#include "../include/my.h"
#include "../include/util.h"
#include "../include/stack.h"

STATUS createStack(LP_STACK *ppStack, unsigned int sizeOfElement)
{
	*ppStack = (LP_STACK)malloc(sizeof(STACK));
	if (NULL == *ppStack)
		return OVERFLOW;

	(*ppStack)->pData = malloc(INIT_STACK_SIZE * sizeOfElement);
	if (NULL == (*ppStack)->pData)
	{
		free(*ppStack);
		return OVERFLOW;
	}
	(*ppStack)->maxElements = INIT_STACK_SIZE;
	(*ppStack)->sizeOfElement = sizeOfElement;
	(*ppStack)->top = 0;
	return OK;
}

void destoryStack(LP_STACK pStack)
{
	free(pStack->pData);
	free(pStack);
}

STATUS push(LP_STACK pStack, void *pData)
{
	if (pStack->top >= pStack->maxElements)
	{
		pStack->pData = realloc(pStack->pData, (pStack->maxElements + INCRE_STACK_SIZE)*pStack->sizeOfElement);
		if (NULL == pStack->pData)
		{
			return OVERFLOW;
		}
		pStack->maxElements += INCRE_STACK_SIZE;
	}
	
	memcpy((char *)pStack->pData + pStack->top * pStack->sizeOfElement, (char *)pData, pStack->sizeOfElement);
	pStack->top++;
	return OK;
}

STATUS pop(LP_STACK pStack, void *pData)
{
	if (pStack->top == 0)
		return ERROR;
	
	memcpy((char *)pData, (char *)pStack->pData + (pStack->top - 1)*pStack->sizeOfElement, pStack->sizeOfElement);
	pStack->top--;
	return OK;
}

STATUS getTop(const LP_STACK pStack, void *pData)
{
	if (pStack->top == 0)
		return ERROR;
	
	memcpy((char *)pData, (char *)pStack->pData + (pStack->top - 1)*pStack->sizeOfElement, pStack->sizeOfElement);
	return OK;
}

STATUS isStackEmpty(const LP_STACK pStack)
{
	return (pStack->top == 0);
}



