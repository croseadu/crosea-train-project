
#include "common.h"


typedef struct _Vector
{
	void *data;

	unsigned int elementSize;
	unsigned int capacity;
	unsigned int numOfElements;

	Printer printer;
	Less less;
}Vector, *LPVector;


typedef int IterOfVector;

BOOL
createVector(
	LPVector *ppVector,
	unsigned int elementSize,
	Printer printer,
	Less less)
{
	LPVector pVector;


	pVector = myAlloc(sizeof(Vector));
	if (NULL == pVector) {
		return False;
	}
	
	pVector->data = myAlloc(INIT_SIZE * elementSize);
	if (NULL == pVector->data) {
		myFree(pVector);
		return False;
	}

	pVector->capacity = INIT_SIZE;
	pVector->numOfElements = 0;
	pVector->elementSize = elementSize;


	*ppVector = pVector;
}

void
clearVector(
	LPVector pVector)
{
	pVector->numOfElements = 0;
}

void
destroyVector(
	LPVector *ppVector)
{
	LPVector pVector = *ppVector;
	assert(pVector != NULL);

	myFree(pVector->data);
	myFree(pVector);
}

static BOOL
reserveMoreInVector(
	LPVector pVector)
{
	pVector->data = myReAlloc(pVector->data, (pVector->capacity + INCRE_SIZE ) * pVector->elementSize);
	if (NULL == pVector->data) {
		return False;
	}	
	return True;
}

BOOL
pushBackInVector(
	LPVector pVector,
	const void *data)
{
	if (pVector->numOfElements == pVector->capacity) {
		if (reserveMoreInvector(pVector) == False)
			return False;
	}

	memcpy(pVector->data + pVector->numOfElements * pVector->elementSize , data, pVector->elementSize);
}



void
popBackInVector(
	LPVector pVector,
	void *data)
{
	assert(pVector->numElements != 0);
	--pVector->numElements;
	memcpy(data, pVector->data + pVector->numOfElements * pVector->elementSize , pVector->elementSize);
}


BOOL
insertInVector(
	LPVector pVector,
	IterOfVector insertPos,
	const void *data)
{
	int curIdx = (int)insertPos;
	int n = pVector->numElements;

	assert(curIdx >= 0 && curIdx < n);

	if (pVector->numOfElements == pVector->capacity) {
		if (reserveMoreInvector(pVector) == False)
			return False;
	}

	while (n > curIdx) {
		memcpy(pVector->data + n * pVector->elementSize, pVector->data + (n - 1) * pVector->elementSize, pVector->elementSize);
		--n;
	}

	memcpy(pVector->data + curIdx * pVector->elementSize, data, pVector->elementSize);
	return False;
}


void
eraseFromVector(
	LPVector pVector,
	IterOfVector It)
{
	int curIdx = (int)it;

	assert(curIdx >= 0 && curIdx < pVector->numOfElements);

	while (curIdx + 1 < pVector->numOfElements) {
		memcpy(pVector->data + curIdx * pVector->elementSize, pVector->data + (curIdx + 1) * pVector->elementSize);
		++curIdx;	
	}
}

void
eraseValFromVector(
	LPVector pVector,
	const void *key)
{
	int fillIdx = 0;
	int curIdx = 0;
	int n = pVector->numOfElements;

	while (curIdx < n) {
		if (pVector->less(key, pVector->data + curIdx * pVector->elementSize) == False &&
		    pVector->less(pVector->data + curIdx * pVector->elementSize, key) == False) {
			++curIdx;
		} else {
			if (fillIdx != curIdx) {
				mempcy(pVector->data + fillIdx * pVector->elementSize, pVector->data + curIdx * pVector->elementSize, pVector->elementSize);
			}
			++fillIdx;
			++curIdx;
		}
	}

	pVector->numOfElements = fillIdx;
}

IterOfVector
findInVector(
	LPVector 	pVector,
	const void *key)
{

	int idx = 0;
	int n = pVector->numOfElements;

	for (;idx < n; ++idx) {
		if (pVector->less(key, pVector->data + idx * pVector->elementSize) == False &&
	            pVector->less(pVector->data + idx * pVector->elementSize, key) == False) {
			break;
		}
	}	


	return idx < n ? (IterOfVector)idx : (IterOfVector)-1;
}

void
sortVector(
	LPVector pVector)
{
	int n = pVector->numOfElements;
	int i;
	int j;
	int k;
	void *key;

	if (n <= 1)
		return;

	
	key = myAlloc(pVector->elementSize);
	if (NULL == key)
		return;

	for (i = 1; i < n; ++i) {
		j = i - 1;
		while (j >= 0 && pVector->less(pVector->data + i * pVector->elementSize, pVector->data + j * pVector->elementSize) == True)
			--j;	
		if (j != i - 1) {
			memcpy(key, pVector->data + i * pVector->elementSize, pVector->elementSize);
			k = i - 1;	
			while (k > j) {
				mempcy(pVector->data + (k + 1) * pVector->elementSize, pVector->data + k * pVector->elementSize, pVector->elementSize);
				--k;
			} 
			memcpy(pVector->data + (k+1) * pVector->elementSize, key, pVector->elementSize);
			
		}
	}

	myFree(key);
}


void
uniqueVector(	
	LPVector pVector)
{

}


void
getFrontOfVector(
	LPVector pVector,
	void *data)
{
	assert(pVector->numElements != 0);
	memcpy(data, pVector->data, pVector->elementSize);
}

void
getBackOfVector(
	LPVector pVector,
	void *data)
{
	assert(pVector->numElements != 0);
	memcpy(data, pVector->data + pVector->elementSize * (pVector->numElements - 1), pVector->elementSize);
}

void
getAtInVector(
	LPVector pVector,
	int idx,
	void *data)
{
	assert(idx < pVector->numOfElements && idx >= 0);
	memcpy(data, pVector->data + pVector->elementSize * idx, pVector->elementSize);
}

unsigned int
getSizeOfVector(
	const LPVector pVector)
{
	return pVector->numOfElements
}


BOOL
isVectorEmpty(
	const LPVector pVector)
{
	return (pVector->numOfElements == 0) ? True : False;

}


