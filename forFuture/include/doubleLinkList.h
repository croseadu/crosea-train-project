
#include "../common.h"

typedef struct _DoubleLinkListNode
{
  void *data;
  struct _DoubleLinkListNode *pNextNode;
}DoubleLinkListNode, *LPDoubleLinkListNode;

typedef struct _DoubleLinkList
{
  LPDoubleLinkListNode pHead;
  unsigned int elementSize;
  unsigned int listSize;
  Printer printer;
  CompareFunc less;
  CompareFunc equal;
}DoubleLinkList, *LPDoubleLinkList;

BOOL initDoubleLinkList(LPDoubleLinkList *ppList,
			unsigned int elementSize,
			Printer printer,
			CompareFunc less,
			CompareFunc equal);
void destroyDoubleLinkList(LPDoubleLinkList *ppList);

BOOL insertToDoubleLinkList(LPDoubleLinkList pList,
			    void *srcData,
			    LPDoubleLinkListNode pInsertAfter);
BOOL insertToDoubleLinkListHead(LPDoubleLinkList pList,
				void *srcData);
BOOL insertToDoubleLinkListTail(LPDoubleLinkList pList,
				void *srcData);
BOOL removeFromDoubleLinkList(LPDoubleLinkList pList,
			      void *refData);
BOOL removeIfFromDoubleLinkList(LPDoubleLinkList pList,
				void *refData,
				PredFunc pred);
LPDoubleLinkListNode * findInDoubleLinkList(LPDoubleLinkList pList,
					    void *refData);
void visitDoubleLinkList(LPDoubleLinkList pList,
			 Visitor visitor,
			 void *visitorArgument);
void sortDoubleLinkList(LPDoubleLinkList pList);
void reverseDoubleLinkList(LPDoubleLinkList pList);
LPDoubleLinkList mergeDoubleLinkList(LPDoubleLinkList pListLhs,
				     LPDoubleLinkList pListRhs,
				     bool duplicateSubElement);

