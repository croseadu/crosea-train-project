#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/doubleLinkList.h"


bool initDoubleLinkList(LPDoubleLinkList *ppList, unsigned int elementSize, PrintFunc printer, CompareFunc eq, CompareFunc less)
{
  LPDoubleLinkList pList;
  LPDoubleLinkListNode pNode;

  pList = (LPDoubleLinkList)malloc(sizeof(DoubleLinkList));
  if (NULL == pList) {
    printf ("Out of Memory in %s", __func__);
    return false;
  }
  
  pNode = (LPDoubleLinkListNode)malloc(sizeof(DoubleLinkListNode));
  if (NULL == pNode) {
    printf ("Out Of Memory in %s", __func__);
    free(pList);
    return false;
  }
  
  pNode->pPrev = pNode->pNext = pNode;
  pNode->pData = NULL;

  pList->pHead = pNode;
  pList->elementSize = elementSize;
  pList->printer = printer;
  pList->equal = eq;
  pList->less = less;
  *ppList = pList;
  return true;
}
bool insertToDoubleLinkListHead(LPDoubleLinkList pList, void * pVal)
{
  return insertToDoubleLinkList(pList, pVal, pList->pHead);
}
bool insertToDoubleLinkListTail(LPDoubleLinkList pList, void *pVal)
{
  if (pList->pHead->pNext == pList->pHead)
    return insertToDoubleLinkList(pList, pVal, pList->pHead);

  return insertToDoubleLinkList(pList, pVal, pList->pHead->pPrev);
}
bool insertToDoubleLinkList(LPDoubleLinkList pList, void *pVal, DoubleLinkListNode *pInsertPos)
{
  LPDoubleLinkListNode pNew;
  
  pNew = (LPDoubleLinkListNode)malloc(sizeof(DoubleLinkListNode));
  if (NULL == pNew) {
    printf ("Out Of Memory in %s", __func__);
    return false;
  }

  pNew->pData = malloc(pList->elementSize);
  if (NULL == pNew->pData) {
    printf ("Out Of Memor yin %s", __func__);
    free(pNew);
    return false;
  }

  memcpy(pNew->pData, pVal, pList->elementSize);
  
  pNew->pNext = pInsertPos->pNext;
  pNew->pPrev = pInsertPos;
  
  pInsertPos->pNext = pNew;
  pNew->pNext->pPrev = pNew;
  return true;
}
void deleteNodeInDoubleLinkList(LPDoubleLinkList pList, DoubleLinkListNode *pDelete)
{
  pDelete->pNext->pPrev = pDelete->pPrev;
  pDelete->pPrev->pNext = pDelete->pNext;
  free(pDelete->pData);
  free(pDelete);
}
unsigned int deleteValInDoubleLinkList(LPDoubleLinkList pList, void *val)
{
  LPDoubleLinkListNode pIter, pNext;
  unsigned int cnt = 0;

  pIter = pList->pHead->pNext;
  while (pIter != pList->pHead) {
    pNext = pIter->pNext;
    if (pList->equal(val, pIter->pData)) {
      free(pIter->pData);
      pIter->pPrev->pNext = pIter->pNext;
      pIter->pNext->pPrev = pIter->pPrev;
      free(pIter);
      
      ++cnt;
    }
    pIter = pNext;
  }

  return cnt;
}
unsigned int deleteIfInDoubleLinkList(LPDoubleLinkList pList, PredFunc pred)
{
  LPDoubleLinkListNode pIter, pNext;
  unsigned int cnt = 0;

  pIter = pList->pHead->pNext;
  while (pIter != pList->pHead) {
    pNext = pIter->pNext;
    if (pred(pIter->pData)) {
      free(pIter->pData);
      pIter->pPrev->pNext = pIter->pNext;
      pIter->pNext->pPrev = pIter->pPrev;
      free(pIter);
      
      ++cnt;
    }
    pIter = pNext;
  }

  return cnt;
 
}
void visitDoubleLinkList(LPDoubleLinkList pList, VisitFunc visitor)
{
  LPDoubleLinkListNode pIter = pList->pHead->pNext;
  while (pIter != pList->pHead) {
    visitor(pIter->pData);
    pIter = pIter->pNext;
  }
}
void printDoubleLinkList(LPDoubleLinkList pList)
{
  printf("\nDoubleLinkList :\n");
  visitDoubleLinkList(pList, pList->printer);
}
void clearDoubleLinkList(LPDoubleLinkList pList)
{
  LPDoubleLinkListNode pIter, pNext;

  pIter = pList->pHead->pNext;
  while (pIter != pList->pHead) {
    pNext = pIter->pNext;
    free(pIter->pData);
    free(pIter);
    pIter = pNext;
  }
  pList->pHead->pPrev = pList->pHead->pNext = pList->pHead;
}

static void insertSortDoubleLinkList(LPDoubleLinkList pList)
{
  LPDoubleLinkListNode pIter, pNext, pPos;

  pIter = pList->pHead->pNext;
  
  if (pIter == pList->pHead || pIter->pNext == pList->pHead)
    return;

  pIter = pIter->pNext;
  pIter->pPrev->pNext = pList->pHead;
  pList->pHead->pPrev = pIter->pPrev;

  while (pIter != pList->pHead) {
    pNext = pIter->pNext;
    pPos = pList->pHead;
    while (pPos->pNext != pList->pHead 
	   && pList->less(pPos->pNext->pData, pIter->pData))
      pPos = pPos->pNext;
    
    pIter->pNext = pPos->pNext;
    pIter->pPrev = pPos;
    pPos->pNext = pIter;
    pIter->pNext->pPrev = pIter;
    
    pIter = pNext;
  }
}

void sortDoubleLinkList(LPDoubleLinkList pList)
{
  insertSortDoubleLinkList(pList);
}
void reverseDoubleLinkList(LPDoubleLinkList pList)
{
  LPDoubleLinkListNode pIter, pNext;
  
  pIter = pList->pHead->pNext;
  pList->pHead->pPrev = pList->pHead->pNext = pList->pHead;

  while (pIter != pList->pHead) {
    pNext = pIter->pNext;
    pIter->pNext = pList->pHead->pNext;
    pIter->pPrev = pList->pHead;
    pIter->pNext->pPrev = pIter;
    pList->pHead->pNext = pIter;
    pIter = pNext;
  }
}
void destroyDoubleLinkList(LPDoubleLinkList *ppList)
{
  free((*ppList)->pHead);
  free(*ppList);
  *ppList = NULL;
}
