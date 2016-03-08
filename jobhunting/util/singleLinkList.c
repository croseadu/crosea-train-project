
#include "singleLinkList.h"
#include "memory.h"
#include <assert.h>

BOOL createSingleLinkList(LPSingleLinkList *ppList, unsigned int elementSize, Printer printer, Less less)
{
	LPSingleLinkList pList = NULL;
	
	pList = (LPSingleLinkList)myMalloc(sizeof(SingleLinkList));
	if (NULL == pList) {
		printf("Out Of Memory in %d %s", __LINE__, __func__);
		return False;
	}

	pList->pHead = NULL;
	pList->elementSize = elementSize;
	pList->less = less;
	
	*ppList = pList;
	return True;

}
void clearSingleLinkList(LPSingleLinkList pList)
{
	LPSingleLinkListNode pIterNode, pNextNode;
	pIterNode = pList->pHead;
	pList->pHead = NULL;

	while (pIterNode != NULL) {
		pNextNode = pIterNode->pNextNode;
		if (pIterNode->data) {
			myFree(pIterNode->data);
		}
		myFree(pIterNode);
		pIterNode = pNextNode;
	}

}


void destroySingleLinkList(LPSingleLinkList *ppList)
{
	LPSingleLinkList pList = *ppList;
	clearSingleLinkList(pList);


	myFree(pList);        
	*ppList = NULL;

}

BOOL insertToHeadOfSingleLinkList(LPSingleLinkList pList, const void *data)
{	
	SingleLinkListIter iter = (SingleLinkListIter)(&pList->pHead);
	return insertBeforeInSingleLinkList(pList, data, iter);
}

BOOL insertToTailOfSingleLinkList(LPSingleLinkList, const void *data)
{
	SingleLinkListIter iter = (SingleLinkListIter)(&pList->pHead);
	while ( *iter != NULL) {
		iter = (SingleLinkListIter)&(*iter)->pNextNode;
	}
	
	return insertBeforeInSingleLinkList(pList, data, iter);
}

static LPSingleLinkListNode 
createSingleLinkListNode(const LPSingleLinkList pList, const void *data)
{
	LPSingleLinkListNode pNewNode = NULL;

	pNewNode = (LPSingleLinkListNode)myMalloc(sizeof(SingleLinkListNode));
	if (NULL == pNewNode) {
		printf("Out Of Memory in %d %s", __LINE__, __func__);
		return NULL;
	}

	pNewNode->data = myAlloc(pList->elementSize);
	if (NULL == pNewNode->data) {
		printf("Out Of Memory in %d %s", __LINE__, __func__);
		myFree(pNewNode);
		return NULL;
	}
	memcpy(pNewNode->data, data, pList->elementSize);
	pNewNode->pNextNode = NULL;
	
	return pNewNode;
}

BOOL
insertAfterInSingleLinkList(LPSingleLinkList pList, const void *data, SingleLinkListIter insertAfter)
{
	LPSingleLinkListNode pNewNode;

	pNewNode = createSingleLinkListNode(pList, data);
	if (NULL == pNewNode) {
		return False;
	}

	pNewNode->pNextNode = (*insertAfter)->pNextNode;
	(*insertAfter)->pNextNode = pNewNode;

	return True;
	
}

BOOL insertBeforeInSingleLinkList(LPSingleLinkList pList, const void *data, SingleLinkListIter insertBefore)
{
	LPSingleLinkListNode pNewNode;

	pNewNode = createSingleLinkListNode(pList, data);
	if (NULL == pNewNode) {
		return False;
	}

	pNewNode->pNextNode = (*iter);
	*Iter = pNewNode;
	return True;
}


SingleLinkListIter findInSingleLinkList(LPSingleLinkList pList, Predicate pred)
{
	SingleLinkListIter iter;
	
	iter = (SingleLinkListIter)&pList->pHead;
	while (*iter != NULL && pred((*iter)->data) == False) {
		iter = (SingleLinkListIter)&((*iter)->pNextNode);
	}

	return iter;

}

void removeFromSingleLinkList(LPSingleLinkList pList, SingleLinkListIter iter)
{
	LPSingleLinkListNode pDeleteNode = *iter;

	*Iter = pDeleteNode->pNextNode;
	myFree(pDeleteNode->data);
	myFree(pDeleteNode);
}

void removeIfInSingleLinkList(LPSingleLinkList pList, Predicate pred)
{
	SingleLinkListIter iter = (SingleLinkListIter)&pList->pHead;
	SingleLinkListIter nextIt;	

	while (*iter != NULL) {
		if (pred((*iter)->data) == True) {
			nextIt = (SingleLinkListIter)&((*iter)->pNextNode);
			removeFromSingleLinkList(pList, iter);
			iter = nextIt;
		} else {
			iter = (SingleLinkListIter)&((*iter)->pNextNode);
		}

	}
}

void sortSingleLinkList(LPSingleLinkList pList)
{
	LPSingleLinkListNode pIterNode, pNextNode;
	SingleLinkListIter iter;
	
	if (pList->pHead == NULL || pList->pHead->pNextNode == NULL) {
		return;
	}

	pIterNode = pList->pHead->pNextNode;
	pList->pHead->pNextNode = NULL;


	while (pIterNode != NULL) {
		pNextNode = pIterNode->pNextNode;
		iter =(SingleLinkListIter)&pList->pHead;
		while (*iter != NULL && pList->less((*iter)->data, pIterNode->data) == True) {
			iter = &(*iter)->pNextNode;
		}
		
		pIterNode->pNextNode = *iter;
		*iter = pIterNode;
		pIterNode = pNextNode;
	}
}

BOOL isSingleLinkListEmpty(const LPSingleLinkList pList)
{
	return (pList->Head == NULL)?True:False;
}

unsigned int sizeOfSingleLinkList(const LPSingleLinkList pList)
{
	unsigned int length = 0;

	LPSingleLinkListNode pIterNode = pList->pHead;

	while (pIterNode != NULL) {
		++length;
		pIterNode = pIterNode->pNextNode;
	}
	return length;
}

void TraverseSingleLinkList(LPSingleLinkList pList, Visitor visitor)
{
	LPSingleLinkListNode pIterNode = pList->pHead;


	while (pIterNode != NULL) {
		visitor(pIterNode->data);
		pIterNode = pIterNode->pNextNode;
	}
}

