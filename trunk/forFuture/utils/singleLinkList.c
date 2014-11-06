#include "../include/singleLinkList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


BOOL
initSingleLinkList(LPSingleLinkList *ppList,
			unsigned int elementSize,
			Printer printer,
			CompareFunc less,
			CompareFunc equal)
{
  LPSingleLinkList pList = NULL;
  pList = (LPSingleLinkList)malloc(sizeof(SingleLinkList));
  if (NULL == pList) {
    printf("Out Of Memory in %s", __func__);
    return FALSE;
  }
  pList->pHead = NULL;
  pList->elementSize = elementSize;
  pList->printer=printer;
  pList->less = less;
  pList->equal = equal;
  pList->listSize = 0;

  *ppList = pList;
  return TRUE;
}
void
destroySingleLinkList(LPSingleLinkList *ppList)
{
  LPSingleLinkList pList;
  LPSingleLinkListNode pIterNode, pNextNode;

  assert (ppList != NULL);
  pList = *ppList;
  if (NULL == pList)
    return;

  pIterNode = pList->pHead;
  while (pIterNode) {
    pNextNode = pIterNode->pNextNode;
    free(pIterNode->data);
    free(pIterNode);
    pIterNode = pNextNode;
  }
  
  free(pList);
  *ppList = NULL;
}

static LPSingleLinkListNode
createNewSingleLinkListNode(const LPSingleLinkList pList,
			    void *srcData)
{
  LPSingleLinkListNode pNode;

  pNode = (LPSingleLinkListNode)malloc(sizeof(SingleLinkListNode));
  if (NULL == pNode) {
    printf("Out Of Memory in %s", __func__);
    return NULL;
  }
  pNode->data = malloc(pList->elementSize);
  if (NULL == pNode->data) {
    free(pNode);
    printf("Out of Memory in %s", __func__);
    return NULL;
  }
  memcpy(pNode->data, srcData, pList->elementSize);
  pNode->pNextNode = NULL;
  return pNode;
}

BOOL
insertToSingleLinkList(LPSingleLinkList pList,
		       void *srcData,
		       LPSingleLinkListNode pInsertAfter)
{
  LPSingleLinkListNode pNewNode, *ppInsertPos;
  

  pNewNode = createNewSingleLinkListNode(pList, srcData);
  if (NULL == pNewNode) {
    return FALSE;
  }
  ppInsertPos = &pInsertAfter->pNextNode;
  pNewNode->pNextNode = *ppInsertPos;
  *ppInsertPos = pNewNode;
  ++pList->listSize;
  return TRUE;
}

BOOL
insertToSingleLinkListHead(LPSingleLinkList pList,
				void *srcData)
{
  LPSingleLinkListNode pNewNode, *ppInsertPos;

  pNewNode = createNewSingleLinkListNode(pList, srcData);
  if (NULL == pNewNode) {
    return FALSE;
  }
  
  ppInsertPos = &pList->pHead;
  pNewNode->pNextNode = *ppInsertPos;
  *ppInsertPos = pNewNode;

  ++pList->listSize;
  return TRUE;
}
BOOL
insertToSingleLinkListTail(LPSingleLinkList pList,
				void *srcData)
{
  LPSingleLinkListNode pNewNode, *ppInsertPos;

  pNewNode = createNewSingleLinkListNode(pList, srcData);
  if (NULL == pNewNode) {
    return FALSE;
  }
  ppInsertPos = &pList->pHead;
  while (*ppInsertPos) {
    ppInsertPos = &(*ppInsertPos)->pNextNode;
  }
  
  pNewNode->pNextNode = NULL;
  *ppInsertPos = pNewNode;

  ++pList->listSize;
  return TRUE;
  

}
BOOL
removeFromSingleLinkList(LPSingleLinkList pList,
			      void *refData)
{
  BOOL bFound = FALSE;
  LPSingleLinkListNode *ppIterNode, pRemoveNode;
  
  ppIterNode = &pList->pHead;
  while ((pRemoveNode = *ppIterNode)) {
    if (pList->equal(pRemoveNode->data, refData)) {
      *ppIterNode = pRemoveNode->pNextNode;
      free(pRemoveNode->data);
      free(pRemoveNode);
      bFound = TRUE;
      
    } else {
      ppIterNode = &(*ppIterNode)->pNextNode;
    }
  }

  return bFound;
}

BOOL
removeIfFromSingleLinkList(LPSingleLinkList pList,
				PredFunc pred,
				void *predArgument)
{
  BOOL bFound = FALSE;
  LPSingleLinkListNode *ppIterNode, pRemoveNode;

  ppIterNode = &pList->pHead;
  while ((pRemoveNode = *ppIterNode)) {
    if (pred(pRemoveNode->data, predArgument)) {
      *ppIterNode = pRemoveNode->pNextNode;
      free(pRemoveNode->data);
      free(pRemoveNode);
      bFound = TRUE;
    } else {
      ppIterNode = &(*ppIterNode)->pNextNode;
    }
  }
  return bFound;
}

LPSingleLinkListNode 
findInSingleLinkList(LPSingleLinkList pList,
		     void *refData)
{
  LPSingleLinkListNode pIterNode;
  pIterNode = pList->pHead;
  while (pIterNode != NULL) {
    if (pList->equal(pIterNode->data, refData))
      return pIterNode;
  }
  return NULL;
}

void
visitSingleLinkList(LPSingleLinkList pList,
		    Visitor visitor,
		    void *visitorArgument)
{
  LPSingleLinkListNode pIterNode;
  
  pIterNode = pList->pHead;
  while (pIterNode) {
    visitor(pIterNode->data, visitorArgument);
    pIterNode = pIterNode->pNextNode;
  }
}

typedef struct _PrintInfo
{
  Printer printer;
  unsigned int printWidth;
  unsigned int numberOfPrinted;
}PrintInfo, *LPPrintInfo;

static void
printerHelper(void *data, void *printArgument)
{
  LPPrintInfo lpPrintInfo = (LPPrintInfo)printArgument;
  lpPrintInfo->printer(data);
  if (++lpPrintInfo->numberOfPrinted % lpPrintInfo->printWidth == 0) {
    putchar('\n');
  }
}

void
printSingleLinkList(LPSingleLinkList pList)
{
  PrintInfo printInfo;
  printInfo.printer = pList->printer;
  printInfo.printWidth = 5;
  printInfo.numberOfPrinted = 0;
  visitSingleLinkList(pList, printerHelper, &printInfo);
  if (printInfo.numberOfPrinted % printInfo.printWidth != 0) {
    putchar('\n');
  }
}

static void
insertSortSingleLinkList(LPSingleLinkList pList)
{
  LPSingleLinkListNode pIterNode, pNextNode;;
  LPSingleLinkListNode *ppInsertPos;

  if (NULL == pList->pHead || NULL == pList->pHead->pNextNode)
    return;
  
  pIterNode = pList->pHead->pNextNode;
  pList->pHead->pNextNode = NULL;
  while (pIterNode != NULL) {
    pNextNode = pIterNode->pNextNode;
    ppInsertPos = &pList->pHead;
    // Do a stable sort, keep order for equal elements
    while (*ppInsertPos && !pList->less(pIterNode->data, (*ppInsertPos)->data))
      ppInsertPos = &(*ppInsertPos)->pNextNode;
    pIterNode->pNextNode = *ppInsertPos;
    *ppInsertPos = pIterNode;
    pIterNode = pNextNode;
  }
}

void
sortSingleLinkList(LPSingleLinkList pList)
{
  insertSortSingleLinkList(pList);
}


void
uniqueSingleLinkList(LPSingleLinkList pList)
{
  LPSingleLinkListNode pIterNode, pNextNode;
  LPSingleLinkListNode pLiveNode;

  if (NULL == pList->pHead
      || NULL == pList->pHead->pNextNode)
    return;

  pLiveNode = pList->pHead;
  pIterNode = pLiveNode->pNextNode;
  while (pIterNode) {
    if (pList->equal(pIterNode->data, pLiveNode->data)) {
      pNextNode = pIterNode->pNextNode;
      free(pIterNode->data);
      free(pIterNode);
      pIterNode = pNextNode;
    } else {
      pLiveNode->pNextNode = pIterNode;
      pLiveNode = pIterNode;
      pIterNode = pIterNode->pNextNode;
    }
  }

  pLiveNode->pNextNode = NULL;
}

void
reverseSingleLinkList(LPSingleLinkList pList)
{
  LPSingleLinkListNode pIterNode, pNextNode;
  if (NULL == pList->pHead 
      || NULL == pList->pHead->pNextNode)
    return;
  
  pIterNode = pList->pHead->pNextNode;
  pList->pHead->pNextNode = NULL;
  while (pIterNode) {
    pNextNode = pIterNode->pNextNode;
    pIterNode->pNextNode = pList->pHead;
    pList->pHead = pIterNode;
    pIterNode = pNextNode;
  }
}

LPSingleLinkList
mergeSingleLinkList(LPSingleLinkList pLhsList,
		    LPSingleLinkList pRhsList,
		    BOOL duplicateSubElement)
{
  LPSingleLinkList pResultList;
  LPSingleLinkListNode *ppLhsIterNode, *ppRhsIterNode;
  LPSingleLinkListNode *ppLastNode;
  LPSingleLinkListNode pNewNode;

  BOOL flag = initSingleLinkList(&pResultList,
				 pLhsList->elementSize,
				 pLhsList->printer,
				 pLhsList->less,
				 pLhsList->equal);
  if (!flag)
    return NULL;
  
  ppLhsIterNode = &pLhsList->pHead;
  ppRhsIterNode = &pRhsList->pHead;
  ppLastNode = &pResultList->pHead;
  while (*ppLhsIterNode && *ppRhsIterNode) {
    if (pResultList->less((*ppLhsIterNode)->data, (*ppRhsIterNode)->data)) {
      if (duplicateSubElement) {
	pNewNode = createNewSingleLinkListNode(pResultList,
					       (*ppLhsIterNode)->data);
	if (NULL == pNewNode) {
	  destroySingleLinkList(&pResultList);
	  return NULL;
	}
	*ppLastNode = pNewNode;
	pNewNode->pNextNode = NULL;
	ppLastNode = &pNewNode->pNextNode;
	ppLhsIterNode = &(*ppLhsIterNode)->pNextNode;
      } else {
	*ppLastNode = *ppLhsIterNode;
	ppLhsIterNode = &(*ppLhsIterNode)->pNextNode;
	(*ppLastNode)->pNextNode = NULL;
	ppLastNode = &(*ppLastNode)->pNextNode;
      }
    } else {
      if (duplicateSubElement) {
	pNewNode = createNewSingleLinkListNode(pResultList,
					       (*ppRhsIterNode)->data);
	if (NULL == pNewNode) {
	  destroySingleLinkList(&pResultList);
	  return NULL;
	}
	*ppLastNode = pNewNode;
	pNewNode->pNextNode = NULL;
	ppLastNode = &pNewNode->pNextNode;
	ppRhsIterNode = &(*ppRhsIterNode)->pNextNode;
      } else {
	*ppLastNode = *ppRhsIterNode;
	ppRhsIterNode = &(*ppRhsIterNode)->pNextNode;
	(*ppLastNode)->pNextNode = NULL;
	ppLastNode = &(*ppLastNode)->pNextNode;
      }
    }
  }
  if (*ppLhsIterNode) {
    if (duplicateSubElement) {
      while (*ppLhsIterNode) {
	pNewNode = createNewSingleLinkListNode(pResultList,
					       (*ppLhsIterNode)->data);
	if (NULL == pNewNode) {
	  destroySingleLinkList(&pResultList);
	  return NULL;
	}
	*ppLastNode = pNewNode;
	pNewNode->pNextNode = NULL;
	ppLastNode = &pNewNode->pNextNode;
	ppLhsIterNode = &(*ppLhsIterNode)->pNextNode;	
      }
    } else {
      *ppLastNode = *ppLhsIterNode;
    }
  } else if (*ppRhsIterNode) {
    if (duplicateSubElement) {
      while (*ppRhsIterNode) {
	pNewNode = createNewSingleLinkListNode(pResultList,
					       (*ppRhsIterNode)->data);
	if (NULL == pNewNode) {
	  destroySingleLinkList(&pResultList);
	  return NULL;
	}
	*ppLastNode = pNewNode;
	pNewNode->pNextNode = NULL;
	ppLastNode = &pNewNode->pNextNode;
	ppRhsIterNode = &(*ppRhsIterNode)->pNextNode;
      }
    } else {
      *ppLastNode = *ppRhsIterNode;
    }

  }
  pResultList->listSize = pLhsList->listSize + pRhsList->listSize;
  if (!duplicateSubElement) {
    pLhsList->listSize = 0;
    pRhsList->listSize = 0;
    pLhsList->pHead = NULL;
    pRhsList->pHead = NULL;
  }
  return pResultList;
}

