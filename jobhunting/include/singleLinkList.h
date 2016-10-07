#ifndef _MY_SINGLE_LINK_LIST
#define _MY_SINGLE_LINK_LIST


#include "common.h"

typedef struct _SingleLinkListNode
{
	void *data;
	struct _SingleLinkListNode *pNextNode;

}SingleLinkListNode, *LPSingleLinkListNode;

typedef LPSingleListNode * SingleLinkListIter;

typedef struct _SingleLinkList
{
	LPSingleLinkListNode pHead;
	unsigned int elementSize;
	Printer printer;
}SingleLinkList, *LPSingleLinkList;

BOOL createSingleLinkList(LPSingleLinkList *ppList, unsigned int elementSize, Printer printer);
void destroySingleLinkList(LPSingleLinkList **ppList);

void clearSingleLinkList(LPSingleLinkList pList);

BOOL insertToHeadOfSingleLinkList();
BOOL insertToTailOfSingleLinkList();
BOOL insertBeforeInSingleLinkList();
BOOL insertAfterInSingleLinkList();

SingleLinkListIter findInSingleLinkList();
SingleLinkListIter findIfInSingleLinkList();

void removeInSingleLinkList();
void removeIfInSingleLinkList();


void reverseSingleLinkList();
void uniqueSingleLinkList();
void sortSingleLinkList();


#endif
