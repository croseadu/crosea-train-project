#ifndef _MY_MAP_H
#define _MY_MAP_H

#include <stdio.h>
#include <string.h>
#include "mytype.h"


typedef struct _Map
{
  char * keyPool;
  char * valPool;
  unsigned int sizeOfKey;
  unsigned int sizeOfVal;

  unsigned int size;
  unsigned int capacity;
  
  CompareFunc keyEqual;
  PrintFunc keyPrint;
  PrintFunc valPrint;
}Map, *LPMap;

#define INIT_MAP_SIZE 10
#define INCRE_MAP_SIZE 5

bool initMap(LPMap *ppMap, unsigned int sizeOfKey,
	     unsigned int sizeOfVal,
	     CompareFunc keyEq,
	     PrintFunc printKey,
	     PrintFunc printVal)
{
  LPMap pMap;

  pMap = (LPMap)malloc(sizeof(Map));
  if (NULL == pMap) {
    printf ("Out Of Memory in %s", __func__);
    return false;
  }
  pMap->keyPool = (char *)malloc(sizeOfKey * INIT_MAP_SIZE);
  pMap->valPool = (char *)malloc(sizeOfKey * INIT_MAP_SIZE);
  if (NULL == pMap->keyPool || NULL == pMap->valPool) {
    free (pMap);
    printf ("Out Of Memory in %s", __func__);
    return false;
  } 
  pMap->sizeOfKey = sizeOfKey;
  pMap->sizeOfVal = sizeOfVal;
  pMap->size = 0;
  pMap->capacity = INIT_MAP_SIZE;
  pMap->keyPrint = printKey;
  pMap->valPrint = printVal;
  pMap->keyEqual = keyEq;
  *ppMap = pMap;
  return true;
}

bool insertEntry(LPMap pMap, void *key, void * val)
{
  if (pMap->size >= pMap->capacity) {
    pMap->keyPool = realloc(pMap->keyPool, 
			    (pMap->capacity+INCRE_MAP_SIZE) *
			    pMap->sizeOfKey);
    pMap->valPool = realloc(pMap->valPool, 
			    (pMap->capacity+INCRE_MAP_SIZE) *
			    pMap->sizeOfVal);
    if (NULL == pMap->keyPool ||
	NULL == pMap->valPool) {
      printf ("Out Of Memory in %s", __func__);
      return false;
    }
    pMap->capacity += INCRE_MAP_SIZE;
 }

  memcpy(pMap->keyPool + pMap->size*pMap->sizeOfKey,
	 key, pMap->sizeOfKey);
  memcpy(pMap->valPool + pMap->size*pMap->sizeOfVal,
	 val, pMap->sizeOfVal);
  ++pMap->size;
  return true;
}

bool insertOrModifyEntry(LPMap pMap, void *key, void * val)
{
  int i;
  for (i = 0; i < pMap->size; ++i)
    if (pMap->keyEqual(key, pMap->keyPool+i*pMap->sizeOfKey))
      break;
  if (i >= pMap->size)
    return insertEntry(pMap, key, val);
  memcpy(pMap->valPool+i*pMap->sizeOfVal, val, pMap->sizeOfVal);
  return true;
}  

bool findValueViaKey(LPMap pMap, void * key, void * val)
{
  int i;
  for (i = 0; i < pMap->size; ++i)
    if (pMap->keyEqual(key, pMap->keyPool+i*pMap->sizeOfKey))
      break;
  if (i >= pMap->size)
    return false;
  memcpy(val, pMap->valPool+i*pMap->sizeOfVal, pMap->sizeOfVal);
  return true;
}

void eraseEntry(LPMap pMap, void * key)
{
  int i;
  for (i = 0; i < pMap->size; ++i)
    if (pMap->keyEqual(key, pMap->keyPool+i*pMap->sizeOfKey))
      break;
  if (i >= pMap->size) {
    printf ("Wrong Key in %s", __func__);
    return;
  }
  --pMap->size;
  for (;i <pMap->size; ++i) {
    memcpy(pMap->keyPool+i*pMap->sizeOfKey,
	   pMap->keyPool+(i+1)*pMap->sizeOfKey,
	   pMap->sizeOfKey);
    memcpy(pMap->valPool+i*pMap->sizeOfVal,
	   pMap->valPool+(i+1)*pMap->sizeOfVal,
	   pMap->sizeOfVal);
  
  }
}

void destroyMap(LPMap *ppMap)
{
  free ((*ppMap)->keyPool);
  free ((*ppMap)->valPool);
  free (*ppMap);
}


#endif
