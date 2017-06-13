#ifndef _MY_VECTOR_H
#define _MY_VECTOR_H


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


typedef int VectorIter;

BOOL
createVector(
	LPVector *ppVector,
	unsigned int elementSize,
	Printer printer,
	Less less);

void
clearVector(
	LPVector pVector);

void
destroyVector(
	LPVector *ppVector);


BOOL
pushBackInVector(
	LPVector pVector,
	const void *data);

void
popBackInVector(
	LPVector pVector,
	void *data);

BOOL
insertInVector(
	LPVector pVector,
	VectorIter insertPos,
	const void *data);


void
eraseFromVector(
	LPVector pVector,
	VectorIter It);

BOOL
removeValFromVector(
	LPVector pVector,
	const void *key);

BOOL
removeIfInVector(
	LPVector pVector,
	Pred pred);

VectorIter
findInVector(
	LPVector pVector,
	const void *key);

VectorIter
findIfInVector(
	LPVector pVector,
	Pred pred);

void
sortVector(
	LPVector pVector);


void
uniqueVector(	
	LPVector pVector);


void
getFrontOfVector(
	LPVector pVector,
	void *data);

void
getBackOfVector(
	LPVector pVector,
	void *data);

void
getAtInVector(
	LPVector pVector,
	int idx,
	void *data);

unsigned int
getSizeOfVector(
	const LPVector);


BOOL
isVectorEmpty(
	const LPVector);

void *
getDataFromVector(
	LPVector);

void
dumpVector(
	const LPVector,
	const char *,
	unsigned int);

#endif
