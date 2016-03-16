#ifndef _MY_SET_H
#define _MY_SET_H



#include "singleLinkList.h"

typedef struct _Set
{
	LPSingleLinkList pList;

	unsigned int keySize;
	Less         keyCompare;

	Printer      printer;
}Set, *LPSet;

typedef IteratorOfSingleLinkList IteratorOfSet;

bool createSet(LPSet *, unsigned int keySize, Less less, Printer printer);
void destroySet(LPSet *);

void clearSet(LPSet);

bool insertToSet(LPSet, const void *key);
void eraseFromSet(LPSet, IteratorOfSet);

unsigned int countInSet(const LPSet, const void *key);
IteratorOfSet findInSet(const LPSet, const void *key);

#endif

