#include "set.h"
#include "myMemory.h"


#include <stdlib.h>
#include <string.h>
#include <assert.h>




bool
createSet(LPSet *ppSet, unsigned int keySize, Less less, Printer printer)
{
	LPSet pSet;

	pSet = (LPSet)myAlloc(sizeof(Set));
	if (NULL == pSet) {
		assert(0 && "Out Of Memory!");
		return False;
	}

	if (False == createSingleLinkList(&pSet->pList, keySize, printer, Less)) {
		myFree(pSet);
		assert(0 && "Out Of Memory!");
		return False;
	}

	pSet->keySize = keySize;
	pSet->keyCompare = less;
	pSet->printer = printer;

	*ppSet = pSet;

	return True;
}

void 
destroySet(LPSet *ppSet)
{
	LPSet pSet = *ppSet;
	clearSet(pSet);

	destorySingleLinkList(&pSet->pList);
	myFree(pSet);
	*ppSet = NULL;

}

void clearSet(LPSet pSet)
{
	clearSingleLinkList(pSet->pList);
}

bool
insertToSet(LPSet pSet, const void *key)
{
	IteratorOfSingleLinkList it;

	it = findInSingleLinkList(pSet->pList, key);
	if (NULL == it) {
		if (False == insertToHeadOfSingleLinkList(pSet->pList, key)) {
			return False;
		}
	} 

	return True;	

}

void
eraseFromSet(LPSet pSet, IteratorOfSet it)
{
	IteratorOfSingleLinkList itOfList = (IteratorOfSingleLinkList)it;

	if (False == removeFromSingleLinkList(pSet->pList, itOfLit)) {
		assert(0 && "remove a item which doesn't exist in set!");
		return;
	}
}

static countOfOccurences = 0;
static void *refData = NULL;
static unsigned int elementSize = 0;

void countItem(const void *in)
{
	if (memcmp(in, refData, elementSize) == 0) {
		++countOfOccurrences;
	} 
}

unsigned int
countInSet(const LPSet pSet, const void *key)
{
	countOfOccurences = 0;
	refData = key;
	elementSize = pSet->keySize;

	travsereSingleLinkList(pSet->pList,  countItem);

	return countOfOccurences;
}


IteartorOfSet
findInSet(const LPSet pSet, const void *key)
{
	IteratorOfSingleLinkList it;

	it = findInSingleLinkList(pSet->pList, key);

	return (IteratorOfSet)it;

}


