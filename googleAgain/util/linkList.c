#include "../include/linkList.h"



bool initLinkList(LPLinkList *ppList, unsigned int elementSize, PrintFunc printer, CompareFunc eq, CompareFunc less)
{
  LPLinkList pList;
  pList = (LPLinkList)malloc(sizeof(LinkList));
  if (NULL == pList) {
    printf("Out Of Memory in %s", __func__);
    return false;
  }

  pList->pHead = NULL;
  pList->elementSize = elementSize;
  pList->printer = printer;
  pList->equal = eq;
  pList->less = less;
  *ppList = pList;
  return true;
}

bool insertToLinkListHead(LPLinkList pList, void * pVal)
{
  Node *pNew = (Node *)malloc(sizeof(Node));
  if (NULL == pNew) {
    printf("Out of Memory in %s", __func__);
    return false;
  }
  pNew->pData = malloc(pList->elementSize);
  if (NULL == pNew->pData) {
    printf("Out of Memory in %s", __func__);
    free(pNew);
    return false;
  }
  memcpy(pNew->pData, pVal, pList->elementSize);
  pNew->pNext = pList->pHead;
  pList->pHead = pNew;
  return true;
}

bool insertToLinkListTail(LPLinkList pList, void *pVal)
{
  Node *pNew = (Node *)malloc(sizeof(Node));
  if (NULL == pNew) {
    printf("Out of Memory in %s", __func__);
    return false;
  }
  pNew->pData = malloc(pList->elementSize);
  if (NULL == pNew->pData) {
    printf("Out of Memory in %s", __func__);
    free(pNew);
    return false;
  }
  memcpy(pNew->pData, pVal, pList->elementSize);
  pNew->pNext = NULL;
  
  if (NULL == pList->pHead) {
    pList->pHead = pNew;
  }
  else {
    Node *pPos = pList->pHead;
    while (pPos->pNext)
      pPos = pPos->pNext;
    pPos->pNext = pNew;
  }  
  return true;
}

bool insertToLinkList(LPLinkList pList, void *pVal, Node *pInsertPos)
{
  Node *pNew = (Node *)malloc(sizeof(Node));
  if (NULL == pNew) {
    printf("Out of Memory in %s", __func__);
    return false;
  }
  pNew->pData = malloc(pList->elementSize);
  if (NULL == pNew->pData) {
    printf("Out of Memory in %s", __func__);
    free(pNew);
    return false;
  }
  memcpy(pNew->pData, pVal, pList->elementSize);
  
  pNew->pNext = pInsertPos->pNext;
  pInsertPos->pNext = pNew;
  return true;
}

void deleteNodeInLinkList(LPLinkList pList, Node *pDelete)
{
  Node **ppIter = &pList->pHead;
  while (*ppIter && *ppIter != pDelete)
    ppIter = &((*ppIter)->pNext);
  
  if (NULL == *ppIter) {
    printf("Delete Node doesn't exist in List %s", __func__);
    return ;
  }

  *ppIter = pDelete->pNext;
  free(pDelete);
}

unsigned int deleteValInLinkList(LPLinkList pList, void *val)
{
  int cnt = 0;
  Node **ppIter = &pList->pHead;
  while (*ppIter) {
    if (pList->equal((*ppIter)->pData, val)) {
      Node *pDelete = *ppIter;

      printf("\nDelete Node in List, val is :");
      pList->printer(pDelete->pData);
      *ppIter = pDelete->pNext;
      free(pDelete);
      ++cnt;
    }
    else
      ppIter = &((*ppIter)->pNext);
  }

  return cnt;
}

unsigned int deleteIfInLinkList(LPLinkList pList, PredFunc pred)
{
  int cnt = 0;
  Node **ppIter = &pList->pHead;
  while (*ppIter) {
    if (pred((*ppIter)->pData)) {
      Node *pDelete = *ppIter;

      printf("\nDelete Node in List, val is :");
      pList->printer(pDelete->pData);
      *ppIter = pDelete->pNext;
      free(pDelete);
      ++cnt;
    }
    else
      ppIter = &((*ppIter)->pNext);
  }

  return cnt;
}

void visitLinkList(LPLinkList pList, VisitFunc visitor)
{
  Node *pIter = pList->pHead;
  while (pIter) {
    visitor(pIter->pData);
    pIter = pIter->pNext;
  }
}

void printLinkList(LPLinkList pList)
{
  printf("\nLinkList :\n");
  visitLinkList(pList, pList->printer);
}


static void insertSortLinkList(LPLinkList pList)
{
  Node *pHead = pList->pHead, *pIter, *pNext;
  
  if (NULL == pHead || NULL == pHead->pNext)
    return;

  pIter = pHead->pNext;
  pHead->pNext = NULL;
  while (pIter) {
    Node **ppPos = &pList->pHead;
    while (*ppPos && pList->less((*ppPos)->pData, pIter->pData))
      ppPos = &((*ppPos)->pNext);
    
    pNext = pIter->pNext;

    pIter->pNext = *ppPos;
    *ppPos = pIter;
    pIter = pNext;
  }
  
}


void sortLinkList(LPLinkList pList)
{
  insertSortLinkList(pList);
}

void reverseLinkList(LPLinkList pList)
{
  Node *pHead = pList->pHead, *pIter, *pNext;
  
  if (NULL == pHead || NULL == pHead->pNext)
    return;
  
  pIter = pHead->pNext;
  pHead->pNext = NULL;
  
  while (pIter) {
    pNext = pIter->pNext;
    pIter->pNext = pHead;
    pHead = pIter;
    pIter = pNext;
  }
  pList->pHead = pHead;
}

void clearLinkList(LPLinkList pList)
{
  Node *pIter = pList->pHead, *pNext;
  
  while (pIter) {
    pNext = pIter->pNext;
    free(pIter->pData);
    free(pIter);
    pIter = pNext;
  }
}

void destroyLinkList(LPLinkList *ppList)
{
  if ((*ppList)->pHead)
    clearLinkList(*ppList);
  free(*ppList);
  *ppList = NULL;
}





