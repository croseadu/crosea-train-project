#include "vector.h"

#include "memory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>


#define INIT_VECTOR_SIZE 10
#define INCRE_VECTOR_SIZE 5




BOOL
createVector(LPVector *ppVector,
	     unsigned int elementSize,
             Less less,
             Printer printer)
{
	LPVector pVector = NULL;

	pVector = (LPVector)myAlloc(sizeof(Vector));
	if (NULL == pVector) {
		assert(0 && "Out Of memory!");
		return False;
	}	

	pVector->base = myAlloc(INIT_VECTOR_SIZE * elementSize);
	if (NULL == pVector->base) {
		myFree(pVector);
		assert(0 && "Out Of Memory!");
		return False;
	}


	pVector->elementSize = elementSize;
	pVector->less = less;
	pVector->printer = printer;

	pVector->maxItems = INIT_VECTOR_SIZE;
	pVector->items = 0;


	*ppVector = pVector;

	return True;
}

void
destroyVector(LPVector *ppVector)
{
	LPVector pVector;

	assert(ppVector);
	pVector = *ppVector;
	if (NULL == pVector)
		return;

	if (pVector->base)
		myFree(pVector->base);
	myFree(pVector);


	*ppVector = NULL;
}
static BOOL
reserveVector(LPVector pVector)
{
	unsigned int newSize;

	if (pVector->items < pVector->maxItems)
		return True;

	newSize = (pVector->maxItems + INCRE_VECTOR_SIZE) * pVector->elementSize;
	pVector->base = myRealloc(pVector->base, newSize);
	if (NULL == pVector->base)
		return False;	

	pVector->maxItems += INCRE_VECTOR_SIZE;
	
	return True;
}

BOOL
pushFrontInVector(LPVector pVector, const void *data)
{
	if (False == reserveVector(pVector))
		return False;

	memmove((char *)pVector->base + pVector->elementSize, pVector->base, pVector->elementSize * pVector->items);
	memcpy(pVector->base, data, pVector->elementSize);
	++pVector->items;

	return True;
}

BOOL
pushBackInVector(LPVector pVector, const void *data)
{
	if (False == reserveVector(pVector))
		return False;

	memcpy((char *)pVector->base + pVector->elementSize * pVector->items, data, pVector->elementSize);
	++pVector->items;
	return True;
}

void
popFrontInVector(LPVector pVector, void *data)
{
	assert(isVectorEmpty(pVector) == False);
	memcpy(data, pVector->base, pVector->elementSize);
	--pVector->items;
	memmove(pVector->base, (char *)pVector->base + pVector->elementSize, pVector->items * pVector->elementSize);

}

void
popBackInVector(LPVector pVector, void *data)
{
	assert(isVectorEmpty(pVector) == False);
	--pVector->items;
	memcpy(data, (char *)pVector->base + pVector->items * pVector->elementSize, pVector->elementSize);
}

void
getIthInVector(LPVector pVector, unsigned int idx, void *data)
{
	assert(idx < pVector->items);

	memcpy(data, (char *)pVector->base + idx * pVector->elementSize, pVector->elementSize);
}
void
setIthInVector(LPVector pVector, unsigned int idx, const void *data)
{
	assert(idx < pVector->items);
	memcpy((char *)pVector->base + idx * pVector->elementSize, data, pVector->elementSize);
}


BOOL
isVectorEmpty(const LPVector pVector)
{
	return pVector->items == 0 ? True : False;
}


unsigned int
getSizeOfVector(const LPVector pVector)
{
	return pVector->items;
}


void
sortVector(LPVector pVector)
{
	int i, j;	
	unsigned int size, elementSize;
	char *base;
	char *temp;

	assert(pVector != NULL);

	if (getSizeOfVector(pVector) <= 1)
		return;

	base = (char *)pVector->base;
	elementSize = pVector->elementSize;
	temp = (char *)myAlloc(elementSize);
	if (NULL == temp) {
		assert(0 && "Out Of Memory!");
		return;
	}

	size = getSizeOfVector(pVector);
	for (i = 1; i < size; ++i) {
		j = i -1;
		if (pVector->less(base + i * elementSize, base + j * elementSize) == True) {
			getIthInVector(pVector, i, temp);
			while (j >= 0 && pVector->less(temp, base + j * elementSize) == True) {
				memcpy(base + (j + 1) * elementSize, base + j * elementSize, elementSize);
				--j;
			}
			memcpy(base + (j+1) * elementSize, temp, elementSize);
		}
	}
}

void
printVector(const LPVector pVector)
{
	unsigned int format = 0;
	unsigned int i, size;
	
#define MAX_PER_LINE 5
	assert(pVector != NULL);
	size = getSizeOfVector(pVector);
	for (i = 0; i < size; ++i) {
		++format;
		pVector->printer((char *)pVector->base + i * pVector->elementSize);
		if (format % MAX_PER_LINE == 0) {
			putchar('\n');
		}

	}

	if (format % MAX_PER_LINE != 0) {
		putchar('\n');
	}

#undef MAX_PER_LINE
}


