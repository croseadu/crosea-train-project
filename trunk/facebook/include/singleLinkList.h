#ifndef _MY_SINGLE_LINK_LIST_H
#define _MY_SINGLE_LINK_LIST_H

#include "common.h"

typedef struct _SingleLinkListNode {
  char *data;
  struct _SingleLinkListNode *pNext;
}SingleLinkListNode, *LPSingleLinkListNode;

typedef struct _SingleLinkList {
  LPSingleLinkListNode pHead;
  unsigned int elementSize;
  Printer printer;
  LessFunc less;
  EqualFunc equal;
  unsigned int formatCounter;
}SingleLinkList, *LPSingleLinkList;


bool createSingleLinkList(LPSingleLinkList *ppList, 
			  unsigned int elementSize,
			  Printer printer,
			  LessFunc less,
			  EqualFunc equal);
void destroySingleLinkList(LPSingleLinkList *ppList);
void visitSingleLinkList(LPSingleLinkList pList, Visitor visitor);
void printSingleLinkList(const LPSingleLinkList pList, const char *prefix);
void sortSingleLinkList(LPSingleLinkList pList);

bool insertToHeadOfSingleLinkList(LPSingleLinkList, const char *);
bool insertToTailOfSingleLinkList(LPSingleLinkList, const char *);
bool insertAfterSingleLinkList(LPSingleLinkList, 
			       LPSingleLinkListNode, 
			       const char *);
bool insertBeforeSingleLinkList(LPSingleLinkList, 
			       LPSingleLinkListNode *, 
				const char *);
bool removeDataFromSingleLinkList(LPSingleLinkList, const char *);
bool removeIfFromSingleLinkList(LPSingleLinkList, Pred);
bool removeFromSingleLinkList(LPSingleLinkList, LPSingleLinkListNode *);

LPSingleLinkList mergeSingleList(const LPSingleLinkList ,
				 const LPSingleLinkList );
LPSingleLinkList differenceOfSingleLinkList(const LPSingleLinkList ,
					    const LPSingleLinkList );

void reverseSingleLinkList(LPSingleLinkList pList);

#endif
