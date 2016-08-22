#ifndef _MY_SET_H
#define _MY_SET_H


#include "common.h"


struct SetImpl;

typedef struct _Set
{
	SetImpl *pImpl;

	unsigned int elementSize;
	Less less;
}Set, *LPSet;

typedef void * SetIt;

BOOL
createSet(LPSet *ppSet,
	  unsigned int elementSize,
	  Less less);


void
clearSet(LPSet);

void
destroySet(LPSet *);


BOOL
insertToSet(LPSet, const void *key);

BOOL
eraseKeyFromSet(LPSet, const void *key);

void
eraseFromSet(LPSet, SetIter);



SetIter
findInSet(LPSet, const void *key);

unsigned int
countInSet(LPSet, const void *key);

BOOL
isSetEmpty(const LPSet);

unsigned
getSizeOfKey(const LPSet);





#endif
