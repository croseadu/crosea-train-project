#include "singleLinkList.h"

#include "myMemory.h"

#include <stdio.h>
#include <assert.h>



bool
createSingleLinkList(LPSingleLinkList *ppList, 
		     unsigned int elementSize,
		     Printer printer,
		     Less less)
{
	LPSingleLinkList pList = NULL;


	pList = (LPSingleLinkList)myAlloc(sizeof(SingleLinkList));
	if (NULL == pList) {
		assert(0 && "Out Of Memory!");
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
	assert(ppList != NULL && *ppList != NULL);
	clearSingleLinkList(*ppList);

	myFree(*ppList);
	*ppList = NULL;
}


void
clearSingleLinkList(LPSingleLinkList pList)
{
	LPSingleLinkListNode pIterNode = pList->pHead;
	LPSingleLinkListNode pNextNode = NULL;


	while (pIterNode != NULL) {
		pNextNode = pIterNode->pNextNode;
		myFree(pIterNode->data);
		myFree(pIterNode);
		pIterNode = pNextNode;
	} 
}

static LPSingleLinkListNode
createNewSingleLinkListNode(const LPSingleLinkList pList, const void *data)
{
	LPSingleLinkListNode pNewNode = NULL;

	pNewNode = (LPSingleLinkListNode)myAlloc(sizeof(SingleLinkListNode));

	if (NULL == pNewNode) {
		assert (0 && "Out Of Memory!");
		return NULL;
	}
	pNewNode->data = myAlloc(pList->elementSize);
	if (NULL == pNewNode->data) {
		myFree(pNewNode);
		assert(0 && "Out Of Memory");
		return NULL;
	}

	memcpy(pNewNode->data, data, pList->elementSize);
	pNewNode->pNextNode = NULL;
	
	return pNewNode;
}


bool
insertToHeadOfSingleLinkList(LPSingleLinkList pList, const void *data)
{
	LPSingleLinkListNode pNewNode = createNewSingleLinkList(pList, data);

	if (NULL == pNewNode) {
		return False;
	}
	pNewNode->pNextNode = pList->pHead;
	pList->pHead = pNewNode;

	return True;

}


bool insertToTailOfSingleLinkList(LPSingleLinkList pList, const void *data)
{
	
	LPSingleLinkListNode *ppInsertAfter;
	LPSingleLinkListNode pNewNode = createNewSingleLinkList(pList, data);

	if (NULL == pNewNode) {
		return False;
	}
	ppInsertAfter = &pList->pHead;
	while (*ppInsertAfter != NULL) {
		ppInsertAfter = &((*ppInsertAfter)->pNextNode);
	}
	*ppInsertAfter = pNewNode;

	return True;

}



bool
insertBeforeInSingleLinkList(LPSingleLinkList pList, const void *data, IterOfSingleLinkList it)
{
	
	LPSingleLinkListNode *ppInsertAfter;
	LPSingleLinkListNode pNewNode = createNewSingleLinkList(pList, data);

	if (NULL == pNewNode) {
		return False;
	}

	pNewNode->pNextNode = *it;
	*it = pNewNode;

	return True;
	
}


bool insertAfterInSingleLinkList(LPSingleLinkList pList, const void *data, IterOfSingleLinkList);
{
	
	LPSingleLinkListNode *ppInsertAfter;
	LPSingleLinkListNode pNewNode = createNewSingleLinkList(pList, data);

	if (NULL == pNewNode) {
		return False;
	}

	pNewNode->pNextNode = *it;
	*it = pNewNode;

	return True;
}

IterOfSingleLinkList
findInSingleLinkList(LPSingleLinkList pList, const void *data)
{
	IterOfSingleLinkList it;

	it = &pList->pHead;
	while (*it && 
		( pList->less((*it)->data, data) || pList->less(data, (*it)->data) )) {
		it = &((*it)->pNextNode);
	}
	return it;
}


IterOfSingleLinkList
findIfInSingleLinkList(LPSingleLinkList pList, Pred pred)
{

	IterOfSingleLinkList it;

	it = &pList->pHead;
	while (*it && pred((*it)->data) == False ) {
		it = &((*it)->pNextNode);
	}
	return it;
}

bool
removeInSingleLinkList(LPSingleLinkList pList, const void *data)
{
	IterOfSingleLinkList it;
	LPSingleLinkListNode pRemovedNode;
	it = &pList->pHead;
	bool found = False;
	while (*it != NULL) {
		if (pList->less((*it)->data, data) == False && pList->less(data, (*it)->data) == False) {
			pRemovedNode = *it;
			*it = (*it)->pNextNode;
			myFree(pRemovedNode->data);
			myFree(pRemovedNode);
			found = True;
		} else {
			it = &((*it)->pNextNode);
		}
	}
	
	return found;
}

bool
removeIfInSingleLinkList(LPSingleLinkList pList, Pred pred)
{

	IterOfSingleLinkList it;
	LPSingleLinkListNode pRemovedNode;
	it = &pList->pHead;
	bool found = False;
	while (*it != NULL) {
		if (pred((*it)->data) == True) {
			pRemovedNode = *it;
			*it = (*it)->pNextNode;
			myFree(pRemovedNode->data);
			myFree(pRemovedNode);
			found = True;
		} else {
			it = &((*it)->pNextNode);
		}
	}
	
	return found;
}

bool
eraseFromSingleLinkList(LPSingleLinkList pList, IterOfSingleLinkList iter)
{
	LPSingleLinkListNode pRemoveNode = *iter;
	*iter = pRemoveNode->pNextNode;

	myFree(pRemoveNode->data);
	myFree(pRemoveNode);

	return True;
}


bool
isSingleLinkListEmpty(const LPSingleLinkList pList)
{
	return pList->pHead == NULL ? True : False;
}

void
sortSingleLinkList(LPSingleLinkList pList)
{
	LPSingleLinkListNode pIterNode, pNextNode;
	IterOfSingleLinkList it;

	if (NULL == pList->pHead) {
		return;
	}

	pIterNode = pList->pHead->pNextNode;
	pList->phead->pNextNode = NULL;
	while (pIterNode != NULL) {
		it = &pList->pHead;
		while (*it != NULL && pList->less((*it)->data,data) == True) {
			it = &((*it)->pNextNode);
		}
		*it = pIterNode;
		pNextNode = pIterNode->pNextNode;
		pIterNode->pNextNode = NULL;
		pIterNode = pNextNode;
	}

}

void traverseSingleLinkList(LPSingleLinkList)
{

}

void uniqueSingleLinkList(LPSingleLinkList pList)
{


}





