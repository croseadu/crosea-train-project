#ifndef _MY_SET_H
#define _MY_SET_H

#include "common.h"

#include "singleLinkList.h"

typedef struct _Set
{
	LPSingleLinkList pList;
}Set, *LPSet;



BOOL
createSet(
	LPSet *ppSet,
	unsigned int elementSize,
	Less less,
	Printer printer);

void
destroySet(
	LPSet *ppSet);


unsigned int
countInSet(
	const LPSet,
	const void *key);

typedef SingleLinkListIter SetIter;

SetIter
findInSet(
	LPSet pSet,
	const void *key);


BOOL
insertToSet(
	LPSet pSet,
	const void *key);

void
eraseFromSet(
	LPSet pSet,
	SetIter it);

BOOL
eraseKeyFromSet(
	LPSet pSEt,
	const void *key);


#endif
