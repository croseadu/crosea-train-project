#ifndef _MY_MAP_H
#define _MY_MAP_H

#include "common.h"

#include "singleLinkList.h"
 
typedef struct _MAP_ENTRY
{
  void *Key;
  void *Value;
}MapEntry, *LPMapEntry;

typedef struct _MAP
{
  LPSingleLinkList pMapEntry;
  
  unsigned int keySize;
  unsigned int valueSize;
  CompareFunc  less;
}Map, *LPMap;

BOOL initMap(LPMap *, unsigned int , unsigned int, CompareFunc);
BOOL destroyMap(LPMap *);

BOOL insertToMap(LPMap, void *key, void *value);
BOOL eraseFromMap(LPMap, void *key);
BOOL eraseFromMap(LPMap, MapIterator);
MapIterator findInMap(LPMap, void *key);
unsigned int countInMap(LPMap, void* key);


#endif
