#include "common.h"
#include "singleLinkList.h"
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
		struct _GNode *ptr;
	};
	struct _GNode *next;
}GNode, *LPGNode;




void createGList(LPGNode *ppNode, char strs[], int *pIdx)
{	
	LPGNode pNode = NULL;
	LPGNode *ppIter;	

	if (strs[*pIdx] == '(') {
		++*pIdx;
		pNode = myAlloc(sizeof(GNode));
		pNode->tag = List;
		pNode->ptr = NULL;
		pNode->next = NULL;
	
		ppIter = &pNode->ptr;
		while (strs[*pIdx] != ')') {
			createGList(ppIter, strs, pIdx);
			if (strs[*pIdx] == ',')
				++*pIdx;
			ppIter = &((*ppIter)->next);
		}
		++*pIdx;
		*ppNode = pNode;
		
	} else if ( strs[*pIdx] >= 'a' && strs[*pIdx] <= 'z') {
		pNode = myAlloc(sizeof(GNode));
		pNode->tag = Atomic;
		pNode->element = strs[*pIdx];
		pNode->next = NULL;
		

		++*pIdx;
		*ppNode = pNode;
		

	} else {

		*ppNode = NULL;
	}
	
}

void dumpGList(const LPGNode pHead)
{
	LPGNode pIter;
	if (pHead == NULL)
		return;
	if (pHead->tag == List) {
		putchar('(');
		pIter = pHead->ptr;
		while (pIter != NULL) {
			dumpGList(pIter);
			pIter = pIter->next;
			if (pIter)
				putchar(',');
		}

		putchar(')');

	} else {
		putchar(pHead->element);

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
	char strs[] = "(a,(b,c,d),())";
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

