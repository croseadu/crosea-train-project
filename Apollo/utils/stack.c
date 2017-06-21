#include "stack.h"

#include "common.h"
#include "memory.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

BOOL
createStack(
	LPStack *ppStack,
	unsigned int elementSize,
	Printer printer)
{
	LPStack pStack;


	pStack = myAlloc(sizeof(Stack));
	if (NULL == pStack)
		return False;

	pStack->base = myAlloc(INIT_SIZE * elementSize);
	if (NULL == pStack->base) {
		myFree(pStack);
		return False;
	} 	

	pStack->capacity = INIT_SIZE;
	pStack->elementSize = elementSize;
	pStack->top = 0;
	pStack->printer = printer;


	*ppStack = pStack;
	return True;
}


void
destroyStack(
	LPStack *ppStack)
{
	LPStack pStack = *ppStack;
	assert(pStack != NULL);

	myFree(pStack->base);
	myFree(pStack);

	*ppStack = NULL;
}

static
BOOL reserveInStack(
	LPStack pStack)
{
	pStack->base = myReAlloc(pStack->base, (pStack->capacity + INCRE_SIZE) * pStack->elementSize);
	if (NULL == pStack->base)
		return False;
	pStack->capacity += INCRE_SIZE;
	return True;
}

BOOL
pushToStack(
	LPStack pStack,
	const void *data)
{
	if (pStack->top >= pStack->capacity) {
		if ( False == reserveInStack(pStack))
			return False;
	}

	memcpy((char *)pStack->base + pStack->top * pStack->elementSize, data, pStack->elementSize);

	++pStack->top;
	return True;
}

void
getTopFromStack(
	LPStack pStack,
	void *data)
{
	assert(isStackEmpty(pStack) == False);
	memcpy(data, (char *)pStack->base + (pStack->top - 1)* pStack->elementSize, pStack->elementSize);
}

void popFromStack(
	LPStack pStack)
{
	assert(isStackEmpty(pStack) == False);
	--pStack->top;
}


BOOL
isStackEmpty(
	const LPStack pStack)
{
	return pStack->top == 0 ? True : False;
}
unsigned int
getSizeOfStack(
	const LPStack pStack)
{
	return pStack->top;
}
