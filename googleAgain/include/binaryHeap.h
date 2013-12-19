#ifndef _MY_HEAP_H
#define _MY_HEAP_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mytype.h"



typedef struct _Binary_Heap {
  char *data;
  unsigned int size;
  unsigned int elementSize;

  CompareFunc less;
  CompareFunc equal;
  unsigned int capacity; 
}BinaryHeap, *LPBinaryHeap;


#define INIT_HEAP_SIZE 10
#define INCRE_HEAP_SIZE 5

bool initBinaryHeap(LPBinaryHeap *ppHeap, unsigned int elementSize, CompareFunc less, CompareFunc equal)
{
  LPBinaryHeap pHeap = NULL;

  pHeap = (LPBinaryHeap)malloc(sizeof(BinaryHeap));
  if (NULL == pHeap) {
    printf ("Out Of Memory in %s", __func__);
    return false;
  }

  pHeap->data = (char *)malloc(elementSize * INIT_HEAP_SIZE);
  if (NULL == pHeap->data) {
    free (pHeap);
    printf ("Out Of Memory in %s", __func__);
    return false;
  }
  pHeap->size = 0;
  pHeap->elementSize = elementSize;
  pHeap->less = less;
  pHeap->equal = equal;
  pHeap->capacity = INIT_HEAP_SIZE;


  *ppHeap = pHeap;
  return true;
}

bool destroyBinaryHeap(LPBinaryHeap *ppHeap) 
{
  free ((*ppHeap)->data);
  free (*ppHeap);
  *ppHeap = NULL;
}

bool isBinaryHeapEmpty(LPBinaryHeap pHeap)
{
  return pHeap->size == 0;
}

void peekBinaryHeap(LPBinaryHeap pHeap, void *out)
{
  memcpy(out, pHeap->data, pHeap->elementSize);
}
void removeRootFromBinaryHeap(LPBinaryHeap pHeap)
{
  int i, j;
  int n;
  char *pTemp;

  pTemp = (char *)malloc(pHeap->elementSize);
  memcpy(pTemp, 
	 pHeap->data+(pHeap->size-1)*pHeap->elementSize, 
	 pHeap->elementSize);
  --pHeap->size;
  n = pHeap->size;
  
  
  for (i = 0, j = 1; j < n;) {
    if (i > 0 && j+1 < n && 
	pHeap->less(pHeap->data+(j+1)*pHeap->elementSize, 
		    pHeap->data+j*pHeap->elementSize))
      ++j;
    if (pHeap->less(pHeap->data+j*pHeap->elementSize, pTemp)) {
      memcpy (pHeap->data+i*pHeap->elementSize,
	      pHeap->data+j*pHeap->elementSize,
	      pHeap->elementSize);
      i = j;
      j = j*2;
    }
    else
      break;
  }
  memcpy(pHeap->data+i*pHeap->elementSize,
	 pTemp,
	 pHeap->elementSize);
  free (pTemp);
}

void increaseRankOnBinaryHeap(LPBinaryHeap pHeap, void *old, void * new)
{
  int i, j, n;
  n = pHeap->size;
  
  for (i = 0; i < n; ++i) {
    if (pHeap->equal(pHeap->data+i*pHeap->elementSize,
		     old)) 
      break;
  }

  j = i;
  while (j >= 0) {
    if (pHeap->less(new, pHeap->data+j*pHeap->elementSize)) {
      
      memcpy(pHeap->data+i*pHeap->elementSize, 
	     pHeap->data+j*pHeap->elementSize,
	     pHeap->elementSize);
      i = j;
      if (j == 0)
	--j;
      else
	j /= 2;
    }
    else
      break;
  }
  memcpy(pHeap->data+i*pHeap->elementSize, new, pHeap->elementSize);
}


void insertKeyToBinaryHeap(LPBinaryHeap pHeap, void *in)
{
  int i = 0;
  int j = pHeap->size;

  if (pHeap->size >= pHeap->capacity) {
    pHeap->data = realloc(pHeap->data, 
			  (pHeap->capacity+INCRE_HEAP_SIZE)*pHeap->elementSize);
    if (NULL == pHeap->data) {
      printf("Out Of Memory in %s", __func__);
      return;
    }
    pHeap->capacity += INCRE_HEAP_SIZE;
  }
  
  if (pHeap->size == 0) {
    memcpy(pHeap->data, in, pHeap->elementSize);
    ++pHeap->size;
    return ;
  }
  i = j/2;
  while (i >= 0 && pHeap->less(in,pHeap->data + i * pHeap->elementSize)) {
    memcpy(pHeap->data + j*pHeap->elementSize,
	   pHeap->data + i*pHeap->elementSize,
	   pHeap->elementSize);
    j = i;
    if (i > 0)
      i = i/2;
    else
      --i;
  }
  memcpy(pHeap->data + j * pHeap->elementSize,
	 in, pHeap->elementSize);
  ++pHeap->size;
}

bool validateBinaryHeap(LPBinaryHeap pHeap)
{
  int i = 0;
  int n = pHeap->size;
  if (n <= 1)
    return true;
  for (i = 0; i <= (n-1)/2;++i) {
    if (pHeap->less(pHeap->data + 2*i* pHeap->elementSize,
		    pHeap->data + i * pHeap->elementSize)) {
      printf("\nInvalid i:%d, j:%d", i, 2*i);
      return false;
    }
    if (2*i+1 < n)
      if (pHeap->less(pHeap->data + (2*i+1)* pHeap->elementSize,
		      pHeap->data + i * pHeap->elementSize)) {
	printf("\nInvalid i:%d, j:%d", i, 2*i+1);
	return false;
      }
  }
  return true;
}

void dumpBinaryHeap(LPBinaryHeap pHeap, VisitFunc printer)
{
  int i;
  printf("Heap:\n");
  int k = 0;
  for (i = 0; i < pHeap->size; ++i) {
    printf("[%2d]", i);
    printer(pHeap->data+i*pHeap->elementSize);
    ++k;
    if (k%6 == 0)
      putchar('\n');
  }
  putchar('\n');
}

void createBinaryHeapFromArray(LPBinaryHeap pHeap, char * array, unsigned int arraySize)
{
  int i,j,k;
  char *pTemp;

  if (pHeap->capacity < arraySize) {
    pHeap->data = realloc(pHeap->data, arraySize*pHeap->elementSize);
    if (NULL == pHeap->data) {
      printf ("Out OF Memory in %s", __func__);
      return ;
    }
    pHeap->capacity = arraySize;
  }
  
  pTemp = (char *)malloc(pHeap->elementSize);
  if (NULL == pTemp) {
    printf ("Out Of Memory in %s", __func__);
    return ;
  }
  
  memcpy (pHeap->data, array, arraySize * pHeap->elementSize);
  pHeap->size = arraySize;
  i = pHeap->size/2;
  for(; i >= 0; --i) {
    k = i;
    j = 2*k;
    memcpy (pTemp, pHeap->data + i * pHeap->elementSize, pHeap->elementSize);
    for (;j < pHeap->size;) {
      if (j+1 < pHeap->size &&
	  pHeap->less(pHeap->data + (j+1)*pHeap->elementSize,
		      pHeap->data + j * pHeap->elementSize))
	++j;
      if (pHeap->less(pTemp, pHeap->data+j*pHeap->elementSize))
	break;
      memcpy (pHeap->data + k * pHeap->elementSize,
	      pHeap->data + j * pHeap->elementSize,
	      pHeap->elementSize);
      k = j;
      j *= 2;
    }
    memcpy(pHeap->data + k * pHeap->elementSize, 
	   pTemp, pHeap->elementSize);
  }

  free (pTemp);
}
#endif
