
#include "../include/singleLinkList.h"

bool createSingleLinkList(LPSingleLinkList *ppList, 
			  unsigned int elementSize,
			  Printer printer,
			  LessFunc less,
			  EqualFunc equal)
{
  // Create a single link list with a header node.
  LPSingleLinkList pList;
  LPSingleLinkListNode pNode;

  pList = (LPSingleLinkList)malloc(sizeof(SingleLinkList));
  if (NULL == pList) {
    printf("Out of Memory in %d %s", __LINE__, __func__);
    return False;
  }
  
  pNode = (LPSingleLinkListNode)malloc(sizeof(SingleLinkListNode));
  if (NULL == pNode) {
    printf("Out of Memory in %d %s", __LINE__, __func__);
    free (pList);
    return False;  
  }

  pNode->pNext = NULL;
  pNode->data = NULL;
  pList->pHead = pNode;
  pList->elementSize = elementSize;
  pList->printer = printer;
  pList->less = less;
  pList->equal = equal;
  
  *ppList = pList;
  return True;
}

void destroySingleLinkList(LPSingleLinkList *ppList)
{
  LPSingleLinkList pList;
  LPSingleLinkListNode pIterNode, pNextNode;
  assert (ppList != NULL);
  
  pList = *ppList;
  assert (pList != NULL);
  pIterNode = pList->pHead;
  while (pIterNode) {
    pNextNode = pIterNode->pNext;
    if (pIterNode->data)
      free (pIterNode->data);
    free (pIterNode);
    pIterNode = pNextNode;
  }
  free (pList);
  *ppList = NULL;
}
static LPSingleLinkListNode createSingleLinkListNode(LPSingleLinkList pList, const char *data)
{
  LPSingleLinkListNode pNode;
  
  pNode = (LPSingleLinkListNode)malloc(sizeof(SingleLinkListNode));
  if (NULL == pNode) {
    printf ("Out Of Memory in %d %s", __LINE__, __func__);
    return NULL;
  }
  pNode->data = (char *)malloc(pList->elementSize);
  if (NULL == pNode->data) {
    printf ("Out Of Memory in %d %s", __LINE__, __func__);
    free (pNode);
    return NULL;
  }
  memcpy(pNode->data, data, pList->elementSize);
  return pNode;
}

void visitSingleLinkList(LPSingleLinkList pList, Visitor visitor)
{
  LPSingleLinkListNode pIterNode = pList->pHead->pNext;
  while (pIterNode) {
    visitor(pIterNode->data);
    pIterNode = pIterNode->pNext;
  }
}
void printSingleLinkList(const LPSingleLinkList pList, const char *prefix)
{
  LPSingleLinkListNode pIterNode = pList->pHead->pNext;

  printf("\n%s:\n", prefix);

  pList->formatCounter = 0;
  while (pIterNode) {
    pList->printer(pIterNode->data);
    if ((++pList->formatCounter % 5) == 0)
      putchar('\n');
    pIterNode = pIterNode->pNext;
  }
  if (pList->formatCounter % 5)
    putchar('\n');
}

static void insertSort(LPSingleLinkList pList)
{
  LPSingleLinkListNode pEndNode, pHead;
  LPSingleLinkListNode *ppInsertIter;
  LPSingleLinkListNode pIterNode, pNextNode;
  
  pHead = pList->pHead;
  // If List only have zero or one node, directly return;
  if (pHead->pNext == NULL 
      || pHead->pNext->pNext == NULL) {
    return;
  }
  pEndNode = pHead->pNext;
  pIterNode = pEndNode->pNext;
  pEndNode->pNext = NULL;
  
  while (pIterNode) {
    // Else is a fast branch, use for optimization.
    if (pList->less(pIterNode->data, pEndNode->data)) {
      pNextNode = pIterNode->pNext;
      ppInsertIter = &pHead->pNext;
      while ((*ppInsertIter) && 
	     !pList->less(pIterNode->data,(*ppInsertIter)->data))
	ppInsertIter = &((*ppInsertIter)->pNext);
      pIterNode->pNext = (*ppInsertIter);
      *ppInsertIter = pIterNode;
      pIterNode = pNextNode;
    } else {
      pEndNode->pNext = pIterNode;
      pIterNode = pIterNode->pNext;
      pEndNode = pEndNode->pNext;
      pEndNode->pNext = NULL;
    }
  }
  
}

void sortSingleLinkList(LPSingleLinkList pList)
{
  // Default use insertSort
  insertSort(pList);
}

bool insertToHeadOfSingleLinkList(LPSingleLinkList pList, const char *data)
{
  LPSingleLinkListNode pNode = createSingleLinkListNode(pList, data);
  if (NULL == pNode)
    return False;
  pNode->pNext = pList->pHead->pNext;
  pList->pHead->pNext = pNode;
  return True;
}

bool insertToTailOfSingleLinkList(LPSingleLinkList pList, const char *data)
{
 LPSingleLinkListNode pNode = createSingleLinkListNode(pList, data);
 LPSingleLinkListNode pPrevNode; 
 if (NULL == pNode)
    return False;
  
 pPrevNode = pList->pHead;
 while (pPrevNode->pNext != NULL) {
   pPrevNode = pPrevNode->pNext;
 }
 pNode->pNext = NULL;
 pPrevNode->pNext = pNode;
 return True;
}

bool insertAfterSingleLinkList(LPSingleLinkList pList, 
			       LPSingleLinkListNode pInsertPt, 
			       const char *data)
{
  LPSingleLinkListNode pNode = createSingleLinkListNode(pList, data);
  if (NULL == pNode)
    return False;

  pNode->pNext = pInsertPt->pNext;
  pInsertPt->pNext = pNode;
  return True;
}

bool insertBeforeSingleLinkList(LPSingleLinkList pList, 
			       LPSingleLinkListNode *ppInsertPt, 
			       const char *data)
{
  LPSingleLinkListNode pNode = createSingleLinkListNode(pList, data);
  if (NULL == pNode)
    return False;

  pNode->pNext = *ppInsertPt;
  *ppInsertPt = pNode;
  return True;
}

bool removeDataFromSingleLinkList(LPSingleLinkList pList, const char *data)
{
  LPSingleLinkListNode *ppIter, pNode;
  bool bFound = False;

  ppIter = &pList->pHead->pNext;
  while (*ppIter) {
    if (pList->equal((*ppIter)->data, data)) {
      pNode = *ppIter;
      *ppIter = pNode->pNext;
      free (pNode);
      bFound = True;
    } else {
      ppIter = &(*ppIter)->pNext;
    }
  }
  return bFound;
}
bool removeIfFromSingleLinkList(LPSingleLinkList pList, Pred pred)
{
  LPSingleLinkListNode *ppIter, pNode;
  bool bFound = False;

  ppIter = &pList->pHead->pNext;
  while (*ppIter) {
    if (pred((*ppIter)->data)) {
      pNode = *ppIter;
      *ppIter = pNode->pNext;
      free (pNode);
      bFound = True;
    } else {
      ppIter = &(*ppIter)->pNext;
    }
  }
  return bFound;
}

bool removeFromSingleLinkList(LPSingleLinkList pList, LPSingleLinkListNode *ppDelete)
{
  LPSingleLinkListNode pNode = *ppDelete;
  *ppDelete = pNode->pNext;
  free (pNode);
  return True;
}

LPSingleLinkListNode *findInSingleLinkList(LPSingleLinkList pList, const char *data)
{
  LPSingleLinkListNode pIter;
  pIter = pList->pHead;
  while (pIter->pNext) {
    if (pList->equal(pIter->pNext->data, data))
      break;
    pIter = pIter->pNext;
  }
  
  return pIter->pNext?&pIter->pNext:NULL;
}

LPSingleLinkList mergeSingleList(const LPSingleLinkList lhs,
				 const LPSingleLinkList rhs)
{
  LPSingleLinkList pResult;
  LPSingleLinkListNode pLhsIter;
  LPSingleLinkListNode pRhsIter;
  LPSingleLinkListNode pInsertPt;

  if (!createSingleLinkList(&pResult, 
			    lhs->elementSize,
			    lhs->printer,
			    lhs->less,
			    lhs->equal))
    return NULL;
  
  pLhsIter = lhs->pHead->pNext;
  pRhsIter = rhs->pHead->pNext;
  lhs->pHead->pNext = NULL;
  rhs->pHead->pNext = NULL;
  pInsertPt = pResult->pHead;
  while (pLhsIter && pRhsIter) {
    if (pResult->less(pLhsIter->data, pRhsIter->data)) {
      pInsertPt = pLhsIter;
      pLhsIter = pLhsIter->pNext;
    }
    else {
      pInsertPt = pRhsIter;
      pRhsIter = pRhsIter->pNext;
    }
    pInsertPt = pInsertPt->pNext;
  }
  if (pLhsIter)
    pInsertPt->pNext = pLhsIter;
  else
    pInsertPt->pNext = pRhsIter;
  return pResult;
}

LPSingleLinkList copySingleLinkList(const LPSingleLinkList pList)
{
  LPSingleLinkList pResult;
  LPSingleLinkListNode pIter, pInsertPt, pNewNode;
  

  if (!createSingleLinkList(&pResult, 
			    pList->elementSize,
			    pList->printer,
			    pList->less,
			    pList->equal))
    return NULL;
  
  pIter = pList->pHead->pNext;
  pInsertPt = pList->pHead;
  while (pIter) {
    pNewNode = createSingleLinkListNode(pList,pIter->data);
    pInsertPt->pNext = pNewNode;
    pInsertPt = pNewNode;
  }
  pInsertPt->pNext = NULL;
  return pResult;
}

LPSingleLinkList differenceOfSingleLinkList(const LPSingleLinkList lhs,
					    const LPSingleLinkList rhs)
{
  LPSingleLinkList pResult;
  LPSingleLinkListNode pIter, pTemp;
  LPSingleLinkListNode *ppFind;

  pResult = copySingleLinkList(lhs);

  if (NULL == pResult)
    return NULL;
  pIter = rhs->pHead->pNext;
  while (pIter) {
    if (NULL == (ppFind = findInSingleLinkList(lhs, pIter->data))) {
      insertToTailOfSingleLinkList(pResult, pIter->data);
    } else {
      // remove the find node since it also exist in rhs.
      pTemp = *ppFind;
      *ppFind = (*ppFind)->pNext;
      free (pTemp);
    }
    pIter = pIter->pNext;
  }

  return pResult;
}

void reverseSingleLinkList(LPSingleLinkList pList)
{
  LPSingleLinkListNode pIterNode, pNextNode, pHead;
  pHead = pList->pHead;

  if (pHead == NULL
      || pHead->pNext == NULL)
    return;
  
  pIterNode = pHead->pNext->pNext;
  pHead->pNext->pNext = NULL;
  while (pIterNode) {
    pNextNode = pIterNode->pNext;
    pIterNode->pNext = pHead->pNext;
    pHead->pNext = pIterNode;
    pIterNode = pNextNode;
  }
}
