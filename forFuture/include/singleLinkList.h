
#include "common.h"

typedef struct _SingleLinkListNode
{
  void *data;
  struct _SingleLinkListNode *pNextNode;
}SingleLinkListNode, *LPSingleLinkListNode;

typedef struct _SingleLinkList
{
  LPSingleLinkListNode pHead;
  unsigned int elementSize;
  unsigned int listSize;
  Printer printer;
  CompareFunc less;
  CompareFunc equal;
}SingleLinkList, *LPSingleLinkList;

BOOL initSingleLinkList(LPSingleLinkList *ppList,
			unsigned int elementSize,
			Printer printer,
			CompareFunc less,
			CompareFunc equal);
void destroySingleLinkList(LPSingleLinkList *ppList);

BOOL insertToSingleLinkList(LPSingleLinkList pList,
			    void *srcData,
			    LPSingleLinkListNode pInsertAfter);
BOOL insertToSingleLinkListHead(LPSingleLinkList pList,
				void *srcData);
BOOL insertToSingleLinkListTail(LPSingleLinkList pList,
				void *srcData);
BOOL removeFromSingleLinkList(LPSingleLinkList pList,
			      void *refData);
BOOL removeIfFromSingleLinkList(LPSingleLinkList pList,
				PredFunc pred,
				void *predArgument);
LPSingleLinkListNode findInSingleLinkList(LPSingleLinkList pList,
					  void *refData);
void visitSingleLinkList(LPSingleLinkList pList,
			 Visitor visitor,
			 void *visitorArgument);
void printSingleLinkList(LPSingleLinkList pList);
void sortSingleLinkList(LPSingleLinkList pList);
// Only remove consecutive duplicates, so pls sort list first
void unqiueSingleLinkList(LPSingleLinkList pList);

void reverseSingleLinkList(LPSingleLinkList pList);
LPSingleLinkList mergeSingleLinkList(LPSingleLinkList pListLhs,
				     LPSingleLinkList pListRhs,
				     BOOL duplicateSubElement);

