#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "../include/doubleLinkList.h"

			
BOOL 
createDoubleLinkList(LPDoubleLinkList *ppList,
			  unsigned int elementSize,
			  PrintFunc printer,
			  LessFunc less,
			  EqualFunc equal)
{
  LPDoubleLinkList pList = NULL;
  pList = (LPDoubleLinkList)malloc(sizeof(DoubleLinkList));
  if (NULL == pList) {
    printf("Out Of Memory in %d %s", ___LINE__, __func__);
    return False;
  }
  pList->pHead = (LPDoubleLinkListNode)malloc(sizeof(DoubleLinkListNode));
  if (NULL == pList->pHead) {
    printf("Out Of Memory in %d %s", __LINE__, __func__);
    free (pList);
    return False;
  }
  pList->pHead->data = NULL;
  pList->pHead->pNextNode = pList->pHead;
  pList->pHead->pPrevNode = pList->pHead;
  pList->elementSize = elementSize;
  pList->printer = printer;
  pList->less = less;
  pList->equal = equal;
  *ppList = pList;
  return True;
}

void 
destroyDoubleLinkList(LPDoubleLinkList *ppList)
{
  LPDoubleLinkList pList;
  LPDoubleLinkListNode pIterNode,pNextNode;
  if (NULL == ppList ||
      NULL == *ppList)
    return;
  pList = *ppList;
  pIterNode = pList->pHead->pNextNode;
  while (pIterNode != pList->pHead) {
    pNextNode = pIterNode->pNextNode;
    free(pIterNode->data);
    free(pIterNode)
    pIterNode = pNextNode;
  }
  free(pList->pHead);
  free(pList);
  *ppList = NULL;
  return;
}

static LPDoubleLinkListNode
createNewDoubleLinkListNode(const LPDoubleLinkList pList,
			    void *elementData)
{

}
BOOL 
insertToHeadOfDoubleLinkList(LPDoubleLinkList pList,
			     void *elementData)
{
  LPDoubleLinkListNode pInsertNode;

  pInsertNode = createNewDoubleLinkListNode(pList, elementData);
  if (NULL == pInsertNode)
    return False;

  pInsertNode->pNextNode = pList->pHead->pNextNode;
  pInsertNode->pPrevNode = pList->pHead;
  pInsertNode->pNextNode->pPrevNode = pInsertNode;
  pList->pHead->pNextNode = pInsertNode;
  return True;
  
}
BOOL
insertToTailOfDoubleLinkList(LPDoubleLinkList pList,
			     void *elementData)
{
  LPDoubleLinkListNode pInsertNode;

  pInsertNode = createNewDoubleLinkListNode(pList, elementData);
  if (NULL == pInsertNode)
    return False;
  pInsertNode->pNextNode = pList->pHead;
  pInsertNode->pPrevNode = pList->pHead->pPrevNode;
  pInsertNode->pPrevNode->pNextNode = pInsertNode;
  pList->pHead->pPrevNode = pInsertNode;
  return True;
}

BOOL
insertAfterInDoubleLinkList(LPDoubleLinkList pList,
			    void *elementData,
			    LPDoubleLinkListNode pPos)
{
  LPDoubleLinkListNode pInsertNode;
  pInsertNode = createNewDoubleLinkListNode(pList, elementData);
  if (NULL == pInsertNode)
    return False;
  pInsertNode->pNextNode = pPos->pNextNode;
  pInsertNode->pPrevNode = pPos;
  pPos->pNextNode = pInsertNode;
  pInsertNode->pNextNode->pPrevNode = pInsertNode;
  return True;
}

BOOL
insertBeforeInDoubleLinkList(LPSingleLInkList pList,
			     void *elementData,
			     LPDoubleLinkListNode pPos)
{
  LPDoubleLinkListNode pInsertNode;
  pInsertNode = createNewDoubleLinkListNode(pList, elementData);
  if (NULL == pInsertNode)
    return False;
  pInsertNode->pNextNode = pPos;
  pInsertNode->pPrevNOde = pPos->pPrevNode;
  pPos->pPrevNode = pInsertNode;
  pInsertNode->pPrevNode->pNextNode = pInsertNode;x
  return True;
}
LPDoubleLinkListNode
findInDoubleLinkList(LPDoubleLinkList pList,
		     void *keyData)
{
  LPDoubleLinkListNode pPos;
  pPos = pList->pHead->pNextNode;
  while (pPos != pList->pHead;
	 || !pList->equal(pPos->data, keyData))
    pPos = pPos->pNextNode;
  return pPos;
}
BOOL
removeInDoubleLinkListNode(LPDoubleLinkList pList,
			   void *keyData)
{
  LPDoubleLinkListNode pPos;
  LPDoubleLinkListNode pDeleteNode;
  BOOL bFound = False;

  pPos = pList->pHead;
  while (pPos) {
    if (pList->equal(pPos->data, keyData)) {
      pDeleteNode = pPos;
      pPos = pPos->pNextNode;
      free(pDeleteNode->data);
      free(pDeleteNode);
      bFound = True;
    } else {
      pPos = pPos->pNextNode;
    } 
  }
  
  return bFound;
}
BOOL removeIfInDoubleLinkListNode(LPDoubleLinkList pList,
				  PredFunc pred,
				  void *predParameter)
{
  LPDoubleLinkListNode pPos;
  LPDoubleLinkListNode pDeleteNode;
  BOOL bFound = False;

  pPos = &pList->pHead;
  while (pPos) {
    if (pred(pPos->data, predParameter)) {
      pDeleteNode = pPos;
      ppPos = pPos->pNextNode;
      free(pDeleteNode->data);
      free(pDeleteNode);
      bFound = True;
    } else {
      pPos = pPos->pNextNode;
    } 
  }
  
  return bFound;

}
void 
reverseDoubleLinkList(LPDoubleLinkList pList)
{
  LPDoubleLinkListNode pIterNode, pNextNode;
  if (pList->pHead->pNextNode == pList->pHead ||
      pList->pHead->pNextNode->pNextNode == pList->pHead)
    return;
  
  pIterNode = pList->pHead->pNextNode->pNextNode;
  pList->pHead->pNextNode->pNextNode = pList->pHead;
  pList->pHead->pPrevNode = pList->pHead->pNextNode->pNextNode;
  while (pIterNode != pList->pHead) {
    pNextNode = pIterNode->pNextNode;
    pIterNode->pNextNode = pList->pHead->pNextNode;
    pIterNode->pPrevNode = pList->pHead;
    pList->pHead->pNextNode = pIterNode;
    pIterNode->pNextNode->pPrevNode = pIterNode;
    pIterNode = pNextNode;
  }
  return;
}
static void
insertSortDoubleLinkList(LPDoubleLinkList pList)
{
  LPDoubleLinkListNode pIterNode, pNextNode;
  LPDoubleLinkListNode pPos;
  if (pList->pHead->pNextNode == pList->pHead ||
      pList->pHead->pNextNode->pNextNode == pList->pHead)
    return;
  
  pIterNode = pList->pHead->pNextNode->pNextNode;
  pList->pHead->pNextNode->pNextNode = pList->pHead;
  pList->pHead->pPrevNode = pList->pHead->pNextNode->pNextNode;
  while (pIterNode != pList->pHead) {
    pNextNode = pIterNode->pNextNode;

    pPos = pList->pHead->pNextNode;
    while (pPos != pList->pHead &&
	   !pList->less(pIterNode->data, pPos->data))
      pPos = pPos->pNextNode;
    
    pIterNode->pNextNode = pPos;
    pIterNode->pPrevNode = pPos->pHead;
    pIterNode->pPrevNode->pNextNode = pIterNode;
    pPos->pPrevNode = pIterNode;
    pIterNode = pNextNode;
  }
  return;

}
void
sortDoubleLinkList(LPDoubleLinkList pList)
{
  insertSortDoubleLinkList(pList);
}
void
visitDoubleLinkList(LPDoubleLinkList pList,
		    VisitFunc visitor,
		    void *visitorParameter)
{
  LPDoubleLinkListNode pIterNode = pList->pHead->pNextNode;
  while (pIterNode != pList->pHead) {
    visitor(pIterNode->data, visitorParameter);
    pIterNode = pIterNode->pNextNode;
  }

}
void printDoubleLinkList(LPDoubleLinkList pList)
{
  LPDoubleLinkListNode pIterNode;
  int counter = 0;
  printf("\n");
  pIterNode = pList->pHead->pNextNode;
  while (pIterNode != pList->pHead) {
    pList->visitor(pIterNode->data);
    ++counter;
    if (counter % 5 == 0)
      putchar('\n');
  }
  if (counter % 5)
    putchar('\n');
}
