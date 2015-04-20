#include <my.h>


typedef struct _SingleLinkListNode
{
  void *data;
  struct _SingleLinkListNode *pNextNode;
}SingleLinkListNode, *LPSingleLinkListNode;

typedef struct _SingleLinkList
{
  LPSingleLinkListNode pHead;
  unsigned int elementSize;
  Printer printer;
  Less less;
  Equal equal;
}SingleLinkList, *LPSingleLinkList;



BOOL createSingleLinkList(LPSingleLinkList *ppList,
			  unsigned int elementSize,
			  Printer printer,
			  Less less,
			  Equal equal);
void destroySingleLinkList(LPSingleLinkList *ppList);

BOOL insertToHeadOfSingleLinkList(LPSingleLinkList pList,
				  void *srcData);
BOOL insertToTailOfSingleLinkList(LPSingleLinkList pList,
				  void *srcData);
BOOL insertAfterInSingleLinkList(LPSingleLinkList pList,
				 void *srcData,
				 LPSingleLinkListNode pPosNode);

BOOL insertBeforeInSingleLinkList(LPSingleLinkList pList,
				  void *srcData,
				  LPSingleLinkListNode *ppPosNode);
BOOL findInSingleLinkList(const LPSingleLinkList pList,
			  const void *refData);
BOOL findIfInSingleLinkList(const LPSingleLinkList pList,
			    Pred pred);
BOOL removeInSingleLinkList(LPSingleLinkList pList,
			    const void *refData);
BOOL removeIfInSingleLinkList(LPSingleLinkList pList,
			      Pred pred);
