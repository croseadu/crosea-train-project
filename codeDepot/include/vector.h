#ifndef _MY_VECTOR_H
#define _MY_VECTOR_H

#include "common.h"



typedef struct _Vector
{
	void *base;

	unsigned int elementSize;
	unsigned int items;
	unsigned int maxItems;

	Less less;
	Printer printer;
}Vector, *LPVector;


BOOL
createVector(LPVector *,
	     unsigned int elementSize,
             Less less,
             Printer printer);

void
destroyVector(LPVector *);


BOOL
pushFrontInVector(LPVector, const void *);
BOOL
pushBackInVector(LPVector, const void *);

void
popFrontInVector(LPVector, void *);
void
popBackInVector(LPVector, void *);

void
getIthInVector(LPVector, unsigned int, void *);
void
setIthInVector(LPVector, unsigned int, const void *);


BOOL
isVectorEmpty(const LPVector);
unsigned int
getSizeOfVector(const LPVector);


void
sortVector(LPVector);
void
printVector(const LPVector);

#endif
