
#include <stdio.h>
#include "common.h"
#include "doubleLinkList.h"
#include "myMemory.h"


enum BOOL
createDoubleLinkList(LPDoubleLinkList *ppList,
                     unsigned int elementSize,
                     Printer printer,
		     Less less)
{
	LPDoubleLinkList pList = (LPDoubleLinkList)myAlloc(sizeof(DoubleLinkList));
	if (NULL == pList) {
		printf("Out Of Memory!");
		return False;
	}
	pList->pHead = (LPDoubleLinkListNode)myAlloc(sizeof(DoubleLinkListNode));
	if (NULL == pList->pHead) {
		printf("Out of Memory!");
		myFree(pList);
		return False;
	}
	pList->pHead->data = NULL;
	pList->pHead->pNextNode = pList->pHead;
	pList->pHead->pPrevNode = pList->pHead;
	pList->elementSize = elementSize;
	pList->printer = printer;
	pList->less = less;
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
		if (pIterNode->data != NULL)
			myFree(pIterNode->data);
		if (pIterNode != NULL)
			myFree(pIterNode);
		pIterNode = pNextNode;

	}
	myFree(pList->pHead);
	pList->pHead = NULL;
	*ppList = NULL;
}

static LPDoubleLinkListNode
createDoubleLinkListNode(const LPDoubleLinkList pList, const void *data)
{
	LPDoubleLinkListNode pNewNode = NULL;
	pNewNode = myAlloc(sizeof(DoubleLinkListNode));
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
	pNewNode->pPrevNode = NULL;
	memcpy(pNewNode->data, data, pList->elementSize);
	return pNewNode;
}
enum BOOL
insertToHeadOfDoubleLinkList(LPDoubleLinkList pList, const void *data)
{
	LPDoubleLinkListNode pNewNode;
	pNewNode = createDoubleLinkListNode(pList,data);
	if (NULL == pNewNode) {
		return False;
	}
	pNewNode->pNextNode = pList->pHead->pNextNode;
	pNewNode->pPrevNode = pList->pHead;
	pList->pHead->pNextNode->pPrevNode = pNewNode;
	pList->pHead->pNextNode = pNewNode;
	return True;
}


enum BOOL
insertToTailOfDoubleLinkList(LPDoubleLinkList pList, const void *data)
{

	LPDoubleLinkListNode pNewNode, *ppInsertPos;
	pNewNode = createDoubleLinkListNode(pList,data);
	if (NULL == pNewNode) {
		return False;
	}
	pNewNode->pNextNode = pList->pHead;
	pNewNode->pPrevNode = pList->pHead->pPrevNode;
	pList->pHead->pPrevNode->pNextNode  = pNewNode;
	pList->pHead->pPrevNode = pNewNode;
	return True;
}

enum BOOL
insertAfterInDoubleLinkList(LPDoubleLinkList pList, const void *data, DoubleLinkListIter iter)
{
	LPDoubleLinkListNode pNewNode;
	pNewNode = createDoubleLinkListNode(pList,data);
	if (NULL == pNewNode) {
		return False;
	}
		
	pNewNode->pNextNode = (*iter)->pNextNode;
	pNewNode->pPrevNode = (*iter);
	(*iter)->pNextNode = pNewNode;
	pNewNode->pNextNode->pPrevNode = pNewNode;
	return True;
}

DoubleLinkListIter findInDoubleLinkList(LPDoubleLinkList pList, const void *key)
{
	DoubleLinkListIter iter = &pList->pHead->pNextNode;
	while (*iter != pList->pHead
		&& !(!pList->less(key, (*iter)->data)
		     && !pList->less((*iter)->data, key)))
		iter = &(*iter)->pNextNode;
	return iter;
		
}
DoubleLinkListIter findIfInDoubleLinkList(LPDoubleLinkList pList, Pred pred)
{
	DoubleLinkListIter iter = &pList->pHead->pNextNode;
	while (*iter != pList->pHead && !pred((*iter)->data)) 
		iter = &(*iter)->pNextNode;
	return iter;


}

enum BOOL removeInDoubleLinkList(LPDoubleLinkList pList, const void *data)
{
	LPDoubleLinkListNode pNode;
	DoubleLinkListIter iter = &pList->pHead->pNextNode;
	enum BOOL result = False;
	while (*iter != NULL) {
		if (!pList->less(data, (*iter)->data)
		    && !pList->less((*iter)->data, data)) {
			pNode = *iter;
			pNode->pNextNode->pPrevNode = pNode->pPrevNode;
			pNode->pPrevNode->pNextNode = pNode->pNextNode;
			
			myFree(pNode->data);
			myFree(pNode);
			result = True;
		} else {
			iter = &(*iter)->pNextNode;
		}
	}

	return result;
}

enum BOOL removeIfInDoubleLinkList(LPDoubleLinkList pList, Pred pred)
{
	LPDoubleLinkListNode pNode;
	DoubleLinkListIter iter = &pList->pHead;
	enum BOOL result = False;
	while (*iter != NULL) {
		if (pred(pNode->data)) {
			pNode = *iter;
			pNode->pNextNode->pPrevNode = pNode->pPrevNode;
			pNode->pPrevNode->pNextNode = pNode->pNextNode;
			myFree(pNode->data);
			myFree(pNode);
			result = True;
		} else {
			iter = &(*iter)->pNextNode;
		}	
	}
	return result;

}

void
traverseDoubleLinkList(LPDoubleLinkList pList, Visitor visitor)
{
	LPDoubleLinkListNode pIterNode = pList->pHead->pNextNode;
	while (pIterNode != pList->pHead) {
		visitor(pIterNode->data);
		pIterNode = pIterNode->pNextNode;
	}
}
void
sortDoubleLinkList(LPDoubleLinkList pList)
{
	LPDoubleLinkListNode pIterNode,pNextNode, pInsertAfter;
	if (pList->pHead->pNextNode == pList->pHead)
		return;
	pIterNode = pList->pHead->pNextNode->pNextNode;
	pList->pHead->pNextNode->pNextNode = pList->pHead;
	pList->pHead->pPrevNode = pList->pHead->pNextNode;

	while (pIterNode != pList->pHead) {
		pNextNode = pIterNode->pNextNode;
		pInsertAfter = pList->pHead;
		while(pInsertAfter->pNextNode != pList->pHead) {
			if (!pList->less(pInsertAfter->pNextNode->data, pIterNode->data))
				break;
			pInsertAfter = pInsertAfter->pNextNode;
		}
		pIterNode->pNextNode = pInsertAfter->pNextNode;
		pIterNode->pPrevNode = pInsertAfter;
		pIterNode->pNextNode->pPrevNode = pIterNode;
		pIterNode->pPrevNode->pNextNode = pIterNode;
		pIterNode = pNextNode;
	}


}

void printDoubleLinkList(const LPDoubleLinkList pList)
{

	LPDoubleLinkListNode pIterNode = pList->pHead->pNextNode;
	const int format = 5;
	int count = 0;
	while (pIterNode != pList->pHead) {
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
void reverseDoubleLinkList(LPDoubleLinkList pList)
{
	LPDoubleLinkListNode pIterNode, pNextNode;
	if (pList->pHead == pList->pHead->pNextNode)
		return;

	pIterNode = pList->pHead->pNextNode->pNextNode;
	pList->pHead->pNextNode->pNextNode = pList->pHead;
	pList->pHead->pPrevNode = pList->pHead->pNextNode;
	while (pIterNode != pList->pHead) {
		pNextNode = pIterNode->pNextNode;
		pIterNode->pNextNode = pList->pHead->pNextNode;
		pIterNode->pPrevNode = pList->pHead;

		pIterNode->pNextNode->pPrevNode = pIterNode;
		pList->pHead->pNextNode = pIterNode;
		pIterNode = pNextNode;

	}

}
