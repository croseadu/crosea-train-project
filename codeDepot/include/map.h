#ifndef _MY_MAP_H
#define _MY_MAP_H


#include "common.h"


struct MapImpl;

typedef struct _Map
{
	struct MapImpl *pImpl;

	unsigned int keySize;
	unsigned int dataSize;
	Less keyComp;
}Map, *LPMap;

typedef void * MapIter;

BOOL
createMap(LPMap *ppMap,
	  unsigned int keySize,
	  unsigned int dataSize,
	  Less keyComp);


void
clearMap(LPMap);

void
destroyMap(LPMap *);


BOOL
insertToMap(LPMap, const void *key, const void *data);

BOOL
eraseKeyFromMap(LPMap, const void *key);

void
eraseFromMap(LPMap, MapIter);

void
getFirstFromMapIter(LPMap, MapIter, void *key);
void
getSecondFromMapIter(LPMap, MapIter, void *data);


MapIter
findInMap(LPMap, const void *key);

unsigned int
countInMap(LPMap, const void *key);

BOOL
isMapEmpty(const LPMap);

unsigned
getSizeOfKey(const LPMap);

void
traverseMap(LPMap, Visitor);

#endif
