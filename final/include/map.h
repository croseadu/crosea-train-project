#ifndef _MY_MAP_H
#define _MY_MAP_H

#include "singleLinkList.h"

typedef struct {
	LPSingleLinkList pList;

	unsigned int keySize;
	unsigned int dataSize;

	Printer keyPrinter;
	Printer dataPrinter;
	Less keyCompare;
}Map, *LPMap;

typedef IteratorOfSingleLinkList IteratorOfMap;

bool createMap(LPMap *ppMap, unsigned int keySize, unsigned int dataSize, Less keyCompare, Printer, Printer);

void destroyMap(LPMap *ppMap);

void clearMap(LPMap);


bool insertToMap(LPMap pMap, const void *key, const void *data);

IteratorOfMap findInMap(LPMap pMap, const void *key);

void eraseFromMap(LPMap pMap, IteratorOfMap iter);



void getFirstOfMapIterator(LPMap, IteratorOfMap, void *key);
void getSecondOfMapIterator(LPMap, IteratorOfMap, void *data);

void setSecondOfMapIterator(LPMap, IteratorOfMap, const void *data);

#endif
