#ifndef _MY_DOUBLE_LINK_LIST_H
#define _MY_DOUBLE_LINK_LIST_H

#include "common.h"

typedef struct _DoubleLinkListNode {
  char *data;
  struct _DoubleLinkListNode *pNext, *pPrev;
}DoubleLinkListNode, *LPDoubleLinkListNode;

typedef struct _DoubleLinkList {
  LPDoubleLinkListNode pHead;
  unsigned int elementSize;
  Printer printer;
  LessFunc less;
  EqualFunc equal;
  unsigned int formatCounter;
}DoubleLinkList, *LPDoubleLinkList;


bool createDoubleLinkList(LPDoubleLinkList *ppList, 
			  unsigned int elementSize,
			  Printer printer,
			  LessFunc less,
			  EqualFunc equal);
void destroyDoubleLinkList(LPSingleLinkList *ppList);
void visitDoubleLinkList(LPSingleLinkList pList, Visitor visitor);
void printDoubleLinkList(const LPSingleLinkList pList, const char *prefix);
void sortDoubleLinkList(LPSingleLinkList pList);

bool insertToHeadOfDoubleLinkList(LPSingleLinkList, const char *);
bool insertToTailOfDoubleLinkList(LPSingleLinkList, const char *);
bool insertAfterDoubleLinkList(LPDoubleLinkList, 
			       LPDoubleLinkListNode, 
			       const char *);
bool insertBeforeDoubleLinkList(LPDoubleLinkList, 
			       LPDoubleLinkListNode *, 
				const char *);
bool removeDataFromDoubleLinkList(LPDoubleLinkList, const char *);
bool removeIfFromDoubleLinkList(LPDoubleLinkList, Pred);
bool removeFromDoubleLinkList(LPDoubleLinkList, LPDoubleLinkListNode *);

LPDoubleLinkList mergeDoubleList(const LPDoubleLinkList ,
				 const LPDoubleLinkList );
LPDoubleLinkList differenceOfDoubleLinkList(const LPDoubleLinkList ,
					    const LPDoubleLinkList );

void reverseDoubleLinkList(LPDoubleLinkList pList);

#endif
