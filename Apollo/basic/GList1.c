#include "singleLinkList.h"
#include "memory.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef enum _Tag
{
	Atom,
	List,
}Tag;


typedef struct _GList
{
	Tag tag;
	union 
	{
		char data;
		struct _GList * pStartElements;
	};

	struct _GList * pNext;
}GList, *LPGList;


LPGList 
createGList(char *buf, int *pI)
{
	LPGList pNewList = NULL;

	assert (buf[*pI] != '\0');
	
	pNewList = myAlloc(sizeof(GList));
	LPGList *ppPos;

	if (buf[*pI] == '(') {
		pNewList->tag = List;
		pNewList->pNext = NULL;
		++*pI;
		ppPos = &pNewList->pStartElements;
		
		while (buf[*pI] != ')') {
			*ppPos = createGList(buf, pI);
			ppPos = &(*ppPos)->pNext;
		}
		*ppPos = NULL;
		++*pI;
	} else {
		assert(buf[*pI] != ')');
		pNewList->tag = Atom;
		pNewList->pNext = NULL;
		pNewList->data = buf[*pI];
		++*pI;
	}
	
	return pNewList;
}

LPGList
copyGList(const LPGList pSrc)
{
	LPGList pDst = NULL;
	LPGList *ppPos;
	LPGList pIter;

	if (pSrc == NULL)
		return NULL;
	
	pDst = (LPGList)myAlloc(sizeof(GList));
	assert (pDst != NULL);
	if (pSrc->tag == Atom) {
		pDst->tag = Atom;
		pDst->data = pSrc->data;
		pDst->pNext = NULL;
	} else {
		pDst->tag = List;
		pDst->pNext = NULL;
		ppPos = &pDst->pStartElements;
		pIter = pSrc->pStartElements;
		while (pIter != NULL) {
			*ppPos = copyGList(pIter);
			pIter = pIter->pNext;
			ppPos = &(*ppPos)->pNext;
		}
		*ppPos = NULL;
		

	}
	return pDst;
}

void
dumpGList(const LPGList pList)
{
	LPGList pIter, pNext;

	if (pList == NULL)
		return;

	if (pList->tag == Atom)
		printf("%c", pList->data);
	else {
		putchar('(');
		pIter = pList->pStartElements;
		while (pIter != NULL) {
			dumpGList(pIter);
			pIter = pIter->pNext;
		}
		putchar(')');
	}
}

void destroyGList(LPGList pList)
{
	LPGList pIter, pNext;

	if (pList == NULL)
		return;



	if (pList->tag == Atom) {
		myFree(pList);
	} else {
		pIter = pList->pStartElements;
		while (pIter) {
			pNext = pIter->pNext;
			destroyGList(pIter);

			pIter = pNext;
		}


		myFree(pList);
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
	
	printf("\nGList: ");
	dumpGList(root);

	newList = copyGList(root);
	printf("\nGLIst: ");
	dumpGList(newList);

lexit:
	if (root)
		destroyGList(root);
	if (newList)
		destroyGList(newList);


	return 0;
}
