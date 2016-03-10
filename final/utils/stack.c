#include "stack.h"
#include "myMemory.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



#define INIT_SIZE 10
#define INCRE_SIZE 5

bool
createStack(LPStack *ppStack, unsigned int elementSize, Printer printer)
{
	LPStack pStack = NULL;



	pStack = (LPStack)myAlloc(sizeof(Stack));
	if (NULL == pStack) {
		assert(0 && "out of memory!");
		return False;
	}

	pStack->base = (char *)myAlloc(elementSize * INIT_SIZE);
	if (NULL == pStack->base) {
		myFree(pStack);
		assert(0 && "out of memory!");
		return False;
	}	


	pStack->elementSize = elementSize;
	pStack->capacity = INIT_SIZE;
	pStack->top = 0;

	pStack->printer = printer;

	*ppStack = pStack;
}



void
destroyStack(LPStack *ppStack)
{
	LPStack pStack = *ppStack;

	myFree(pStack->base);
	myFree(pStack);

	*ppStack = NULL;

}

static bool
reserve(LPStack pStack)
{
	pStack->base = myReAlloc(pStack->base, (pStack->capacity + INCRE_SIZE)*pStack->elementSize);
	if (NULL == pStack->base) {
		return False;
	}

	pStack->capacity += INCRE_SIZE;
}

bool
push(LPStack pStack, const void *data)
{
	if (pStack->top == pStack->capacity) {
		if (reserve(pStack) == False) {
			return False;
		}
	}
	
	memcpy(pStack->base + pStack->top * pStack->elementSize, data, pStack->elementSize);
	++pStack->top;

	return True;
}

void
pop(LPStack pStack, void *data)
{
	assert(pStack->top != 0);
	
	--pStack->top;
	

	memcpy(data, pStack->base + pStack->top * pStack->elementSize, pStack->elementSize);
}

void
getTop(LPStack pStack, void *data)
{
	assert(pStack->top != 0);

	memcpy(data, pStack->base + (pStack->top - 1)* pStack->elementSize, pStack->elementSize);
}

bool
isStackEmpty(const LPStack pStack)
{
	return pStack->top == 0 ? True : False;
}

unsigned int
sizeOfStack(const LPStack pStack)
{
	return pStack->top;
}






