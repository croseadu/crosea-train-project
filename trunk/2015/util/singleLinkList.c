#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "../include/singleLinkList.h"

			
BOOL 
createSingleLinkList(LPSingleLinkList *ppList,
			  unsigned int elementSize,
			  PrintFunc printer,
			  LessFunc less,
			  EqualFunc equal)
{
  LPSingleLinkList pList = NULL;
  pList = (LPSingleLinkList)malloc(sizeof(SingleLinkList));
  if (NULL == pList) {
    printf("Out Of Memory in %d %s", ___LINE__, __func__);
    return False;
  }
  pList->pHead = NULL;
  pList->elementSize = elementSize;
  pList->printer = printer;
  pList->less = less;
  pList->equal = equal;
  *ppList = pList;
  return True;
}

void 
destroySingleLinkList(LPSingleLinkList *ppList)
{
  LPSingleLinkList pList;
  LPSingleLinkListNode pIterNode,pNextNode;
  if (NULL == ppList ||
      NULL == *ppList)
    return;
  pList = *ppList;
  pIterNode = pList->pHead;
  while (pIterNode) {
    pNextNode = pIterNode->pNextNode;
    free(pIterNode->data);
    free(pIterNode)
    pIterNode = pNextNode;
  }
  free(pList);
  *ppList = NULL;
  return;
}

static LPSingleLinkListNode
createNewSingleLinkListNode(const LPSingleLinkList pList,
			    void *elementData)
{

}
BOOL 
insertToHeadOfSingleLinkList(LPSingleLinkList pList,
			     void *elementData)
{
  LPSingleLinkListNode *ppStartNode;
  LPSingleLinkListNode pInsertNode;

  ppStartNode = &pList->pHead;
  pInsertNode = createNewSingleLinkListNode(pList, elementData);
  if (NULL == pInsertNode)
    return False;

  pInsertNode->pNextNode = (*ppStartNode)->pNextNode;
  *ppStartNode = pInsertNode;
  return True;
  
}
BOOL
insertToTailOfSingleLinkList(LPSingleLinkList pList,
			     void *elementData)
{
  LPSingleLinkListNode *ppLastNode;
  LPSingleLinkListNode pInsertNode;

  ppLastNode = &pList->pHead;
  while (*ppLastNode)
    ppLastNode = &(*ppLastNode)->pNextNode;
  pInsertNode = createNewSingleLinkListNode(pList, elementData);
  if (NULL == pInsertNode)
    return False;

  pInsertNode->pNextNode = NULL;
  *ppLastNode = pInsertNode;
  return True;
}

BOOL
insertAfterInSingleLinkList(LPSingleLinkList pList,
			    void *elementData,
			    SingleLinkListNodeIter iter)
{
  LPSingleLinkListNode pInsertNode;
  pInsertNode = createNewSingleLinkListNode(pList, elementData);
  if (NULL == pInsertNode)
    return False;
  pInsertNode->pNextNode = (*iter)->pNextNode;
  (*iter)->pNextNode = pInsertNode;
  return True;
}

BOOL
insertBeforeInSingleLinkList(LPSingleLInkList pList,
			     void *elementData,
			     SingleLinkListNodeIter iter)
{
  LPSingleLinkListNode pInsertNode;
  pInsertNode = createNewSingleLinkListNode(pList, elementData);
  if (NULL == pInsertNode)
    return False;
  pInsertNode->pNextNode = (*iter);
  *iter = pInsertNode;
  return True;
}
SingleLinkListNodeIter
findInSingleLinkList(LPSingleLinkList pList,
		     void *keyData)
{
  LPSingleLinkListNode *ppPos;
  ppPos = &pList->pHead;
  while (NULL != *ppPos
	 || !pList->equal((*ppPos)->data, keyData))
    ppPos = &(*ppPos)->pNextNode;
  return (SingleLinkListNodeIter)ppPos;
}
BOOL
removeInSingleLinkListNode(LPSingleLinkList pList,
			   void *keyData)
{
  LPSingleLinkListNode *ppPos;
  LPSingleLinkListNode pDeleteNode;
  BOOL bFound = False;

  ppPos = &pList->pHead;
  while (*ppPos) {
    if (pList->equal((*ppPos)->data, keyData)) {
      pDeleteNode = *ppPos;
      ppPos = &(*ppPos)->pNextNode;
      free(pDeleteNode->data);
      free(pDeleteNode);
      bFound = True;
    } else {
      ppPos = &(*ppPos)->pNextNode;
    } 
  }
  
  return bFound;
}
BOOL removeIfInSingleLinkListNode(LPSingleLinkList pList,
				  PredFunc pred,
				  void *predParameter)
{
  LPSingleLinkListNode *ppPos;
  LPSingleLinkListNode pDeleteNode;
  BOOL bFound = False;

  ppPos = &pList->pHead;
  while (*ppPos) {
    if (pred((*ppPos)->data, predParameter)) {
      pDeleteNode = *ppPos;
      ppPos = &(*ppPos)->pNextNode;
      free(pDeleteNode->data);
      free(pDeleteNode);
      bFound = True;
    } else {
      ppPos = &(*ppPos)->pNextNode;
    } 
  }
  
  return bFound;

}
void 
reverseSingleLinkList(LPSingleLinkList pList)
{
  LPSingleLinkListNode pIterNode, pNextNode;
  if (NULL == pList->pHead ||
      NULL == pList->pHead->pNextNode)
    return;
  
  pIterNode = pList->pHead->pNextNode;
  pList->pHead->pNextNode = NULL;
  while (pIterNode) {
    pNextNode = pIterNode->pNextNode;
    pIterNode->pNextNode = pList->pHead;
    pList->pHead = pIterNode;
    pIterNode = pNextNode;
  }
  return;
}
static void
insertSortSingleLinkList(LPSingleLinkList pList)
{
  LPSingleLinkListNode pIterNode, pNextNode;
  LPSingleLinkListNode ppInsertPos;
  if (NULL == pList->pHead ||
      NULL == pList->pHead->pNextNode)
    return;
  
  pIterNode = pList->pHead->pNextNode;
  pList->pHead->pNextNode = NULL;
  while (pIterNode) {
    pNextNode = pIterNode->pNextNode;
    ppInsertPos = &pList->pHead;
    while (*ppInsertPos && !pList->pLess(pIterNode->data, (*ppPos)->data))
      ppInsertPos = &(*ppInsertPos)->pNextNode;
    pIterNode->pNextNode = *ppInsertPos;
    *ppInsertPos = pIterNode;
    pIterNode = pNextNode;
  }
  return;

}
void
sortSingleLinkList(LPSingleLinkList pList)
{
  insertSortSingleLinkList(pList);
}
void
visitSingleLinkList(LPSingleLinkList pList,
		    VisitFunc visitor,
		    void *visitorParameter)
{
  LPSingleLinkListNode pIterNode = pList->pHead;
  while (pIterNode) {
    visitor(pIterNode->data, visitorParameter);
    pIterNode = pIterNode->pNextNode;
  }

}
void printSingleLinkList(LPSingleLinkList pList)
{


}
