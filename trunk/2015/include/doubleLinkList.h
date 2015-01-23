#ifndef _MY_DOUBLE_LINK_LIST_H
#define _MY_DOUBLE_LINK_LIST_H

#include "common.h"

typedef struct _DoubleLinkListNode
{
  void *data;
  struct _DoubleLinkListNode *pNextNode;
  struct _DoubleLinkListNode *pPrevNode;

}DoubleLinkListNode, *LPDoubleLinkListNode;

typedef LPDoubleLinkListNode * DoubleLinkListNodeIter;

typedef struct _DoubleLinkList
{
  LPDoubleLinkListNode pHead;
  unsigned int elementSize;
  PrintFunc printer;
  LessFunc less;
  EqualFunc equal;
}DoubleLinkList, *LPDoubleLinkList;

BOOL createDoubleLinkList(LPDoubleLinkList *ppList,
			  unsigned int elementSize,
			  PrintFunc printer,
			  LessFunc less,
			  EqualFunc equal);
void destroyDoubleLinkList(LPDoubleLinkList *ppList);

BOOL insertToHeadOfDoubleLinkList(LPDoubleLinkList pList,
				  void *elementData);
BOOL insertToTailOfDoubleLinkList(LPDoubleLinkList pList,
				  void *elementData);
BOOL insertAfterInDoubleLinkList(LPDoubleLinkList pList,
				 void *elementData,
				 LPDoubleLinkListNode pPos);
BOOL insertBeforeInDoubleLinkList(LPSingleLInkList pList,
				  void *elementData,
				  LPDoubleLinkListNode pPos);
LPDoubleLinkListNode findInDoubleLinkList(LPDoubleLinkList pList,
					    void *keyData);
BOOL removeInDoubleLinkListNode(LPDoubleLinkList pList,
				void *keyData);
BOOL removeIfInDoubleLinkListNode(LPDoubleLinkList pList,
				  PredFunc pred,
				  void *predParameter);
void reverseDoubleLinkList(LPDoubleLinkList pList);
void sortDoubleLinkList(LPDoubleLinkList pList);
void visitDoubleLinkList(LPDoubleLinkList pList,
			 VisitFunc visitor,
			 void *visitorParameter);
void printDoubleLinkList(LPDoubleLinkList pList);

#endif
