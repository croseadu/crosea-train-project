#include "vector.h"
#include "myMemory.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


#define INIT_SIZE 10
#define INCRE_SIZE 5

bool
createVector(LPVector *ppVector, unsigned int elementSize)
{
	LPVector pVector;

	pVector = myAlloc(sizeof(Vector));
	if (NULL == pVector) {
		assert(0 && "Out Of Memory!");
		return False;
	}

	pVector->data = myAlloc(elementSize * INIT_SIZE);
	if (NULL == pVector->data) {
		myFree(pVector->data);
		assert(0 && "Out Of memory!");
		return False;
	}

	pVector->elementSize = elementSize;
	pVector->capacity = INIT_SIZE;
	
	pVector->size = 0;

	*ppVector = pVector;

	return True;
}


void destroyVector(LPVector *ppVector)
{
	LPVector pVector = *ppVector;
	clearVector(pVector);

	myFree(pVector);

	*ppVector = NULL;
}

void *
dataOfVector(LPVector pVector)
{
	return (void *)pVector->data;
}



unsigned int
sizeOfVector(const LPVector pVector)
{
	return pVector->size;
}


bool isVectorEmpty(const LPVector pVector)
{
	return pVector->size == 0 ? True : False;
}


static bool 
reserve(LPVector pVector)
{
	if (pVector->size == pVector->capacity) {
		pVector->data = myReAlloc(pVector->data, pVector->elementSize * (pVector->capacity + INCRE_SIZE));
		if ( NULL == pVector->data) {
			assert (0 && "Out Of memory!");
			return False;
		}
		pVector->capacity += INCRE_SIZE;
	}

	return True;
}

bool
pushBackToVector(LPVector pVector, const void *data)
{
	if ( reserve(pVector) == False) {
		return False;
	}
	
	memcpy(pVector->data + pVector->size * pVector->elementSize, data, pVector->elementSize);
	++pVector->size;
	return True;	
}


void
popBackFromVector(LPVector pVector, void *data)
{
	assert(isVectorEmpty(pVector) == False);
	
	--pVector->size;
	memcpy(data, (char *)pVector->data + pVector->size * pVector->elementSize, pVector->elementSize);
}

void
getFrontInVector(const LPVector pVector, void *data)
{
	
	assert(isVectorEmpty(pVector) == False);
	
	
	memcpy(data, pVector->data, pVector->elementSize);
}

void
getBackInVector(const LPVector pVector, void *data)
{
	
	assert(isVectorEmpty(pVector) == False);
	
	memcpy(data, (char *)pVector->data + (pVector->size - 1)* pVector->elementSize, pVector->elementSize);
}




bool
insertBeforeInVector(LPVector pVector, IteratorOfVector it, const void *data)
{
	unsigned int end = pVector->size;

	if (reserve(pVector) == False) {
		return False;
	}

	if (it != end) {
		memmove(pVector->data + pVector->elementSize * (it + 1), 
			pVector->data + pVector->elementSize * it,
			(end - it) * pVector->elementSize);
	}
	memcpy(pVector->data + pVector->elementSize * it, data, pVector->elementSize);
	++pVector->size;
	return True;
}

void
clearVector(LPVector pVector)
{

	myFree(pVector->data);
	pVector->size = 0;
}

void
eraseFromVector(LPVector pVector, IteratorOfVector it)
{
	unsigned int end = pVector->size;

	assert (it >= 0 && it < end);

	if (it != end - 1) {
		memmove(pVector->data + pVector->elementSize * it,
			pVector->data + pVector->elementSize * (it + 1),
			(end - it - 1) * pVector->elementSize);

	}
	--pVector->size;
}





