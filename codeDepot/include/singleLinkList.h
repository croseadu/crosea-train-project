#ifndef _My_SINGLE_LINK_LIST
#define _MY_SINGLE_LINK_LIST

#include "common.h"



typedef struct _SingleLinkListNode
{
	void *data;
	struct _SingleLinkListNode *pNext;
}SingleLinkListNode, *LPSingleLinkListNode;

typedef LPSingleLinkListNode * SingleLinkListIter;


typedef struct _SingleLinkList
{
	LPSingleLinkListNode pHead;
	unsigned int elementSize;
	Less less;
	Printer printer;
}SingleLinkList, *LPSingleLinkList;


BOOL
createSingleLinkList(LPSingleLinkList *ppList,
	             unsigned int elementSize,
		     Less less,
		     Printer printer);

void
destroySingleLinkList(LPSingleLinkList *ppList);


BOOL
insertToHeadOfSingleLinkList(LPSingleLinkList, const void *data);
BOOL
insertToTailOfSingleLinkList(LPSingleLinkList, const void *data);
BOOL
insertAfterInSingleLinkList(LPSingleLinkList, SingleLinkListIter, const void *data);
BOOL
insertBeforeInSingleLinkList(LPSingleLinkList, SingleLinkListIter, const void *data);


SingleLinkListIter
findInSingleLinkList(LPSingleLinkList, const void *);

SingleLinkListIter
findIfInSingleLinkList(LPSingleLinkList, Pred);

BOOL
removeInSingleLinkList(LPSingleLinkList, const void *);
BOOL
removeIfInSingleLinkList(LPSingleLinkList, Pred);
void
eraseFromSingleLinkList(LPSingleLinkList, SingleLinkListIter);


void
sortSingleLinkList(LPSingleLinkList);

void
uniqueSingleLinkList(LPSingleLinkList);

void
traverseSingleLinkList(LPSingleLinkList, Visitor visitor);

BOOL 
isSingleLinkListEmpty(const LPSingleLinkList pList);

unsigned int
getSizeOfSingleLinkList(const LPSingleLinkList pList);
#endif
