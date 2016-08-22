
#ifndef _My_DOUBLE_LINK_LIST
#define _MY_DOUBLE_LINK_LIST

#include "common.h"



typedef struct _DoubleLinkListNode
{
	void *data;
	struct _DoubleLinkListNode *pNext;
	struct _DoubleLinkListNode *pPrev;
}DoubleLinkListNode, *LPDoubleLinkListNode;

typedef LPDoubleLinkListNode * DoubleLinkListIter;


typdef struct _DoubleLinkList
{
	LPDoubleLinkList pHead;
	unsigned int elementSize;
	Less less;
	Printer printer;
}DoubleLinkList, *LPDoubleLinkList;


BOOL
createDoubleLinkList(LPDoubleLinkList *ppList,
	             unsigned int elementSize,
		     Less less,
		     Printer printer);

void
destroyDoubleLinkList(LPDoubleLinkList *ppList);


BOOL
insertToHeadOfDoubleLinkList(LPDoubleLinkList, const void *data);
BOOL
insertToTailOfDoubleLinkList(LPDoubleLinkList, const void *data);
BOOL
insertAfterInDoubleLinkList(LPDoubleLinkList, DoubleLinkListIter, const void *data);
BOOL
insertBeforeInDoubleLinkList(LPDoubleLinkList, DoubleLinkListIter, const void *data);

void 
getHeadOfDoubleLinkList(LPDoubleLinkList, void *data);
void
getTailOfDoubleLinkList(LPDoubleLinkList, void *data);

void
removeHeadFromDoubleLinkList(LPDoubleLinkList);
void
removeTailFromDoubleLinkList(LPDoubleLinkList);



DoubleLinkListIter
findInDoubleLinkList(LPDoubleLinkList, const void *);

DoubleLinkListIter
findIfInDoubleLinkList(LPDoubleLinkList, Pred);

BOOL
removeInDoubleLinkList(LPDoubleLinkList, const void *);
BOOL
removeIfInDoubleLinkList(LPDoubleLinkList, Pred);
void
eraseFromDoubleLinkList(LPDoubleLinkList, DoubleLinkListIter);


void
sortDoubleLinkList(LPDoubleLinkList);

void
uniqueDoubleLinkList(LPDoubleLinkList);

void
traverseDoubleLinkList(LPDoubleLinkList, Visitor visitor);

BOOL
isDoubleLinkListEmpty(const LPDoubleLinkList pList);

unsigned int
getSizeOfDoubleLinkList(const LPDoubleLinkList pList);





#endif
