#include "stack.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#include "memory.h"


typdef struct _Stack
{
	void *base;
	
	unsigned int top;

	unsigned int capacity;

	unsigned int elementSize;
}Stack, *LPStack;


BOOL
createStack(LPStack *ppStack,
	    unsigned int elementSize)
{
	LPStack pStack = NULL;


	pStack = (LPStack)myAlloc(sizeof(Stack));
	if (NULL == pStack) {
		DBG(printf("Out Of Memory in %s %d", __FILE__,__line__));
		return False;
	}

	pStack->base = myAlloc(elementSize * INIT_SIZE);
	if (NULL == pStack->base) {
		myFree(pStack);
		DBG(printf("Out Of Memory in %s %d", __FILE__,__line__));
		return False;
	}

	pStack->top = 0;
	pStack->capacity = INIT_SIZE;
	pStack->elementSize = elementSize;

	*ppStack = pStack;

	return True;
}

void
clearStack(LPStack pStack)
{
	pStack->top = 0;
}

void
destroyStack(LPStack *ppStack)
{
	LPStack pStack = *ppStack;

	assert(pStack != NULL);

	myFree(pStack->base);

	myFree(pStack);

	*ppStack = NULL;
}



BOOL
pushToStack(LPStack pStack, const void *data)
{
	if (pStack->top >= pStack->capacity) {
		void *newBase = myAlloc(pStack->elementSize * (pStack->capacity + INCRE_SIZE));
		if (NULL == newBase) {
			DBG(printf("Out Of Memory in %s %d", __FILE__, __line__));
			return False;
		}

		memcpy(newBase, pStack->base, (pStack->top - 1) * pStack->elementSize);
		myFree(pStack->base);
		pStack->base = newBase;
		pStack->capacity += INCRE_SIZE;
	}

	memcpy((char *)pStack->base + pStack->top * pStack->elementSize, data, pStack->elementSize);
	++pStack->top;

	return True;
}

BOOL
isStackEmpty(const LPStack pStack)
{
	return pStack->top > 0 ? True : False;
}

void getTopOfStack(const LPStack pStack, void *data)
{
	unsigned int curTop = pStack->top - 1;
	assert(pStack->top > 0);
	memcpy(data, (char *)pStack->base + curTop * pStack->elementSize, pStack->elementSize);
}

void popFromStack(LPStack pStack)
{
	assert(pStack->top > 0);
	--pStack->top;
}


