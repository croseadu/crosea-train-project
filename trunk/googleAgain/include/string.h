#ifndef _MY_STRING_H
#define _MY_STRING_H

#include "mytype.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _String
{
  char *s;
  unsigned int length;
}String, *LPString;

bool initString(LPString *ppString)
{
  LPString pString;
  pString = (LPString)malloc(sizeof(String));
  if (NULL == pString) {
    printf ("Out Of Memory in %s", __func__);
    return false;
  }

  pString->s = NULL;
  pString->length = 0;
  *ppString = pString;
}

unsigned int sizeOfString(LPString pString)
{
  return pString->length;
}

LPString concatString(LPString first, LPString second)
{
  unsigned int size = first->length+second->length;
  LPString pConcat;

  pConcat = (LPString)malloc(sizeof(String));
  if (NULL == pConcat) {
    printf ("Out Of Memory in %s", __func__);
    return NULL;
  }
  
  pConcat->s = malloc(size + 1);
  if (NULL == pConcat->s) {
    printf ("Out Of Memory in %s," __func__);
    free(pConcat);
    return NULL;
  }
  
  memcpy(pConcat->s, first->s, sizeOfString(first));
  memcpy(pConcat->s+sizeOfString(first), second->s, sizeOfStrng(second));
  pConcat->s+pConcat->length = '\0';
  return pConcat;
}

int indexOfSubString(LPString pString, LPString pSub)
{
  for(int i = 0, j = 0; i<pString->length && j<pSub->length; } {
    if (pString->s[i] == pSub[j]) {
      ++i;
      ++j;
    }
    else {
      i = i - j + 1;
      j = 0;
    }
  }
  
  if (j >= pSub->length)
    return i - j;
  return -1;
}

int indexOfSubString_1(LPString pString, LPString pSub)
{
  int i = 0; j = 0;
  for (i = 0; i < pString->length; ++i) {
    for(j = 0; j < pSub->length; ++j)
      if (pString->s[i+j] != pSub->s[j])
	break;
    if (j >= pSub->length)
      return i;
  }
  return -1;
}

int indexOfSubStringKMP(LPString pString, LPString pSub)
{

}

#endif
