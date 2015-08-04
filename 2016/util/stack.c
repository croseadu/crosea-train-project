#include "stack.h"
#include <assert.h>
#include "myMemory.h"

enum BOOL
createStack(LPStack *ppStack,	      
	    unsigned int elementSize,
	    Printer printer)
{
	LPStack pStack;
		
	pStack = (LPStack)myAlloc(sizeof(Stack));
	if (NULL == pStack) {
		printf("Out Of Memory!");
		return False;
	
	}

	pStack->base = (char *)myAlloc(elementSize*INIT_STACK_SIZE);
	if (NULL == pStack->base) {
		printf("Out Of Memory!");
		myFree(pStack);
		return False;
	}

	pStack->top = pStack->base;
	pStack->capacity = INIT_STACK_SIZE;
	pStack->elementSize = elementSize;
	pStack->printer = printer;
	*ppStack = pStack;	
	return True;
}

void
destroyStack(LPStack *ppStack)
{
	LPStack pStack;
	
	if (NULL == ppStack ||
	    NULL == *ppStack)
		return;

	pStack = *ppStack;
	myFree(pStack->base);
	pStack->base = pStack->top = NULL;
	myFree(pStack);
	*ppStack = NULL;
}

enum BOOL
isStackEmpty(const LPStack pStack)
{

	return (pStack->top == pStack->base) ? True : False;

}

unsigned int getStackSize(const LPStack pStack)
{
	return (pStack->top - pStack->base)/pStack->elementSize;

}

void popFromStack(LPStack pStack)
{
	pStack->top = (char *)pStack->top - pStack->elementSize;
}

enum BOOL
pushToStack(LPStack pStack, const void *data)
{
	unsigned int curItems = (pStack->top - pStack->base)/pStack->elementSize;
	if (curItems >= pStack->capacity) {
		pStack->base = myReAlloc(pStack->base, pStack->elementSize* (pStack->capacity+INCRE_STACK_SIZE));
		if (NULL == pStack->base) {
			printf("Out Of memory!");
			return False;
		}		
		pStack->capacity += INCRE_STACK_SIZE;

		/*FIXME reset pStack->top	*/
	}
	memcpy(pStack->top, data, pStack->elementSize);
	pStack->top = (char *)pStack->top + pStack->elementSize;
	return True;
}

void 
getTopFromStack(const LPStack pStack, void *data)
{
	assert ( isStackEmpty(pStack) == False && "Stack is empty");
	memcpy(data, (char *)pStack->top - pStack->elementSize, pStack->elementSize);

}



