#include "list.h"
#include <stdio.h>


bool initList(LPList *ppList, unsigned elementSize, PrintFunc printer)
{
  LPList pHead = malloc(sizeof(List));
  if (NULL == pHead)
    return false;
  pHead->data = malloc(elementSize * LIST_INIT_SIZE);
  if (NULL == pHead->data){
    free(pHead);
    return false;
  }

  pHead->elementSize = elementSize;
  pHead->capacity = LIST_INIT_SIZE;
  pHead->size = 0;
  pHead->printer = printer;
  *ppList = pHead;
  return true;
}

static bool reserve(LPList pList)
{
  if (pList->size >= pList->capacity)
    {
      char *pNewBuffer = realloc(pList->data,
				 (pList->capacity+LIST_INCRE_SIZE)*pList->elementSize);
      if (NULL == pNewBuffer) {
	printf ("Out Of Memory in %s",__func__);
	return false;
      }
      pList->capacity += LIST_INCRE_SIZE;
      pList->data = pNewBuffer;
    }
  return true;
}

bool insertToListTail(LPList pList, void *val)
{

  if (!reserve(pList)) {
    return false;
  }

  memcpy(pList->data+pList->size*pList->elementSize, val, pList->elementSize);
  ++pList->size;
  return true;
}


bool insertToList(LPList pList, void *val, int insertPos)
{
  int i;
  if (insertPos == -1) {
    return insertToListTail(pList, val);
  }

  if (insertPos >= pList->size) {
    printf("InCorrect insert Pos!\n");
    return false;
  }

  if (!reserve(pList))
    return false;

  i = pList->size-1;
  while (i>= insertPos)
    {
      memcpy(pList->data+(i+1)*pList->elementSize,
	     pList->data+i*pList->elementSize,
	     pList->elementSize);
      --i;
    }

  memcpy(pList->data+pList->elementSize*insertPos, 
	 val, 
	 pList->elementSize);
  ++pList->size;
  return true;
}

bool insertToListHead(LPList pList, void *val)
{
  int i;
  int insertPos = 0;
  
  if (!reserve(pList))
    return false;

  i = pList->size-1;
  while (i>= insertPos)
    {
      memcpy(pList->data+(i+1)*pList->elementSize,
	     pList->data+i*pList->elementSize,
	     pList->elementSize);
      --i;
    }

  memcpy(pList->data+pList->elementSize*insertPos, 
	 val, 
	 pList->elementSize);
  ++pList->size;
  return true;
}

bool deleteListItem(LPList pList, int idx)
{
  int i;
  if (idx < 0 || idx >= pList->size) {
    printf("Invalid index for array in %s\n", __func__);
    return false;
  }
  
  i = idx;
  while (i < pList->size-1) {
    memcpy(pList->data+pList->elementSize * i,
	   pList->data+pList->elementSize * (i+1),
	   pList->elementSize);
    ++i;     
  }
  --pList->size;
  return true;
}


unsigned int deleteValInList(LPList pList, PredFunc pred)
{
  int deleteItem = 0;
  int i = 0, j = 0;
  while (i < pList->size) {
    if (!pred(pList->data+i*pList->elementSize)){
      if (i != j){
	memcpy(pList->data+j*pList->elementSize,
	       pList->data+i*pList->elementSize,
	       pList->elementSize);
      }
      ++j;
    }
    ++i;
  }
  deleteItem = pList->size - j;
  pList->size = j;
  return deleteItem;
}


void visitList(LPList pList, VisitFunc visitor)
{
  int i = 0;
  for (;i < pList->size; ++i)
    visitor(pList->data+i*pList->elementSize);
}



void printList(LPList pList)
{

  printf("List Size : %d\n", pList->size);
  if (pList->size)
    visitList(pList, pList->printer);
}

bool getItem(LPList pList, int idx, void *outVal)
{
  if (idx < 0 || idx >= pList->size) {
    printf("Invalid index for array in %s\n", __FUNCTION__);
    return false;
  }

  memcpy(outVal, pList->data+pList->elementSize*idx, pList->elementSize);
  return true;
}

int locateItem(LPList pList, PredFunc pred)
{
  int i = 0;
  for (; i < pList->size; ++i)
    if (pred(pList->data+i*pList->elementSize))
      return i;
  return -1;
}

void sortList(LPList pList,CompareFunc less)
{
  int i;
  char *pTemp = malloc(pList->elementSize);

  for (i =1; i < pList->size; i++)
    {
      if (less(pList->data+i * pList->elementSize, 
	       pList->data+pList->elementSize*(i-1)))
	{
	  int j = i-1;
	  getItem(pList, i, pTemp);
	  while (j >= 0 && less(pTemp, pList->data+j*pList->elementSize)) {
	    memcpy(pList->data+pList->elementSize * (j+1),
		   pList->data+pList->elementSize*j,
		   pList->elementSize);
	    --j;
	  }
	  memcpy(pList->data+pList->elementSize*(j+1),
		 pTemp,
		 pList->elementSize);
	}
    }

  free(pTemp);
}


void clearList(LPList pList)
{
  free(pList->data);
  pList->size = 0;
}

void destroyList(LPList *ppList)
{
  if ((*ppList)->size)
    clearList(*ppList);
  free(*ppList);
  *ppList = NULL;
}
