#ifndef _MY_SINGLE_LINK_LIST_H
#define _MY_SINGLE_LINK_LIST_H

#include "common.h"

typedef struct _SingleLinkListNode
{
  void *data;
  struct _SingleLinkListNode *pNextNode;
}SingleLinkListNode, *LPSingleLinkListNode;

typedef LPSingleLinkListNode * SingleLinkListNodeIter;

typedef struct _SingleLinkList
{
  LPSingleLinkListNode pHead;
  unsigned int elementSize;
  PrintFunc printer;
  LessFunc less;
  EqualFunc equal;
}SingleLinkList, *LPSingleLinkList;

BOOL createSingleLinkList(LPSingleLinkList *ppList,
			  unsigned int elementSize,
			  PrintFunc printer,
			  LessFunc less,
			  EqualFunc equal);
void destroySingleLinkList(LPSingleLinkList *ppList);

BOOL insertToHeadOfSingleLinkList(LPSingleLinkList pList,
				  void *elementData);
BOOL insertToTailOfSingleLinkList(LPSingleLinkList pList,
				  void *elementData);
BOOL insertAfterInSingleLinkList(LPSingleLinkList pList,
				 void *elementData,
				 SingleLinkListNodeIter pPos);
BOOL insertBeforeInSingleLinkList(LPSingleLinkList pList,
				  void *elementData,
				  SingleLinkListNodeIter pPos);
SingleLinkListNodeIter findInSingleLinkList(LPSingleLinkList pList,
					    void *keyData);
BOOL removeInSingleLinkListNode(LPSingleLinkList pList,
				void *keyData);
BOOL removeIfInSingleLinkListNode(LPSingleLinkList pList,
				  PredFunc pred,
				  void *predParameter);
void reverseSingleLinkList(LPSingleLinkList pList);
void sortSingleLinkList(LPSingleLinkList pList);
void visitSingleLinkList(LPSingleLinkList pList,
			 VisitFunc visitor,
			 void *visitorParameter);
void printSingleLinkList(LPSingleLinkList pList);

#endif
