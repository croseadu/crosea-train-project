#include "map.h"

typedef struct _Map
{
	LPSingleLinkList pList;

	unsigned int keySize;
	unsigned int dataSize;

	Less keyComp;
	
	Printer printer;
}Map, *LPMap;



BOOL
createMap(
	LPMap *ppMap,
	unsigned int keySize,
	unsigned int dataSize,
	Less keyComp,
	Printer printer)
{
	LPMap pMap;

	pMap = (LPMap)myAlloc(sizeof(Map));
	if (NULL == pMap) {
		return False;
	}

	if (False == createSingleLinkList(&pMap->pList,
					  keySize + dataSize,
					  keyComp,
				          printer)) {
		myFree(pMap);
		return False;
	}

	pMap->keySize = keySize;
	pMap->dataSize = dataSize;

	pMap->keyComp = keyComp;
	pMap->printer = printer;

	*ppMap = pMap;

	return True;
}

void
clearMap(
	LPMap pMap)
{
	clearSingleLinkList(pMap->pList);
}

void
destroyMap(
	LPMap *ppMap)
{
	LPMap pMap = *ppMap;
	assert(pMap != NULL);

	destroySingleLinkList(&pMap->pList);

	myFree(pMap);

	*ppMap = NULL;
}


BOOL
insertToMap(
	LPMap pMap,
	const void *key,
	const void *data)
{
	SingleLinkListIter it;
	void *tempBuffer = NULL;
	

	it = &pMap->pList->pHead;

	while (*it != NULL && pMap->pList->less((*it)->data, key) == True)
		i = &(*it)->pNext;
	
	if (*it != NULL && pMap->pList->less(key, (*it)->data) == False)
		return False;

	tempBuffer = myAlloc(pMap->keySize + pMap->dataSize);
	if (NULL == tempBuffer) {
		assert(0 && "Not Enough Memory!");
		return False;
	}	

	memcpy(tempBuffer, key, pMap->keySize);
	memcpy((char*)tempBuffer + keySize, data, dataSize);

	insertBeforeInSingleLinkList(pMap->pList, it, tempBuffer);

	myFree(tempBuffer);

	return True;
}

BOOL
eraseKeyFromMap(
	LPMap pMap,
	const void *key)
{
	return eraseKeyFromSingleLinkList(pMap->pList, key);
}

void
eraseFromMap(
	LPMap pMap,
	MapIter it)
{
	eraseFromSingleLinkList(pMap->pList, (SingleLinkListIter)it);
}


unsigned int
countInMap(
	const LPMap pMap,
	const void *key)
{
	MapIter it = findInMap(pMap, key);

	if (*it == NULL)
		return 0;

	return 1;
}

MapIter
findInMap(
	LPMap pMap,
	const void *key)
{

	return (MapIter)findInSingleLinkList(pMap->pList, key);
}


void
getFirstFromMapIter(
	LPMap pMap,
	MapIter it,
	void *first)
{
	SingleLinkListIter itOfNode = (SingleLinkListIter)it;

	void *data = itOfNode->data;

	memcpy(first, data, pMap->keySize);
	
}

void
getSecondFromMapIter(
	LPMap pMap,
	MapIter it)
{
{
	SingleLinkListIter itOfNode = (SingleLinkListIter)it;

	void *data = itOfNode->data;

	memcpy(first, (char *)data + pMap->keySize, pMap->dataSize);
	
}






