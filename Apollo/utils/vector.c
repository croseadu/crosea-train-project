
#include "common.h"
#include "vector.h"
#include "memory.h"


#include <stdio.h>
#include <string.h>
#include <assert.h>


BOOL
createVector(
	LPVector *ppVector,
	unsigned int elementSize,
	Printer printer,
	Less less)
{
	LPVector pVector;


	pVector = (LPVector)myAlloc(sizeof(Vector));
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

	pVector->capacity += INCRE_SIZE; 

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

	memcpy((char *)pVector->data + pVector->numOfElements * pVector->elementSize , data, pVector->elementSize);
}



void
popBackInVector(
	LPVector pVector,
	void *data)
{
	assert(pVector->numOfElements != 0);
	--pVector->numOfElements;
	memcpy(data, (char *)pVector->data + pVector->numOfElements * pVector->elementSize , pVector->elementSize);
}


BOOL
insertInVector(
	LPVector pVector,
	IterOfVector insertPos,
	const void *data)
{
	int curIdx = (int)insertPos;
	int n = pVector->numOfElements;

	assert(curIdx >= 0 && curIdx < n);

	if (pVector->numOfElements == pVector->capacity) {
		if (reserveMoreInvector(pVector) == False)
			return False;
	}

	while (n > curIdx) {
		memcpy(pVector->data + n * pVector->elementSize, pVector->data + (n - 1) * pVector->elementSize, pVector->elementSize);
		--n;
	}

	memcpy((char *)pVector->data + curIdx * pVector->elementSize, data, pVector->elementSize);
	++pVector->numOfElements;

	return False;
}


void
eraseFromVector(
	LPVector pVector,
	IterOfVector it)
{
	int curIdx = (int)it;

	assert(curIdx >= 0 && curIdx < pVector->numOfElements);

	while (curIdx + 1 < pVector->numOfElements) {
		memcpy((char *)pVector->data + curIdx * pVector->elementSize, pVector->data + (curIdx + 1) * pVector->elementSize, pVector->elementSize);
		++curIdx;	
	}
	--pVector->numOfElements;
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
				mempcy((char *)pVector->data + fillIdx * pVector->elementSize,(char *)pVector->data + curIdx * pVector->elementSize, pVector->elementSize);
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
		if (pVector->less(key, (char *)pVector->data + idx * pVector->elementSize) == False &&
	            pVector->less((char *)pVector->data + idx * pVector->elementSize, key) == False) {
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
		while (j >= 0 && pVector->less((char *)pVector->data + i * pVector->elementSize, (char *)pVector->data + j * pVector->elementSize) == True)
			--j;	
		if (j != i - 1) {
			memcpy(key, (char *)pVector->data + i * pVector->elementSize, pVector->elementSize);
			k = i - 1;	
			while (k > j) {
				mempcy((char *)pVector->data + (k + 1) * pVector->elementSize, (char *)pVector->data + k * pVector->elementSize, pVector->elementSize);
				--k;
			} 
			memcpy((char *)pVector->data + (k+1) * pVector->elementSize, key, pVector->elementSize);
			
		}
	}

	myFree(key);
}


void
uniqueVector(	
	LPVector pVector)
{
	int i = 0;
	int fillIndex = 0;

	int n = pVector->numOfElements;

	if (n <= 1)
		return;

	i = 1;
	fillIndex = 1;
	for (; i < n; ++i) {
		if (pVector->less((char *)pVector->data + i * pVector->elementSize , (char *)pVector->data + (i - 1) * pVector->elementSize) == False &&
		    pVector->less((char *)pVector->data + (i - 1) * pVector->elementSize , (char *)pVector->data + i * pVector->elementSize) == False) {
			;
		} else {
			if (fillIndex != i) {
				memcpy((char *)pVector + fillIndex * pVector->numOfElements, (char *)pVector->data + i * pVector->numOfElements, pVector->elementSize);
			}
			++fillIndex;
		}
	
	}

	pVector->numOfElements = fillIndex;
}


void
getFrontOfVector(
	LPVector pVector,
	void *data)
{
	assert(pVector->numOfElements != 0);
	memcpy(data, (char *)pVector->data, pVector->elementSize);
}

void
getBackOfVector(
	LPVector pVector,
	void *data)
{
	assert(pVector->numOfElements != 0);
	memcpy(data, (char *)pVector->data + pVector->elementSize * (pVector->numOfElements - 1), pVector->elementSize);
}

void
getAtInVector(
	LPVector pVector,
	int idx,
	void *data)
{
	assert(idx < pVector->numOfElements && idx >= 0);
	memcpy(data,(char *)pVector->data + pVector->elementSize * idx, pVector->elementSize);
}

unsigned int
getSizeOfVector(
	const LPVector pVector)
{
	return pVector->numOfElements;
}


BOOL
isVectorEmpty(
	const LPVector pVector)
{
	return (pVector->numOfElements == 0) ? True : False;

}

void *
getDataFromVector(
	LPVector pVector)
{
	return pVector->data;

}

void
dumpVector(
	const LPVector pVector,
	const char *separator,
	unsigned int itemsPerLine)
{
	unsigned int count = 0;
	unsigned int i;
	unsigned int n = pVector->numOfElements;

	printf("\n");
	for (i = 0; i < n; ++i) {
		pVector->printer((char *)pVector->data + i * pVector->elementSize);
		++count;
		if ((count % itemsPerLine) == 0)
			printf("\n");
	}
	
	if (count % itemsPerLine != 0)
		printf("\n");


}



