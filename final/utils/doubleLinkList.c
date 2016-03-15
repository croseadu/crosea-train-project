#include "doubleLinkList.h"

#include "myMemory.h"


#include <string.h>
#include <stdio.h>
#include <assert.h>



bool
createDoubleLinkList(LPDoubleLinkList *ppList, 
		     unsigned int elementSize,
		     Printer printer,
		     Less less)
{
	LPDoubleLinkList pList = NULL;


	pList = (LPDoubleLinkList)myAlloc(sizeof(DoubleLinkList));
	if (NULL == pList) {
		assert(0 && "Out Of Memory!");
		return False;
	}

	pList->pHead = (LPDoubleLinkListNode)myAlloc(sizeof(DoubleLinkListNode));
	if (NULL == pList->pHead) {
		myFree(pList);
		assert(0 && "out of memory!");
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
	assert(ppList != NULL && *ppList != NULL);
	

	pList = *ppList;
	clearDoubleLinkList(*ppList);
	myFree(pList->pHead);
	pList->pHead = NULL;

	myFree(*ppList);
	*ppList = NULL;
}


void
clearDoubleLinkList(LPDoubleLinkList pList)
{
	LPDoubleLinkListNode pIterNode = pList->pHead;
	LPDoubleLinkListNode pNextNode = NULL;


	while (pIterNode != pList->pHead) {
		pNextNode = pIterNode->pNextNode;
		myFree(pIterNode->data);
		myFree(pIterNode);
		pIterNode = pNextNode;
	} 
}

static LPDoubleLinkListNode
createNewDoubleLinkListNode(const LPDoubleLinkList pList, const void *data)
{
	LPDoubleLinkListNode pNewNode = NULL;

	pNewNode = (LPDoubleLinkListNode)myAlloc(sizeof(DoubleLinkListNode));

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
	pNewNode->pPrevNode = NULL;
	return pNewNode;
}


bool
insertToHeadOfDoubleLinkList(LPDoubleLinkList pList, const void *data)
{
	LPDoubleLinkListNode pNewNode = createNewDoubleLinkListNode(pList, data);

	if (NULL == pNewNode) {
		return False;
	}
	pNewNode->pNextNode = pList->pHead->pNextNode;
	pNewNode->pPrevNode = pList->pHead;
	pNewNode->pNextNode->pPrevNode = pNewNode;
	pNewNode->pPrevNode->pNextNode = pNewNode;	


	return True;

}


bool insertToTailOfDoubleLinkList(LPDoubleLinkList pList, const void *data)
{
	
	LPDoubleLinkListNode pInsertAfter;
	LPDoubleLinkListNode pNewNode = createNewDoubleLinkListNode(pList, data);

	if (NULL == pNewNode) {
		return False;
	}
	pInsertAfter = pList->pHead->pPrevNode;

	pNewNode->pNextNode = pInsertAfter->pNextNode;
	pNewNode->pPrevNode = pInsertAfter;

	pNewNode->pNextNode->pPrevNode = pNewNode;
	pNewNode->pPrevNode->pNextNode = pNewNode;	


	return True;

}



bool
insertBeforeInDoubleLinkList(LPDoubleLinkList pList, const void *data, IteratorOfDoubleLinkList it)
{
	
	LPDoubleLinkListNode pNewNode = createNewDoubleLinkListNode(pList, data);

	if (NULL == pNewNode) {
		return False;
	}

	pNewNode->pNextNode = *it;
	pNewNode->pPrevNode = (*it)->pPrevNode;
	pNewNode->pNextNode->pPrevNode = pNewNode;
	pNewNode->pPrevNode->pNextNode = pNewNode;	

	return True;	
}


bool insertAfterInDoubleLinkList(LPDoubleLinkList pList, const void *data, IteratorOfDoubleLinkList it)
{
	
	LPDoubleLinkListNode pNewNode = createNewDoubleLinkListNode(pList, data);

	if (NULL == pNewNode) {
		return False;
	}

	pNewNode->pNextNode = (*it)->pNextNode;
	pNewNode->pPrevNode = *it;
	pNewNode->pNextNode->pPrevNode = pNewNode;
	pNewNode->pPrevNode->pNextNode = pNewNode;	

	return True;
}

IteratorOfDoubleLinkList
findInDoubleLinkList(LPDoubleLinkList pList, const void *data)
{
	IteratorOfDoubleLinkList it;

	it = &(pList->pHead->pNextNode);
	while (*it != pList->pHead && 
		( pList->less((*it)->data, data) || pList->less(data, (*it)->data) )) {
		it = &((*it)->pNextNode);
	}
	return it;
}


IteratorOfDoubleLinkList
findIfInDoubleLinkList(LPDoubleLinkList pList, Pred pred)
{

	IteratorOfDoubleLinkList it;

	it = &(pList->pHead->pNextNode);
	while (*it != pList->pHead && pred((*it)->data) == False ) {
		it = &((*it)->pNextNode);
	}
	return it;
}

bool
removeInDoubleLinkList(LPDoubleLinkList pList, const void *data)
{
	IteratorOfDoubleLinkList it;
	LPDoubleLinkListNode pRemovedNode;
	it = &(pList->pHead->pNextNode);
	bool found = False;
	while (*it != pList->pHead) {
		if (pList->less((*it)->data, data) == False && pList->less(data, (*it)->data) == False) {
			pRemovedNode = *it;
			*it = pRemovedNode->pNextNode;
			(*it)->pPrevNode = pRemovedNode->pPrevNode;


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
removeIfInDoubleLinkList(LPDoubleLinkList pList, Pred pred)
{

	IteratorOfDoubleLinkList it;
	LPDoubleLinkListNode pRemovedNode;
	it = &pList->pHead;
	bool found = False;
	while (*it != NULL) {
		if (pred((*it)->data) == True) {
			pRemovedNode = *it;
			*it = pRemovedNode->pNextNode;
			(*it)->pPrevNode = pRemovedNode->pPrevNode;


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
eraseFromDoubleLinkList(LPDoubleLinkList pList, IteratorOfDoubleLinkList it)
{
	LPDoubleLinkListNode pRemovedNode = *it;
	*it = pRemovedNode->pNextNode;
	(*it)->pPrevNode = pRemovedNode->pPrevNode;

	myFree(pRemovedNode->data);
	myFree(pRemovedNode);

	return True;
}


bool
isDoubleLinkListEmpty(const LPDoubleLinkList pList)
{
	return pList->pHead->pNextNode == pList->pHead ? True : False;
}

void
sortDoubleLinkList(LPDoubleLinkList pList)
{
	LPDoubleLinkListNode pIterNode, pNextNode;
	IteratorOfDoubleLinkList it;

	if (NULL == pList->pHead) {
		return;
	}

	pIterNode = pList->pHead->pNextNode;
	pList->pHead->pNextNode = pList->pHead;
	pList->pHead->pPrevNode = pList->pHead;
	while (pIterNode != pList->pHead) {
		it = &pList->pHead->pNextNode;
		while (*it != pList->pHead && pList->less((*it)->data, pIterNode->data) == True) {
			it = &((*it)->pNextNode);
		}
		pNextNode = pIterNode->pNextNode;
		pIterNode->pNextNode = (*it);
		pIterNode->pPrevNode = (*it)->pPrevNode;		

		pIterNode->pPrevNode->pNextNode = pIterNode;
		pIterNode->pNextNode->pPrevNode = pIterNode;

		pIterNode = pNextNode;
	}

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

void uniqueDoubleLinkList(LPDoubleLinkList pList)
{
	IteratorOfDoubleLinkList last = &pList->pHead->pNextNode;
	LPDoubleLinkListNode pRemovedNode;	
	IteratorOfDoubleLinkList it;		

	if (pList->pHead->pNextNode == pList->pHead ||
	    pList->pHead->pNextNode->pNextNode == pList->pHead)
		return;

	it = &pList->pHead->pNextNode->pNextNode;
	
	while (*it != pList->pHead) {
		if (!pList->less((*it)->data, (*last)->data) && !pList->less((*last)->data, (*it)->data)) {
			pRemovedNode = *it;
			(*it)->pPrevNode = pRemovedNode->pPrevNode;
			*it = pRemovedNode->pNextNode;
			
			myFree(pRemovedNode->data);
			myFree(pRemovedNode);
			
		} else {
			it = &((*it)->pNextNode); 
		}
	}

}





