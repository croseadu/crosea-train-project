#ifndef _MY_SINGLE_LINK_LIST_H
#define _MY_SINGLE_LINK_LIST_H

#include "common.h"

typedef struct _SingleLinkListNode
{
	char *data;
	struct _SingleLinkListNode *pNext;
}SingleLinkListNode, *LPSingleLinkListNode;



typedef struct _SingleLinkList
{
	LPSingleLinkListNode 	pHead;
	unsigned int 		elementSize;

	Printer 		printer;
	Less			less;

}SingleLinkList, *LPSingleLinkList;


BOOL createSingleLinkList(LPSingleLinkList *ppList,
			  unsigned int elementSize,
			  Printer printer,
			  Less less);

void clearSingleLinkList(LPSingleLinkList);
void destroySingleLinkList(LPSingleLinkList *ppList);


void traverseSingleLinkList(LPSingleLinkList, Visitor visitor);
void sortSingleLinkList(LPSingleLinkList);


void printSingleLinkList(const LPSingleLinkList);


LPSingleLinkListNode *findInSingleLinkList(LPSingleLinkList, const void *ref);

LPSingleLinkListNode *findIfInSingleLinkList(LPSingleLinkList, Pred pred);

void uniqueSingleLinkList(LPSingleLinkList);
BOOL removeInSingleLinkList(LPSingleLinkList, const void *ref);
BOOL removeIfInSingleLinkList(LPSingleLinkList, Pred pred);

BOOL insertToHeadOfSingleLinkList(LPSingleLinkList, const void *data);
BOOL insertToTailOfSingleLinkList(LPSingleLinkList, const void *data);
BOOL insertAfterInSingleLinkList(LPSingleLinkList, LPSingleLinkListNode *ppInsertPos, const void *);
BOOL insertBeforeInSingleLinkList(LPSingleLinkList, LPSingleLinkListNode *ppInsertPos, const void *);



#endif
