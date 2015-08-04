#include "set.h"
#include <assert.h>
#include "myMemory.h"


enum BOOL
createSet(LPSet *ppSet,
          unsigned int keySize,
	  Less less, 
	  Printer printer)
{
	LPSet pSet;


	pSet = (LPSet)myAlloc(sizeof(Set));	
	if (NULL == pSet) {
		printf("out of memory!");
		return False;

	}
	pSet->pHead = NULL;
	pSet->elementSize = keySize;
	pSet->less = less;
	pSet->printer = printer;
	pSet->size = 0;

	*ppSet = pSet;
	return True;
}

void
destroySet(LPSet *ppSet)
{
	LPSet pSet = *ppSet;
	LPSetInternalNode pIterNode, pNextNode;	

	if (NULL == pSet)
		return;

	pIterNode = pSet->pHead;
	while (pIterNode != NULL) {
		pNextNode = pIterNode->pNextNode;
		myFree(pIterNode->data);
		myFree(pIterNode);
		pIterNode = pNextNode;
	}	

	*ppSet = NULL;
}

enum BOOL
isSetEmpty(const LPSet pSet)
{
	return pSet->size == 0;

}

unsigned int
getSizeOfSet(const LPSet pSet)
{

	return pSet->size;
}


enum BOOL
insertToSet(LPSet pSet,
	    const void *data)
{
	LPSetInternalNode pNewNode;


	pNewNode = (LPSetInternalNode)myAlloc(sizeof(SetInternalNode));
	if (NULL == pNewNode)
		return False;

	mempcy(pNewNode->data, data, pSet->elementSize);
	pNewNode->pNextNode = pSet->pHead;
	pSet->pHead = pNewNode;

	return True;	
}

enum BOOL
eraseFromSet(LPSet pSet,
             SetIter iter)
{
	LPSetInternalNode pNode = *iter;
	(*iter) = (*iter)->pNextNode;
	myFree(pNode->data);
	myFree(pNode);
	return True;
}

enum BOOL
removeFromSet(LPSet pSet,
              const void *key)
{
	LPSetInternalNode * ppIterNode  = &pSet->pHead;
	LPSetInternalNode pRemoveNode;	

	while (*ppIterNode != NULL) {
		if (!pSet->less((*ppIterNode)->data, key) && !pSet->less(key, (*ppIterNode)->data)) {
			pRemoveNode = *ppIterNode;

			(*ppIterNode) = pRemoveNode->pNextNode;

			myFree(pRemoveNode->data);
			myFree(pRemoveNode);

			return True;
		}
		ppIterNode = &(*ppIterNode)->pNextNode;
	}
		
	return False;
}

SetIter
findInSet(LPSet pSet, const void *key)
{
	LPSetInternalNode * ppIterNode = &pSet->pHead;

	while (*ppIterNode != NULL) {
		if (!pSet->less((*ppIterNode)->data, key) && !pSet->less(key, (*ppIterNode)->data)) {
			return ppIterNode;
		}
		ppIterNode =&(*ppIterNode)->pNextNode;
	}
	
	return NULL;
}

unsigned int
countInSet(LPSet pSet, const void *key)
{
	if (findInSet(pSet, key) != NULL)
		return 1;
	return 0;

}

