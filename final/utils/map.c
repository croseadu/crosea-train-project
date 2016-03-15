#include "map.h"
#include "myMemory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


void dummy(const void *data) {}

bool
createMap(LPMap *ppMap, unsigned int keySize, unsigned int dataSize, Less keyCompare, Printer keyPrinter, Printer dataPrinter)
{
	LPMap pMap;

	pMap = (LPMap)myAlloc(sizeof(Map));
	if (NULL == pMap) {
		assert(0 && "Out Of Memory!");
		return False;
	}

	if (False == createSingleLinkList(&pMap->pList, keySize + dataSize,  dummy, keyCompare)) {
		myFree(pMap);
		return False;
	}
	
	pMap->keySize = keySize;
	pMap->dataSize = dataSize;

	pMap->keyPrinter = keyPrinter;
	pMap->dataPrinter = dataPrinter;
	
	*ppMap = pMap;
	return True;

}

void 
destroyMap(LPMap *ppMap)
{
	LPMap pMap = *ppMap;
	clearMap(pMap);

	myFree(pMap->pList);
	myFree(pMap);

	*ppMap = NULL;
}

void
clearMap(LPMap pMap)
{
	clearSingleLinkList(pMap->pList);
}


bool
insertToMap(LPMap pMap, const void *key, const void *data)
{
	IteratorOfMap it;
	char *tempData = NULL;

	it = findInMap(pMap, key);
	if (it != NULL) {
		setSecondOfMapIterator(pMap, it, data);
		return True;
	}
	

	tempData =(char *)myAlloc(pMap->keySize + pMap->dataSize);
	if (NULL == tempData) {
		assert(0 && "Out Of Memory!");
		return False;
	}
	memcpy(tempData, key, pMap->keySize);
	memcpy(tempData+pMap->keySize, data, pMap->dataSize);
	
	if (False == insertToHeadOfSingleLinkList(pMap->pList, tempData)) {
		myFree(tempData);
		return False;
	}
	myFree(tempData);
	
	return True;
}

IteratorOfMap
findInMap(LPMap pMap, const void *key)
{
	IteratorOfSingleLinkList it;

	it = findInSingleLinkList(pMap->pList, key);

	return (IteratorOfMap)it;
}

void
getFirstOfMapIterator(LPMap pMap,IteratorOfMap it, void *key)
{
	memcpy(key, (*it)->data, pMap->keySize);
}

void
getSecondOfMapIterator(LPMap pMap, IteratorOfMap it, void *data)
{
	memcpy(data, (*it)->data+pMap->keySize, pMap->dataSize);
}

void
setSecondOfMapIterator(LPMap pMap, IteratorOfMap it, const void *data)
{
	memcpy((*it)->data+pMap->keySize, data, pMap->dataSize);
}

void
eraseFromMap(LPMap pMap, IteratorOfMap it)
{
	IteratorOfSingleLinkList itOfList = (IteratorOfSingleLinkList)it;

	
	eraseFromSingleLinkList(pMap->pList, itOfList);
}

