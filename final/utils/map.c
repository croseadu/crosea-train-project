


void dummy(void *) {}

bool
createMap(LPMap *ppMap, unsigned int keySize, unsigned int dataSize, Less keyCompare, Printer keyPrint, Printer dataprinter)
{
	LPMap pMap;

	pMap = myAlloc(sizeof(Map));
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

	pMap->keyPrinter = keyPrint;
	pMap->dataPrinter = dataPrint;
	
	*ppMap = pMap;
	return True;

}

void 
destroyMap(LPMap *ppMap)
{
	LPMap pMap = *ppMap;
	clearMap(pMap)

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

	it = findInMap(pMap, key);
	if (it != NULL) {
		setSecondOfMapIterator(pMap, it, data);
		return True;
	}

	

}

IteratorOfMap
findInMap(LPMap pMap, const void *key)
{
	IteratorOfSingleLinkList it;

	it = findInSingleLinkList(pMap->pList, key);
}

void getFirstOfMapIterator(LPMap pMap,IteratorOfMap it, void *key);
void getSecondOfMapIterator(LPMap pMap, IteratorOfMap it, void *data);
void setSecondOfMapIterator(LPMap pMap, IteratorOfMap it, const void *data);

void eraseFromMap(LPMap pMap, IteratorOfMap iter);

