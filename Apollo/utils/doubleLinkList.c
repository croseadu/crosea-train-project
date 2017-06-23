#include "doubleLinkList.h"


#include "memory.h"

#include  <stdio.h>
#include  <assert.h>
#include  <string.h>

BOOL 
createDoubleLinkList(
	LPDoubleLinkList 	*ppList,
	unsigned int 		elementSize,
	Printer 		printer,
	Less 			less)
{
	LPDoubleLinkList pList;


	pList = myAlloc(sizeof(DoubleLinkList));
	if (NULL == pList) {
		return False;
	}

	pList->pHead = myAlloc(sizeof(DoubleLinkListNode));
	if (NULL == pList->pHead) {
		myFree(pList);
		return False;
	}
	pList->pHead->data = NULL;
	pList->pHead->pPrev = pList->pHead;
	pList->pHead->pNext = pList->pHead;

	pList->elementSize = elementSize;
	pList->printer = printer;
	pList->less = less;

	*ppList = pList;
	return True;
}

void
clearDoubleLinkList(
	LPDoubleLinkList pList)
{
	LPDoubleLinkListNode pIterNode, pNextNode;


	pIterNode = pList->pHead->pNext;
	while (pIterNode != pList->pHead) {
		pNextNode = pIterNode->pNext;

		myFree(pIterNode->data);
		myFree(pIterNode);


		pIterNode = pNextNode;	
	}	


}

void
destroyDoubleLinkList(
	LPDoubleLinkList *ppList)
{
	LPDoubleLinkList pList;

	assert(ppList != NULL);
	pList = *ppList;
	assert (NULL != pList);

	myFree(pList->pHead);
	myFree(pList);
	*ppList = NULL;
}


static LPDoubleLinkListNode
createNewDoubleLinkListNode(
	const LPDoubleLinkList pList,
	const void *data)
{
	LPDoubleLinkListNode pNewNode;

	pNewNode = myAlloc(sizeof(DoubleLinkListNode));
	if (NULL == pNewNode)
		return NULL;

	pNewNode->data = myAlloc(pList->elementSize);
	if (NULL == pNewNode->data) {
		assert(0 && "Out Of memory");
		myFree(pNewNode);
		return NULL;
	}

	memcpy(pNewNode->data, data, pList->elementSize);
	pNewNode->pNext = NULL;
	pNewNode->pPrev = NULL;
	return pNewNode;
}


BOOL
insertToHeadOfDoubleLinkList(
	LPDoubleLinkList pList,
	const void *data)
{
	LPDoubleLinkListNode pNode;

	pNode = createNewDoubleLinkListNode(pList, data);
	if (NULL == pNode) {
		return False;
	}

	pNode->pNext = pList->pHead->pNext;
	pNode->pPrev = pList->pHead;

	pNode->pPrev->pNext = pNode;
	pNode->pNext->pPrev = pNode;

	return True;
	
}

BOOL
insertToTailOfDoubleLinkList(
	LPDoubleLinkList pList,
	const void *data)
{
	LPDoubleLinkListNode pNode;

	pNode = createNewDoubleLinkListNode(pList, data);
	if (NULL == pNode) {
		return False;
	}

	pNode->pNext = pList->pHead;
	pNode->pPrev = pList->pHead->pPrev;

	pNode->pPrev->pNext = pNode;
	pNode->pNext->pPrev = pNode;

	return True;
}



DoubleLinkListIter
findInDoubleLinkList(
	LPDoubleLinkList pList,
	const void *data)
{
	DoubleLinkListIter it;
	it = &pList->pHead->pNext;

	while ( *it != pList->pHead && 
	        pList->less((*it)->data, data) == False &&
		pList->less(data, (*it)->data) == False ) {
		it = &(*it)->pNext;
	}

	return it;
}

DoubleLinkListIter
findIfInDoubleLinkList(
	LPDoubleLinkList pList,
	Pred pred)
{
	DoubleLinkListIter it;
	it = &pList->pHead->pNext;

	while ( *it != pList->pHead && 
		pred((*it)->data) ) {
		it = &(*it)->pNext;
	}

	return it;
}



void
removeFromDoubleLinkList(
	LPDoubleLinkList pList,
	DoubleLinkListIter it)
{
	LPDoubleLinkListNode pNode = *it;

	if (NULL == pNode) {
		return;
	}

	*it = pNode->pNext;
	pNode->pNext->pPrev = pNode->pPrev;

	myFree(pNode->data);
	myFree(pNode);
}

BOOL
removeIfInDoubleLinkList(
	LPDoubleLinkList pList,
	Pred pred)
{
	DoubleLinkListIter it = &pList->pHead->pNext;
	LPDoubleLinkListNode pNode;
	BOOL bFound = False;

	while (*it != pList->pHead) {
		if (pred((*it)->data) == True) {
			pNode = *it;
			*it = pNode->pNext;
			pNode->pNext->pPrev = pNode->pPrev;

			myFree(pNode->data);
			myFree(pNode);

			bFound = True;
		} else {
			it = &(*it)->pNext;
		}

	}

	return bFound;
}



void
reverseDoubleLinkList(
	LPDoubleLinkList pList)
{
	LPDoubleLinkListNode pIter, pNext;
	
	if (pList->pHead == NULL) {
		return;
	}

	pIter = pList->pHead->pNext;
	pList->pHead->pNext = pList->pHead;
	pList->pHead->pPrev = pList->pHead;

	while (pIter != pList->pHead) {
		pNext = pIter->pNext;

		pIter->pNext = pList->pHead->pNext;
		pIter->pPrev = pList->pHead;		


		pIter->pPrev->pNext = pIter;
		pIter->pNext->pPrev = pIter;

		pIter = pNext;
	}
}


static void
insertSortDoubleLinkList(
	LPDoubleLinkList pList)
{
	LPDoubleLinkListNode pIterNode, pNextNode;
	DoubleLinkListIter it;

	if (pList->pHead->pNext == pList->pHead)
		return;

	pIterNode = pList->pHead->pNext->pNext;
	if (pIterNode == pList->pHead)
		return;

	pList->pHead->pNext->pNext = pList->pHead;
	pList->pHead->pPrev = pList->pHead->pNext;

	while (pIterNode != pList->pHead) {
			pNextNode = pIterNode->pNext;
	
			it = &pList->pHead->pNext;
			while (*it != pList->pHead && pList->less((*it)->data, pIterNode->data) == True)
				it = &(*it)->pNext;

			pIterNode->pNext = *it;
			pIterNode->pPrev = (*it)->pPrev;

			*it = pIterNode;
			pIterNode->pNext->pPrev = pIterNode;	

	
			pIterNode = pNextNode;
	}
	
	
}

void
sortDoubleLinkList(
	LPDoubleLinkList pList)
{
	insertSortDoubleLinkList(pList);
}

void
uniqueDoubleLinkList(
	LPDoubleLinkList pList)
{
	DoubleLinkListIter it = &pList->pHead->pNext;
	LPDoubleLinkListNode pNode = NULL;

	if (*it == pList->pHead)
		return;

	it = &(*it)->pNext;

	while (*it != pList->pHead) {
		if (pList->less((*it)->data, (*it)->pPrev->data) == False &&
		    pList->less((*it)->pPrev->data, (*it)->data) == False) {
			pNode = *it;
			pNode->pPrev->pNext = pNode->pNext;
			pNode->pNext->pPrev = pNode->pPrev;

			myFree(pNode->data);
			myFree(pNode); 
		} else {
			it = &(*it)->pNext;
		}
	}

}

BOOL
isDoubleLinkListEmpty(
	LPDoubleLinkList pList)
{
	return (pList->pHead->pNext == pList->pHead) ? True : False;
}

unsigned int
getSizeOfDoubleLinkList(
	LPDoubleLinkList pList)
{
	unsigned int count = 0;
	LPDoubleLinkListNode pIter = pList->pHead->pNext;

	while (pIter != pList->pHead) {
		++count;
		pIter = pIter->pNext;
	}	
}

void
dumpDoubleLinkList(
	const LPDoubleLinkList pList,
	const char *separator,
	unsigned int itemsPerLine)
{
	unsigned int count = 0;
	LPDoubleLinkListNode pIterNode;

	printf("\n");



	pIterNode = pList->pHead->pNext;
	while (pIterNode != pList->pHead) {
		pList->printer(pIterNode->data);	
		printf("%s", separator);
		++count;
		if (count % itemsPerLine == 0) {
			printf("\n");
		}
		pIterNode = pIterNode->pNext;
	}

	if (count  % itemsPerLine) {
		printf("\n");
	}

}
void
getFrontOfDoubleLinkList(
	LPDoubleLinkList pList,
	void *data)
{
	LPDoubleLinkListNode pNode = pList->pHead->pNext;

	assert(pNode != pList->pHead);

	memcpy(data, pNode->data, pList->elementSize);
}

void
getBackOfDoubleLinkList(
	LPDoubleLinkList pList,
	void *data)
{

	LPDoubleLinkListNode pNode = pList->pHead->pPrev;

	assert(pNode != pList->pHead);

	memcpy(data, pNode->data, pList->elementSize);
}

void
removeHeadFromDoubleLinkList(
	LPDoubleLinkList pList)
{
	DoubleLinkListIter it;

	assert(pList->pHead->pNext != pList->pHead);
	it = &pList->pHead->pNext;

	removeFromDoubleLinkList(pList, it);
}




