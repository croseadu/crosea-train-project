
#include "common.h"
#include "utils.h"

#include "myMemory.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>



enum Tag
{
	Atomic,
	List,
};

typedef char ElementType;

typedef struct _GNode
{
	enum Tag tag;
	union {
		ElementType element;
		
		struct {
			struct _GNode *head;
			struct _GNode *tail;
		}ptr;
	};
}GNode, *LPGNode;




void createGList(LPGNode *ppNode, char strs[], int *pIdx)
{	
	LPGNode pNode = NULL, pTail = NULL;
	LPGNode *ppIter = NULL;

	if (strs[*pIdx] <= 'z' && strs[*pIdx] >= 'a') {
		pNode = myAlloc(sizeof(GNode));
		pNode->tag = Atomic;
		pNode->element = strs[*pIdx];
		++*pIdx;
		*ppNode = pNode;		
		
	} else if (strs[*pIdx] == '(') {
		pNode = myAlloc(sizeof(GNode));
		pNode->tag = List;
		++*pIdx;
		createGList(&pNode->ptr.head, strs, pIdx);
		ppIter = &pNode->ptr.tail;
		if (strs[*pIdx] == ',')
			++*pIdx;
		while (strs[*pIdx] != ')') {
			pTail = myAlloc(sizeof(GNode));
			pTail->tag = List;
			*ppIter = pTail;
			ppIter = &pTail->ptr.tail;
			createGList(&pTail->ptr.head, strs, pIdx);
			if (strs[*pIdx] == ',')
				++*pIdx;
		}
		*ppIter = NULL;

		++*pIdx;
		*ppNode = pNode;

	} else {
		*ppNode = NULL;
	}	
}

void dumpGList(const LPGNode pList)
{
	LPGNode pIter,pNext;

	if (pList == NULL)
		return;
	if (pList->tag == Atomic) {
		putchar(pList->element);
	} else {
		putchar('(');
		pIter = pList->ptr.head;
		pNext = pList->ptr.tail;
		while ( pIter ) {
			dumpGList(pIter);
			
			if (pNext) {
				putchar(',');
			
			pIter = pNext->ptr.head;
			pNext = pNext->ptr.tail;
			} else {
				pIter = NULL;
			}
		}
		putchar(')');
	}

}

void destroyGList(LPGNode *);
void destroyGList(LPGNode *ppHead)
{
	(void)ppHead;
}
int main()
{

	LPGNode pHead = NULL;
	char strs[] = "(a,b,c,(d,e))";
	int i;
	
	printf("\bInput String is :%s\n", strs);
	
	i = 0;
	createGList(&pHead, strs, &i);
	
	printf("\nCreated List:\n");
	dumpGList(pHead);
	putchar('\n');


	destroyGList(&pHead);

	return 0;
}

