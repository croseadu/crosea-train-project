
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
  return pList;
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
static LPSingleLinkListNode createNode(LPSingleLinkList pList, const char *data)
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
  }
}
void printSingleLinkList(const LPSingleLinkList pList)
{
  LPSingleLinkListNode pIterNode = pList->pHead->pNext;
  pList->formatCounter = 0;
  while (pIterNode) {
    pList->printer(pIterNode->data);
    if ((++pList->formatCounter % 5) == 0)
      putchar('\n');
  }
  if (pList->formatCounter % 5)
    putchar('\n');
}

static void insertSort(LPSingleLinkListNode pHead)
{
  LPSingleLinkListNode pEndNode;
  LPSingleLinkListNode *ppInsertIter;
  LPSingleLinkListNode pIterNode, pNextNode;
  
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
      pIterNode->pNext = (*ppInsertIter)->pNext;
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
  LPSingleLinkListNode pNode = createNode(pList, data);
  if (NULL == pNode)
    return False;
  pNode->pNext = pList->pHead->pNext;
  pList->pHead->pNext = pNode;
  return True;
}

bool insertToTailOfSingleLinkList(LPSingleLinkList pList, const char *data)
{
 LPSingleLinkListNode pNode = createNode(pList, data);
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
  LPSingleLinkListNode pNode = createNode(pList, data);
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
  LPSingleLinkListNode pNode = createNode(pList, data);
  if (NULL == pNode)
    return False;

  pNode->pNext = *ppInsertPt;
  *ppInsertPt = pNode;
  return True;
}

bool removeDataFromSingleLinkList(LPSingleLinkList pList, const char *data)
{
  LPSingleLinkListNode *ppIter;
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
bool removeIfFromSingleLinkList(LPSingleLinkList, Pred pred)
{
  LPSingleLinkListNode *ppIter;
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

LPSingleLinkList mergeSingleList(const LPSingleLinkList *,
				 const LPSingleLinkList *);
LPSingleLinkList differenceOfSingleLinkList(const LPSingleLinkList *,
					    const LPSingleLinkList *);
