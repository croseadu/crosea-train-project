#include "singleLinkList.h"
#include "memory.h"




#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum Tag
{
	Atomic,
	List,
};

typedef struct _GList
{
	enum Tag tag;

	union {
		char data;
		struct {
			struct _GList *headPtr;
			struct _GList *tailPtr;	
		}list;
	};

}GList, *LPGList;



LPGList 
createGList(char *buf, int *pI)
{
	LPGList newNode = NULL;	
	LPGList node = NULL;
	LPGList *insertPos = NULL;

	assert (buf[*pI] !='\0' && buf[*pI] != '\n');
	

	if (buf[*pI] == '(') {
		++*pI;
		if (buf[*pI] == ')') {
			++*pI;
			return NULL;
		}	
		newNode = myAlloc(sizeof(GList));
		newNode->tag = List;
		newNode->list.headPtr = createGList(buf, pI);
		insertPos = &newNode->list.tailPtr;
		while (buf[*pI] == ',') {
			++*pI;
			
			node = myAlloc(sizeof(GList));
			*insertPos = node;
			node->tag = List;
			node->list.headPtr = createGList(buf, pI);
			insertPos = &node->list.tailPtr;
		}	
		assert(buf[*pI] == ')');	
		insertPos = NULL;
		++*pI;

	} else {
		newNode = myAlloc(sizeof(GList));
		newNode->tag = Atomic;
		newNode->data = buf[*pI];
		++*pI;
	}

	return newNode;

}

void
destroyGList(LPGList pList)
{
	if (pList == NULL)
		return;

	if (pList->tag == Atomic) {
		myFree(pList);
	} else {
		destroyGList(pList->list.headPtr);
		destroyGList(pList->list.tailPtr);
		myFree(pList);
	}
}


LPGList
copyGList(const LPGList pList)
{
	LPGList pNewList;

	if (pList == NULL)
		return NULL;

	pNewList = (LPGList)myAlloc(sizeof(GList));
	if (NULL == pNewList)
		return NULL;

	if (pList->tag == Atomic) {
		pNewList->tag = Atomic;
		pNewList->data = pList->data;
	} else {
		pNewList->tag = List;
		pNewList->list.headPtr = copyGList(pList->list.headPtr);
		pNewList->list.tailPtr = copyGList(pList->list.tailPtr);
	}	
	
	return pNewList;
}

void
dumpGList(LPGList pList)
{
	if (pList == NULL) {
		printf("()");
		return;
	}

	if (pList->tag == Atomic) {
		putchar(pList->data);
	} else {
		putchar('(');
		do {
			dumpGList(pList->list.headPtr);
			pList = pList->list.tailPtr;
			if (pList)
				putchar(',');
		} while (pList);
		putchar(')');
		
	}
}


int main()
{



	FILE *fp = NULL;
	char buf[4096+1] = {'\0'};
	int i, fillIndex, idx;
	
	LPGList root = NULL;
	LPGList newList = NULL;

	fp = fopen("genericList.txt", "r");
	if (fp == NULL)
		goto lexit;
	
	fgets(buf, 4096, fp);
	fclose(fp);

	fillIndex = 0;
	for (i = 0; i < 4096; ++i)
		if (buf[i] == ' ')
			continue;
		else {
			if (fillIndex != i)
				buf[fillIndex] = buf[i];
			++fillIndex;
		}
	buf[fillIndex] = '\0';

	idx = 0;
	
	root = createGList(buf, &idx);
	

	printf("\nList:");
	dumpGList(root);
	putchar('\n');
	newList = copyGList(root);
	printf("\nList:");
	dumpGList(newList);
	putchar('\n');


lexit:
	if (root)
		destroyGList(root);
	if (newList)
		destroyGList(newList);
	return 0;
}
