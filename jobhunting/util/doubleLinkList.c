

#include "doubleLinkList.h"
#include "memory.h"
#include <assert.h>

BOOL createDoubleLinkList(LPDoubleLinkList *ppList, unsigned int elementSize, Printer printer, Less less)
{
	LPDoubleLinkList pList = NULL;
	
	pList = (LPDoubleLinkList)myMalloc(sizeof(DoubleLinkList));
	if (NULL == pList) {
		printf("Out Of Memory in %d %s", __LINE__, __func__);
		return False;
	}

	pList->pHead = (LPDoubleLinkListNode)myMalloc(sizeof(DoubleLinkListNode));
	if (NULL == pList->pHead) {
		printf("Out Of Memory in %d %s", __LINE__, __func__);
		return False;
	}
	pList->pHead->data = NULL;
	pList->pHead->pNextNode = pList->pHead;
	pList->pHead->pPrevNode = pList->pHead;

	pList->elementSize = elementSize;
	pList->less = less;
	
	*ppList = pList;
	return True;

}
void clearDoubleLinkList(LPDoubleLinkList pList)
{
	LPDoubleLinkListNode pIterNode, pNextNode;
	pIterNode = pList->pHead->pNextNode;
	pList->pHead->pNextNode = pList->pHead;
	pList->pHead->pPrevNode = pList->pHead;

	while (pIterNode != pList->pHead) {
		pNextNode = pIterNode->pNextNode;
		if (pIterNode->data) {
			myFree(pIterNode->data);
		}
		myFree(pIterNode);
		pIterNode = pNextNode;
	}

}


void destroyDoubleLinkList(LPDoubleLinkList *ppList)
{
	LPDoubleLinkList pList = *ppList;
	clearDoubleLinkList(pList);
	
	myFree(pList->pHead);
	myFree(pList);        
	*ppList = NULL;

}

static LPDoubleLinkListNode 
createDoubleLinkListNode(const LPDoubleLinkList pList, const void *data)
{
	LPDoubleLinkListNode pNewNode = NULL;

	pNewNode = (LPDoubleLinkListNode)myMalloc(sizeof(DoubleLinkListNode));
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


BOOL insertToHeadOfDoubleLinkList(LPDoubleLinkList pList, const void *data)
{	
	LPDoubleLinkListNode pNewNode;

	pNewNode = createDoubleLinkListNode(pList, data);
	if (NULL == pNewNode) {
		return False;
	}	

	pNewNode->pNextNode = pList->pHead->pNextNode;
	pNewNode->pPrevNode = pList->pHead;
	pNewNode->pNextNode->pPrevNode = pNewNode;
	pNewNode->pPrevNode->pNextNode = pNewNode;

	return True;
}

BOOL insertToTailOfDoubleLinkList(LPDoubleLinkList, const void *data)
{
	LPDoubleLinkListNode pNewNode;

	pNewNode = createDoubleLinkListNode(pList, data);
	if (NULL == pNewNode) {
		return False;
	}	

	pNewNode->pNextNode = pList->pHead;
	pNewNode->pPrevNode = pList->pHead->pPrevNode;
	pNewNode->pNextNode->pPrevNode = pNewNode;
	pNewNode->pPrevNode->pNextNode = pNewNode;
	
	return True;
}

BOOL
insertAfterInDoubleLinkList(LPDoubleLinkList pList, const void *data, DoubleLinkListIter insertAfter)
{
	LPDoubleLinkListNode pNewNode;

	pNewNode = createDoubleLinkListNode(pList, data);
	if (NULL == pNewNode) {
		return False;
	}

	pNewNode->pNextNode = insertAfter->pNextNode;
	pNewNode->pPrevenode = insertAfter;
	insertAfter->pNextNode = pNewNode;
	pNewNode->pNextNode->pPrevNode = pNewNode;

	return True;
	
}

BOOL insertBeforeInDoubleLinkList(LPDoubleLinkList pList, const void *data, DoubleLinkListIter insertBefore)
{
	LPDoubleLinkListNode pNewNode;

	pNewNode = createDoubleLinkListNode(pList, data);
	if (NULL == pNewNode) {
		return False;
	}

	pNewNode->pNextNode = insertBefore;
	pNewNode->pPrevNode = insertBefore->pPrevNode;
	pNewNode->pNextNode->pPrevNode = pNewNode;
	pNewNode->pPrevNode->pNextNode = pNewNode;
		

	return True;
}


DoubleLinkListIter findInDoubleLinkList(LPDoubleLinkList pList, Predicate pred)
{
	DoubleLinkListIter iter;
	
	iter = (DoubleLinkListIter)pList->pHead->pNextNode;
	while (iter != pList->pHead && pred(iter->data) == False) {
		iter = (DoubleLinkListIter)(iter->pNextNode);
	}

	return iter != pList->pHead ? iter : NULL;

}

void removeFromDoubleLinkList(LPDoubleLinkList pList, DoubleLinkListIter iter)
{
	LPDoubleLinkListNode pDeleteNode = iter;

	iter->pPrevNode->pNextNode = pDeleteNode->pNextNode;
	iter->pNextNode->pPrevNode = pDeleteNode->pPrevNode;
	myFree(pDeleteNode->data);
	myFree(pDeleteNode);
}

void removeIfInDoubleLinkList(LPDoubleLinkList pList, Predicate pred)
{
	DoubleLinkListIter iter = (DoubleLinkListIter)pList->pHead->pNextNode;
	DoubleLinkListIter nextIt;	

	while (iter != pList->pHead) {
		if (pred(iter->data) == True) {
			nextIt = (DoubleLinkListIter)iter->pNextNode;
			removeFromDoubleLinkList(pList, iter);
			iter = nextIt;
		} else {
			iter = (DoubleLinkListIter)iter->pNextNode;
		}

	}
}

void sortDoubleLinkList(LPDoubleLinkList pList)
{
	LPDoubleLinkListNode pIterNode, pNextNode;
	DoubleLinkListIter iter;
	
	if (pList->pHead->pNextNode == pList->pHead || pList->pHead->pNextNode->pNextNode == pList->pHead) {
		return;
	}

	pIterNode = pList->pHead->pNextNode->pNextNode;
	pList->pHead->pNextNode->pNextNode = pList->pHead;
	pList->pHead->pPrevNode = pList->pHead->pNextNode;


	while (pIterNode != pList->pHeadNode) {
		pNextNode = pIterNode->pNextNode;
		iter =(DoubleLinkListIter)pList->pHead->pNextNode;
		while (*iter != pList->pHead && pList->less(iter->data, pIterNode->data) == True) {
			iter = iter->pNextNode;
		}
		
		pIterNode->pNextNode = iter;
		pIterNode->pPrevNode = iter->pPrevNode;
		pIterNode->pNextNode->pPrevNode = pIterNode;
		pIterNode->pPrevNode->pnextNode = pIterNode;	
	
		pIterNode = pNextNode;
	}
}

BOOL isDoubleLinkListEmpty(const LPDoubleLinkList pList)
{
	return (pList->Head->pNextNode == pList->pHead)?True:False;
}

unsigned int sizeOfDoubleLinkList(const LPDoubleLinkList pList)
{
	unsigned int length = 0;

	LPDoubleLinkListNode pIterNode = pList->pHead->pNextNode;

	while (pIterNode != pList->pHead) {
		++length;
		pIterNode = pIterNode->pNextNode;
	}
	return length;
}

void TraverseDoubleLinkList(LPDoubleLinkList pList, Visitor visitor)
{
	LPDoubleLinkListNode pIterNode = pList->pHead->pNextNode;


	while (pIterNode != pList->pHead) {
		visitor(pIterNode->data);
		pIterNode = pIterNode->pNextNode;
	}
}

