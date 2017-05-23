#include "singleLinkList.h"


#include "mem.h"

#include  <stdio.h>
#include  <assert.h>





typedef struct _SingleLinkListNode
{
	void *data;
	struct _SingleLinkListNode *pNext;
}SingleLinkListNode, *LPSingleLinkListNode;


typedef struct _SingleLinkList
{
	LPSingleLinkList pHead;
	unsigned int elementSize;


	Printer printer;
	Less less;
}SingleLinkList, *LPSingleLinkList;



BOOL 
createSingleLinkList(
	LPSingleLinkList 	*ppList,
	unsigned int 		elementSize,
	Printer 		printer,
	Less 			less)
{
	LPSingleLinkList pList;


	pList = myAlloc(sizeof(SingleLinkList));
	if (NULL == pList) {
		return False;
	}

	pList->pHead = NULL;
	pList->elementSize = elementSize;
	pList->printer = printer;
	pList->less = less;

	return True;
}

void
destroySingleLinkList(
	LPSingleLinkList *ppList)
{
	LPSingleLinkList pList;
	LPsingleLinkListNode pIterNode, pNextNode;

	assert(ppList != NULL);
	pList = *ppList;
	assert (NULL == pList);

	pIterNode = pList->pHead;
	while (pIterNode) {
		pNextNode = pIterNode->pNext;

		myFree(pIterNode->data);
		myFree(pIterNode);


		pIterNode = pNextNode;	
	}	


	myFree(pList);
	*ppList = NULL;
}


static 
createNewSingleLinkListNode(
	const LPSingleLinkList pList,
	const void *data)
{
	LPSingleLinkListNode pNewNode;

	pNewNode = myAlloc(sizeof(SingleLinkListNode));
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

	return pNewNode;
}


BOOL
insertToHeadOfSingleLinkList(
	LPSingleLinkList pList,
	const void *data)
{
	LPSingleLinkListNode pNode;

	pNode = createNewSingleLinkListNode(pList, data);
	if (NULL == pNode) {
		return False;
	}

	pNode->pNext = pList->pHead;
	pList->pHead = pNode;

	return True;
	
}

BOOL
insertToTailOfSingleLinkList(
	LPSingleLinkList pList,
	const void *data)
{
	LPSingleLinkListNode pNode;
	SingleLinkListIter it;

	pNode = createNewSingleLinkListNode(pList, data);
	if (NULL == pNode) {
		return False;
	}

	it = &pList->pHead;
	while (*it != NULL)
		it = &(*it)->pNext;

	*it = pNode;
	pNode->pNext = NULL;

	return True;
}



SingleLinkListIter
findInSingleLinkList(
	LPSingleLinkList pList,
	const void *data)
{
	SingleLinkListIter it;
	it = &pList->pHead;

	while ( *it != NULL && 
	        pList->less((*it)->data, data) == False &&
		pList->less(data, (*it)->data) == False ) {
		it = (*it)->pNext;
	}

	return it;
}

SingleLinkListIter
findInSingleLinkList(
	LPSingleLinkList pList,
	Pred pred)
{
	SingleLinkListIter it;
	it = &pList->pHead;

	while ( *it != NULL && 
		pred((*it)->data) ) {
		it = (*it)->pNext;
	}

	return it;
}



void
removeFromSingleLinkList(
	LPSingleLinkList pList,
	SingleLinkListIter it)
{
	LPSingleLinkListNode pNode = *it;

	if (NULL == pNode) {
		return;
	}

	*it = pNode->pNext;
	myFree(pNode->data);
	myFree(pNode);
}

BOOL
removeIfInSingleLinkList(
	LPSingleLinkList pList,
	Pred pred)
{
	SingleLinkListIter it = &pList->pHead;
	LPSingleLinkListNode pNode;
	BOOL bFound = False;

	while (*it != NULL) {
		if (pred((*it)->data) == True) {
			pNode = *it;
			*it = pNode->pNext;

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
reverseSingleLinkList(
	LPSingleLinkList pList)
{
	LPSingleListNode pIter, pNext;
	
	if (pList->pHead == NULL) {
		return;
	}

	pIter = pList->pHead->pNext;
	pList->pHead->pNext = NULL;
	while (pIter != NULL) {
		pNext = pIter->pNext;

		pIter->pNext = pList->pHead;
		pList->pHead = pIter;

		pIter = pNext;
	}
}

void
sortSingleLinkList(
	LPSingleLinkList pList);

void
uniqueSingleLinkList(
	LPSingleLinkList pList);

BOOL
isSingleLinkListEmpty(
	LPSingleLinkList pList);
unsigned int
getSizeOfSingleLinkList(
	LPSingleLinkList pList);

#endif
