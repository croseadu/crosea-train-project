#ifndef _MY_SET_H
#define _MY_SET_H

#include <stdlib.h>
#include <string.h>
#include "mytype.h"

typedef struct _SET
{
  char *data;
  unsigned int count;
  unsigned int capacity;
  unsigned int elementSize;

  PrintFunc printer;
  CompareFunc equal;
}Set, *LPSet;

#define INIT_SET_SIZE 5
#define INCRE_SET_SIZE 5

bool initSet(LPSet *ppSet, unsigned int elementSize, PrintFunc printer, CompareFunc eq)
{
  LPSet pSet;
  
  pSet = (LPSet)malloc(sizeof(Set));
  if (NULL == pSet) {
    printf ("Out Of Memory in %s", __func__);
    return false;
  }

  pSet->data = (char *)malloc(elementSize * INIT_SET_SIZE);
  if (NULL == pSet->data) {
    printf ("Out Of Memory in %s", __func__);
    free (pSet);
    return false;
  }

  pSet->elementSize = elementSize;
  pSet->count = 0;
  pSet->capacity = INIT_SET_SIZE;
  
  *ppSet = pSet;
  return true;
}



bool countInSet(LPSet pSet, void *key)
{
  int i = 0;
  for (i = 0; i < pSet->count; ++i)
    if (pSet->equal(pSet->data + pSet->elementSize*i, key))
      break;
  return i < pSet->count;
}

bool isSetEmpty(LPSet pSet)
{
  return pSet->count == 0;
}

bool insertToSet(LPSet, void *key)
{
  if (pSet->count >= pSet->capacity) {
    pSet->data = realloc(pSet->data, (pSet->capacity + INCRE_SET_SIZE)*pSet->elementSize);
    if (NULL == pSet->data) {
      printf ("Out Of Memory in %s", __func__);
      return false;
    }
    pSet->capacity += INCRE_SET_SIZE;
  }
  memcpy(pSet->data+pSet->elementSize*pSet->count, key, pSet->elementSize);
  ++pSet->count;
  return true;
}

void clearSet(LPSet pSet)
{
  pSet->count = 0;
}

void destorySet(LPSet *ppSet)
{
  free((*ppSet)->data);
  free(*ppSet);
}
#endif

