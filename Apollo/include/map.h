#ifndef _MY_MAP_H
#define _MY_MAP_H


#include "singleLinkList.h"

typedef struct _Map
{
	LPSingleLinkList pList;

	unsigned int keySize;
	unsigned int dataSize;

	Less keyComp;
	
	Printer printer;
}Map, *LPMap;


typedef SingleLinkListIter MapIter;

BOOL
createMap(
	LPMap *ppMap,
	unsigned int keySize,
	unsigned int dataSize,
	Less keyComp,
	Printer printer);

void
destroyMap(
	LPMap *ppMap);


BOOL
insertToMap(
	LPMap pMap,
	const void *key,
	const void *data);

BOOL
eraseKeyFromMap(
	LPMap pMap,
	const void *key);

void
eraseFromMap(
	LPMap pMap,
	MapIter it);


unsigned int
countInMap(
	const LPMap pMap,
	const void *key);

MapIter
findInMap(
	LPMap pMap,
	const void *key);







#endif
