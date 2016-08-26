#include "set.h"
#include "singleLinkList.h"


#include "memory.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct SetImpl
{
  LPSingleLinkList pList;
};

typedef struct SetImpl * LPSetImpl;

BOOL
createSet(LPSet *ppSet,
	  unsigned int elementSize,
	  Less less,
	  Printer printer)
{
	LPSet pSet = NULL;
	
	pSet = (LPSet)myAlloc(sizeof(Set));
	if (NULL == pSet) {
		DBG(printf("Out Of Memory in %s %d", __FILE__, __LINE__));
		return False;
	}

	pSet->pImpl = (LPSetImpl)myAlloc(sizeof(struct SetImpl));
	if (NULL == pSet->pImpl) {
		myFree(pSet);
		DBG(printf("Out Of Memory in %s %d", __FILE__, __LINE__));
		return False;
	}
	
	pSet->pImpl->pList = NULL;
	if (createSingleLinkList(&pSet->pImpl->pList, elementSize, less, printer) == False) {
		myFree(pSet->pImpl);
		myFree(pSet);
		return False;
	}

	pSet->elementSize = elementSize;
	pSet->less = less;	
	pSet->printer = printer;
	*ppSet = pSet;
	

	return True;
}


void
clearSet(LPSet pSet)
{
	clearSingleLinkList(pSet->pImpl->pList);
}

void
destroySet(LPSet *ppSet)
{
	LPSet pSet = *ppSet;
	
	assert(pSet != NULL);

	destroySingleLinkList(&pSet->pImpl->pList);
	myFree(pSet->pImpl);
	myFree(pSet);

	*ppSet = NULL;
}


BOOL
insertToSet(LPSet pSet, const void *key)
{
	SingleLinkListIter it = findInSingleLinkList(pSet->pImpl->pList, key);
	if (NULL != it) 
		return False;

	if (False == insertToHeadOfSingleLinkList(pSet->pImpl->pList, key))
		return False;

	return True;
}

BOOL
eraseKeyFromSet(LPSet pSet, const void *key)
{
	return removeInSingleLinkList(pSet->pImpl->pList, key);
}

void
eraseFromSet(LPSet pSet, SetIter it)
{
	SingleLinkListIter sit = (SingleLinkListIter)it;

	eraseFromSingleLinkList(pSet->pImpl->pList, it);
}


SetIter
findInSet(LPSet pSet, const void *key)
{
	SingleLinkListIter it = findInSingleLinkList(pSet->pImpl->pList, key);

	return (SetIter)it;
}

unsigned int
countInSet(LPSet pSet, const void *key)
{
	SetIter it = findInSet(pSet, key);

	return it != NULL ? 1 : 0;
}


BOOL
isSetEmpty(const LPSet pSet)
{
	return isSingleLinkListEmpty(pSet->pImpl->pList);
}

unsigned
getSizeOfSet(const LPSet pSet)
{
	return getSizeOfSingleLinkList(pSet->pImpl->pList);
}




