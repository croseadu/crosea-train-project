#ifndef _MY_BITSET_H
#define _MY_BITSET_H
#include "mytype.h"

typedef struct _MY_BIT_SET
{
  unsigned int *data;
  unsigned int byteSize;
  //unsigned int count;
}BitSet, *LPBitSet;

bool initBitSet(LPBitSet *ppSet, unsigned int maxElement)
{
  LPBitSet pSet = NULL;
  unsigned int bytes;

  pSet = (LPBitSet)malloc(sizeof(BitSet));
  if (NULL == pSet) {
    printf("Out Of Memory in %s", __func__);
    return false;
  }
  
  bytes = maxElement/sizeof(unsigned int);
  if (maxElement%sizeof(unsigned int) == 0)
    ++bytes;
  pSet->data = (unsigned int *)mallc(sizeof(unsigned int)*bytes);
  if (NULL == pSet->data) {
    printf("Out Of Memory in %s", __func__);
    free(pSet);
    return false;
  }
  pSet->byteSize = bytes;
  *ppSet = pSet;
  return true;
}

bool testInBitSet(LPBitSet pSet, unsigned int pos)
{
  unsigned int words, bits;
  words = pos/sizeof(unsigned int);
  bits = pos%sizeof(unsigned int);
  return pSet->data[words] & (1<<bits);
}
void setInBitSet(LPBitSet pSet, unsigned int pos)
{
  unsigned int words, bits;
  words = pos/sizeof(unsigned int);
  bits = pos%sizeof(unsigned int);
  pSet->data[words] |= (1<<bits);
}
void resetInBitSet(LPBitSet pSet, unsigned int pos)
{
  unsigned int words, bits;
  words = pos/sizeof(unsigned int);
  bits = pos%sizeof(unsigned int);
  pSet->data[words] &= ~(1<<bits);
}
bool anyInBitSet(LPBitSet pSet)
{
  int i;
  for (i = 0; i < pSet->byteSize; ++i) {
    if (pSet->data[i])
      return true;
  }
  return false;
}
void destroyBitSet(LPBItSet *ppSet)
{
  if (*ppSet != NULL) {
    free((*ppSet)->data);
    free(*ppSet);
    *ppSet = NULL;
  }
}

#endif
