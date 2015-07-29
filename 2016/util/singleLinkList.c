#include <stdio.h>
#include "common.h"
#include "singleLinkList.h"
#include "myMemory.h"


enum BOOL
createSingleLinkList(LPSingleLinkList *ppList,
                     unsigned int elementSize,
                     Printer printer,
		     Less less)
{
	LPSingleLinkList pList = (LPSingleLinkList)myAlloc(sizeof(SingleLinkList));
	if (NULL == pList) {
		printf("Out Of Memory!");
		return False;
	}
	pList->pHead = NULL;
	pList->elementSize = elementSize;
	pList->printer = printer;
	pList->less = less;
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
	while (NULL != pIterNode) {
		pNextNode = pIterNode->pNextNode;
		if (pIterNode->data != NULL)
			myFree(pIterNode->data);
		if (pIterNode != NULL)
			myFree(pIterNode);
		pIterNode = pNextNode;

	}
	*ppList = NULL;
}

static LPSingleLinkListNode
createSingleLinkListNode(const LPSingleLinkList pList, const void *data)
{
	LPSingleLinkListNode pNewNode = NULL;
	pNewNode = myAlloc(sizeof(SingleLinkListNode));
	if (NULL == pNewNode) {
		printf("Out Of Memory!");
		return NULL;
	}
	pNewNode->data = myAlloc(pList->elementSize);
	if (NULL == pNewNode->data) {
		myFree(pNewNode);
		printf("Out Of Memory");
		return NULL;
	}
	pNewNode->pNextNode = NULL;
	memcpy(pNewNode->data, data, pList->elementSize);
	return pNewNode;
}
enum BOOL
insertToHeadOfSingleLinkList(LPSingleLinkList pList, const void *data)
{
	LPSingleLinkListNode pNewNode;
	pNewNode = createSingleLinkListNode(pList,data);
	if (NULL == pNewNode) {
		return False;
	}
	pNewNode->pNextNode = pList->pHead;
	pList->pHead = pNewNode;
	return True;
}


enum BOOL
insertToTailOfSingleLinkList(LPSingleLinkList pList, const void *data)
{

	LPSingleLinkListNode pNewNode, *ppInsertPos;
	pNewNode = createSingleLinkListNode(pList,data);
	if (NULL == pNewNode) {
		return False;
	}
	ppInsertPos = &pList->pHead;
	while (*ppInsertPos != NULL)
		ppInsertPos = &(*ppInsertPos)->pNextNode;
	*ppInsertPos = pNewNode;
	return True;
}

enum BOOL
insertAfterInSingleLinkList(LPSingleLinkList pList, const void *data, SingleLinkListIter iter)
{
	LPSingleLinkListNode pNewNode;
	pNewNode = createSingleLinkListNode(pList,data);
	if (NULL == pNewNode) {
		return False;
	}
		
	pNewNode->pNextNode = (*iter)->pNextNode;
	(*iter)->pNextNode = pNewNode;
	return True;
}

SingleLinkListIter findInSingleLinkList(LPSingleLinkList pList, const void *key)
{
	SingleLinkListIter iter = &pList->pHead;
	while (*iter != NULL 
		&& !(!pList->less(key, (*iter)->data)
		     && !pList->less((*iter)->data, key)))
		iter = &(*iter)->pNextNode;
	return iter;
		
}
SingleLinkListIter findIfInSingleLinkList(LPSingleLinkList pList, Pred pred)
{
	SingleLinkListIter iter = &pList->pHead;
	while (*iter != NULL && !pred((*iter)->data)) 
		iter = &(*iter)->pNextNode;
	return iter;


}

enum BOOL removeInSingleLinkList(LPSingleLinkList pList, const void *data)
{
	LPSingleLinkListNode pNode;
	SingleLinkListIter iter = &pList->pHead;
	enum BOOL result = False;
	while (*iter != NULL) {
		if (!pList->less(data, (*iter)->data)
		    && !pList->less((*iter)->data, data)) {
			pNode = *iter;
			*iter = (*iter)->pNextNode;
			myFree(pNode->data);
			myFree(pNode);
			result = True;
		} else {
			iter = &(*iter)->pNextNode;
		}
	}

	return result;
}

enum BOOL removeIfInSingleLinkList(LPSingleLinkList pList, Pred pred)
{
	LPSingleLinkListNode pNode;
	SingleLinkListIter iter = &pList->pHead;
	enum BOOL result = False;
	while (*iter != NULL) {
		if (pred(pNode->data)) {
			pNode = *iter;
			*iter = (*iter)->pNextNode;
			myFree(pNode->data);
			myFree(pNode);
			result = True;
		} else {
			iter = &(*iter)->pNextNode;
		}	
	}
	return result;

}

void traverseSingleLinkList(LPSingleLinkList pList, Visitor visitor)
{
	LPSingleLinkListNode pIterNode = pList->pHead;
	while (NULL != pIterNode) {
		visitor(pIterNode->data);
		pIterNode = pIterNode->pNextNode;
	}
}
void sortSingleLinkList(LPSingleLinkList pList)
{
	LPSingleLinkListNode pNode, pNextNode, *ppInsertBefore;
	if (pList->pHead == NULL ||
	    pList->pHead->pNextNode == NULL)
		return;
	pNode = pList->pHead->pNextNode;
	pList->pHead->pNextNode = NULL;
	while (pNode) {
		pNextNode = pNode;
		ppInsertBefore = &pList->pHead;
		while (*ppInsertBefore && !pList->less(pNode->data, (*ppInsertBefore)->data))
			ppInsertBefore = &(*ppInsertBefore)->pNextNode;
		pNode->pNextNode = *ppInsertBefore;
		*ppInsertBefore = pNode;
		pNode = pNextNode;
	}


}

void printSingleLinkList(const LPSingleLinkList pList)
{

	LPSingleLinkListNode pIterNode = pList->pHead;
	const int format = 5;
	int count = 0;
	while (NULL == pIterNode) {
		pList->printer(pIterNode->data);
		++count;
		if (count % format == 0) {
			printf("\n");
		}
		pIterNode = pIterNode->pNextNode;

	}
	if (count % format) {
		printf("\n");
	}

}
void reverseSingleLinkList(LPSingleLinkList pList)
{
	LPSingleLinkListNode pIterNode, pNextNode;
	if (NULL == pList->pHead ||
	    NULL == pList->pHead->pNextNode)
		return;

	pIterNode = pList->pHead->pNextNode;
	pList->pHead->pNextNode = NULL;
	while (pIterNode != NULL) {
		pNextNode = pIterNode->pNextNode;
		pIterNode->pNextNode = pList->pHead;
		pList->pHead = pIterNode;
		pIterNode = pNextNode;

	}

}
