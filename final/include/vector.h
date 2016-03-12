#ifndef _MY_VECTOR_H
#define _MY_VECTOR_H



typedef struct _Vector
{
	char *data;

	unsigned int elementSize;
	unsigned int compacity;
}Vector, *LPVector;



#include "common.h"

bool createVector(LPVector *ppVector, unsigned int elementSize);
void destroyVector(LPVector **ppVector);



unsigned int sizeOfVector(const LPVector pVector);
bool isVectorEmpty(const LPVector pVector);


bool pushBackToVector(LPVector, const void *data);
void popBackFromVector(LPVector, void *data);

void getFrontInVector(const LPVector, void *data);
void getBackInVector(const LPVector, void *data);



typedef int IteratorOfVector;

bool insertBeforeInVector(LPVector, IteratorOfVector, const void *data);

bool clearVector(LPVector);

bool eraseFromVector(LPVector, IteratorOfVector);



#endif
