#include "map.h"
#include "singleLinkList.h"

#include "memory.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


struct MapImpl
{
	LPSingleLinkList pList;
};


BOOL
createMap(LPMap *ppMap,
	  unsigned int keySize,
	  unsigned int dataSize,
	  Less keyComp)
{
	
	unsigned int elementSize = keySize + dataSize;
	
	LPMap pMap = NULL;
	struct MapImpl *pImpl = NULL;
	LPSingleLinkList pList = NULL;

	pMap = (LPMap)myAlloc(sizeof(Map));
	pImpl = (struct MapImpl *)myAlloc(sizeof(struct MapImpl));
	if (NULL == pMap ||
	    NULL == pImpl ||
            False == createSingleLinkList(&pList, elementSize, keyComp, defaultPrinter)) {
		goto Fail;
	}

	pMap->pImpl = pImpl;
	pImpl->pList = pList;
	pMap->keySize = keySize;
	pMap->dataSize = dataSize;
	pMap->keyComp = keyComp;


	return True;
Fail:
	if (pMap)
		myFree(pMap);
	if (pImpl)
		myFree(pImpl);
	if (pList)
		destroySingleLinkList(&pList);

	return False;
}

void
clearMap(LPMap pMap)
{
	assert(pMap && pMap->pImpl && pMap->pImpl->pList);

	clearSingleLinkList(pMap->pImpl->pList);
}

void
destroyMap(LPMap *ppMap)
{
	LPMap pMap;

	assert(ppMap && *ppMap);

	pMap = *ppMap;
	clearMap(pMap);
	destroySingleLinkList(&pMap->pImpl->pList);
	myFree(pMap->pImpl);
	myFree(pMap);
}

static const void *reference = NULL;
static Less compFunc = NULL;
BOOL BiggerThanReference(const void *item)
{
	assert(reference != NULL && compFunc != NULL);
	return compFunc(reference, item);
}

BOOL
insertToMap(LPMap pMap, const void *key, const void *data)
{
	void *buffer = NULL;
	unsigned int elementSize;
	
	
	SingleLinkListIter it = findInSingleLinkList(pMap->pImpl->pList, key);
	if (it != NULL)
		return False;

	elementSize = pMap->keySize + pMap->dataSize;

	buffer = myAlloc(elementSize);
	if (NULL == buffer)
		return False;
	memcpy(buffer, key, pMap->keySize);
	memcpy((char*)buffer + pMap->keySize, data, pMap->dataSize);

	reference = data;
	compFunc = pMap->keyComp;
	it = findIfInSingleLinkList(pMap->pImpl->pList, BiggerThanReference);
	
	insertBeforeInSingleLinkList(pMap->pImpl->pList, it, buffer);


	myFree(buffer);

		
	return True;

}


BOOL
eraseKeyFromMap(LPMap pMap, const void *key)
{
	MapIter it = findInMap(pMap, key);
	
	SingleLinkListIter sit = (SingleLinkListIter)it;
	if (*sit == NULL)
		return False;
	
	eraseFromMap(pMap, it);
	return True;
}

void
eraseFromMap(LPMap pMap, MapIter it)
{
	SingleLinkListIter sit = (SingleLinkListIter)it;

	erarseFromSingleLinkList(pMap->pImpl->pList, sit);
}

void
getFirstFromMapIter(LPMap pMap, MapIter it, void *key)
{
	SingleLinkListIter sit = (SingleLinkListIter)it;
	char *buffer;

	assert(sit && *sit);

	buffer = (char *)((*sit)->data);

	memcpy(key, buffer, pMap->keySize);	
}

void
getSecondFromMapIter(LPMap pMap, MapIter it, void *data)
{
	SingleLinkListIter sit = (SingleLinkListIter)it;
	char *buffer;

	assert(sit && *sit);

	buffer = (char *)((*sit)->data);

	memcpy(data, buffer + pMap->keySize, pMap->dataSize);	
}


MapIter
findInMap(LPMap pMap, const void *key)
{
	SingleLinkListIter it = findInSingleLinkList(pMap->pImpl->pList, key);

	return (MapIter)it;
}

unsigned int
countInMap(LPMap pMap, const void *key)
{
	SingleLinkListIter it = findInSingleLinkList(pMap->pImpl->pList, key);

	return (*it) != NULL ? 1 : 0;

}

BOOL
isMapEmpty(const LPMap pMap)
{
	return isSingleLinkListEmpty(pMap->pImpl->pList);
}

unsigned
getSizeOfKey(const LPMap pMap)
{
	return getSizeOfSingleLinkList(pMap->pImpl->pList);


}

