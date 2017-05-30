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


typedef int IterOfVector;

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
	IterOfVector insertPos,
	const void *data);



void
eraseFromVector(
	LPVector pVector,
	IterOfVector It);

void
eraseValFromVector(
	LPVector pVector,
	const void *key);

IterOfVector
findInVector(
	LPVector pVector,
	const void *key);

void
sortVector(
	LPVector pVector);


void
uniqueVector(	
	LPVector pVector);


void
getFrontOfVector(
	LPVector pVector);

void
getBackOfVector(
	LPVector pVector);

void
getAtInVector(
	LPVector pVector,
	unsigned int idx);

unsigned int
getSizeOfVector(
	const LPVector);


BOOL
isVectorEmpty(
	const LPVector);


#endif
