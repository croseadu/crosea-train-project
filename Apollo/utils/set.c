

#include "common.h"
#include "set.h"

typedef struct _Set
{
	LPSingleLinkList pList;
}Set, *LPSet;



BOOL
createSet(
	LPSet *ppSet,
	unsigned int 	elementSize,
	Less 		less,
	Printer 	printer)
{
	LPSet pSet;

	pSet = myAlloc(sizeof(Set));
	if (NULL == pSet) {
		return False;
	}

	if (False == createSingleLinkList(&pSet->pList,
					  elementSize,
					  less,
					  printer)) {
		myFree(pSet);
		return False;
	}

	*ppSet = pSet;

	return True;
}

void
destroySet(
	LPSet *ppSet)
{
	LPSet pSet = *ppSet;
	assert(pSet != NULL);
	
	destroySingleLinkList(&pSet->pList);

	myFree(pSet);

	*ppSet = NULL;
}


unsigned int
countInSet(
	const LPSet pSet,
	const void *key)
{
	SetIter it = findInSet((LPSet)pSet, key);

	return *it != NULL ? 1 : 0;
}


SetIter
findInSet(
	LPSet pSet,
	const void *key)
{
	SetIter it;
	
	it = (SetIter)findInSingleLinkList(pSet->pList, key);
	return it;
}


BOOL
insertToSet(
	LPSet pSet,
	const void *key)
{
	SingleLinkListIter it = &pSet->pList->pHead;

	while (*it != NULL && pSet->pList->less((*it)->data, key) == True)
		it = &(*it)->pNext;

	if (*it != NULL && pSet->pList->less(key, (*it)->data) == False)
		return False;

	return insertBeforeInSingleLinkList(pSet->pList, it, key);
}

void
eraseFromSet(
	LPSet pSet,
	SetIter it)
{
	eraseFromSingleLinkList(pSet->pList, (SingleLinkListIter)it);
}

BOOL
eraseKeyFromSet(
	LPSet pSEt,
	const void *key)
{
	eraseKeyFromSingleLinkList(pSet->pList, key);
}


