#ifndef _MY_MAP_H
#define _MY_MAP_H

#include "common.h"

typedef struct _MapInternalNode
{
	void *key;
	void *data;
	struct _MapInternalNode *pNextNode;
}MapInternalNode, *LPMapInternalNode;

typedef LPMapInternalNode MapIter;


typedef struct _Map{
	LPMapInternalNode pHead;
	unsigned int keySize;
	unsigned int dataSize;
	Less keyLess;
	Printer keyPrinter;
	Printer dataPrinter;
}Map, *LPMap;

enum BOOL createMap(LPMap *ppMap,
	            unsigned int keySize,
		    unsigned int dataSize,
		    Less keyLess, 
		    Printer keyPrinter,
		    Printer dataPrinter);
void destroyMap(LPMap *ppMap);

enum BOOL isMapEmpty(const LPMap pMap);
unsigned int getSizeOfMap(const LPMap pMap);

enum BOOL getElementAtInMap(const LPMap pMap,
			    const void *key,
			    void *data);

enum BOOL insertToMap(LPMap pMap,
	              const void *key,
		      const void *data);
enum BOOL eraseFromMap(LPMap pMap,
		       MapIter iter);
enum BOOL removeFromMap(LPMap pMap,
			const void *key);

MapIter findInMap(LPMap pMap, const void *key);
unsigned int countInMap(LPMap pMap, const void *key);







#endif
