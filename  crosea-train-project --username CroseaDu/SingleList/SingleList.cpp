// SingleList.cpp : Defines the entry point for the console application.
//
//	all operation on singlelist,like reverse,sort including bubble,insert sort,
// quick sort,select sort
// Crosea Du 1/6/2008
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define TRUE 1
#define FALSE 0
#define ERROR_IN_INPUT 1
#define END_OF_INPUT 2

#define INIT_SIZE 20
#define INCREMENT_SIZE 20
typedef struct singlelist{
	int data;
	struct singlelist *next;
}SINGLELIST;
int getInputData(const char* inputCharArray,int *index,int *pTempData);
int initSingleList(SINGLELIST **ppSingleList);
int destorySingleList(SINGLELIST *pSingleList);
int insertSingleList(SINGLELIST *pSingleList,int data);
int insertSortSingleList(SINGLELIST *pSingleList);
int reverseSingleList(SINGLELIST *pSingleList);
int printSingleList(SINGLELIST *pSingleList);
int bubbleSortSingleList(SINGLELIST *pSingleList);
int selectSortSingleList(SINGLELIST *pSingleList);
SINGLELIST * pivot(SINGLELIST *from,SINGLELIST *end);
SINGLELIST * quickSort(SINGLELIST *from,SINGLELIST *end);
int quickSortSingleList(SINGLELIST *pSingleList);
int main(int argc, char* argv[])
{
	int curIndex;
	int hr;
	int maxArraySize = 0;
	int tempData;
	char tempChar;
	char *inputCharArray=NULL;
	SINGLELIST *pSingleList=NULL;

	inputCharArray = (char *)malloc(INIT_SIZE*sizeof(char));
	if(!inputCharArray)
	{
		printf("out of memory\n");
		goto exit;
	}
	maxArraySize = INIT_SIZE;
	printf("please input data for build SingleList:\n");
	curIndex = 0;
	tempChar = getchar();
	while(tempChar==' ')
	{
		tempChar = getchar();
	}
	while(tempChar!='\n')
	{
		if(isdigit(tempChar) || tempChar == ' ')
		{
			if(curIndex>=(maxArraySize-2))
			{
				inputCharArray = (char *)realloc(inputCharArray,(maxArraySize+INCREMENT_SIZE)+sizeof(char));
				if(!inputCharArray)
				{
					printf("out of memory when increase input array\n");
					goto exit;
				}
				maxArraySize +=INCREMENT_SIZE;
			}
			inputCharArray[curIndex++] = tempChar;
		}
		else
		{
			printf("invalid input\n");
			goto exit;
		}
		tempChar = getchar();
	}
	inputCharArray[curIndex] = '\0';
	if(initSingleList(&pSingleList))
	{
		printf("out of memory when create single list\n");
		goto exit;
	}
	curIndex = 0;
	while(TRUE)
	{
		hr = getInputData(inputCharArray,&curIndex,&tempData);
		if(hr == ERROR_IN_INPUT)
		{
			printf("Error in input\n");
			goto exit;
		}
		if(hr == END_OF_INPUT)
			break;
		insertSingleList(pSingleList,tempData);
	}
	printSingleList(pSingleList);
/*
	reverseSingleList(pSingleList);
	bubbleSortSingleList();
	insertSortSingleList(pSingleList);
	selectSortSingleList();
	quickSortSingleList();

*/
	printf("before sort\n");
//	insertSortSingleList(pSingleList);
//	selectSortSingleList(pSingleList);
//	bubbleSortSingleList(pSingleList);
	quickSortSingleList(pSingleList);
	printf("after sort\n");
	printSingleList(pSingleList);
	getchar();
exit:
	if(inputCharArray)
		free(inputCharArray);
	destorySingleList(pSingleList);
	return 0;
}
int getInputData(const char* inputCharArray,int *index,int *pTempData)
{
	int tempData = 0;
	int flag = 0;
	while(inputCharArray[*index]==' ')
		(*index)++;
	while(inputCharArray[*index]!='\0' &&inputCharArray[*index]!=' ')
	{
		flag = 1;
		tempData *=10;

		tempData += (inputCharArray[*index]-'0');
		(*index)++;
	}
	*pTempData = tempData;
	if(!flag)
		return END_OF_INPUT;
	return 0;
}
int printSingleList(SINGLELIST *pSingleList)
{
	SINGLELIST	*pTempNode = NULL;
	int		i = 0;
	if (!pSingleList || !pSingleList->next)
		return 0;
	pTempNode = pSingleList->next;
	while(pTempNode)
	{
		printf("%5d%s",pTempNode->data,(++i%5)?"":"\n");
		pTempNode = pTempNode->next;
	}
	if((i-1)%5)
		putchar('\n');
}
int initSingleList(SINGLELIST **ppSingleList)
{
	if((*ppSingleList = (SINGLELIST *)malloc(sizeof(SINGLELIST))) == NULL)
		return 1;
	(*ppSingleList)->next = NULL;
	(*ppSingleList)->data = -1;
	return 0;
}
int insertSingleList(SINGLELIST *pSingleList,int data)
{
	SINGLELIST *pTempNode = NULL;
	pTempNode = (SINGLELIST  *)malloc(sizeof(SINGLELIST));
	if(!pTempNode)
	{
		return 1;
	}
	pTempNode->data = data;
	pTempNode->next = pSingleList->next;
	pSingleList->next = pTempNode;
	return 0;
}
int destorySingleList(SINGLELIST *pSingleList)
{
	SINGLELIST *pTempNode;
	while(pSingleList)
	{
		pTempNode = pSingleList->next;
		free(pSingleList);
		pSingleList = pTempNode;

	}
	return 0;
}
int reverseSingleList(SINGLELIST *pSingleList)
{
	SINGLELIST *pTempNode,*pNextNode;

	pTempNode = pSingleList->next;
	pSingleList->next = NULL;

	while(pTempNode)
	{
		pNextNode = pTempNode->next;
		pTempNode->next = pSingleList->next;
		pSingleList->next = pTempNode;
		pTempNode = pNextNode;
	}
	return 0;

}
int insertSortSingleList(SINGLELIST *pSingleList)
{
	SINGLELIST *pTempNode,*pNextNode,*pInsertTempPosPrev;

	pTempNode = pSingleList->next;
	pSingleList->next = NULL;
	while(pTempNode)
	{
		pNextNode = pTempNode->next;
		pInsertTempPosPrev = pSingleList;
		while(pInsertTempPosPrev->next)
		{
			if(pInsertTempPosPrev->next->data >= pTempNode->data)
				break;
			pInsertTempPosPrev = pInsertTempPosPrev->next;
		}
		pTempNode->next = pInsertTempPosPrev->next;
		pInsertTempPosPrev->next = pTempNode;
		pTempNode = pNextNode;
	}
	return 0;
}
/* select the max node from pTempNode->next,
 * return the prev of max node;
 */
SINGLELIST *  selectMaxNodeFromSingleList(SINGLELIST *pTempNode)
{
	SINGLELIST *pPrevNode,*pNextNode;
	if(!pTempNode || !pTempNode->next)
		return NULL;
	pPrevNode = pTempNode;
	pNextNode = pTempNode;
	while(pNextNode->next)
	{
		if(pNextNode->next->data > pPrevNode->next->data)
			pPrevNode = pNextNode;
		pNextNode = pNextNode->next;
	}
	return pPrevNode;


}
int selectSortSingleList(SINGLELIST *pSingleList)
{

	SINGLELIST *pTempNode,*pSelectPrev,*pSelectNode;
	pTempNode = pSingleList->next;
	pSingleList->next = NULL;

	while(pTempNode)
	{
		pSelectPrev = selectMaxNodeFromSingleList(pTempNode);


		if(!pSelectPrev || pSelectPrev->next->data < pTempNode->data)
		{
			pSelectNode = pTempNode;
			pTempNode = pTempNode->next;
		}
		else
		{
			pSelectNode = pSelectPrev->next;
			pSelectPrev->next = pSelectNode->next;
		}
		pSelectNode->next = pSingleList->next;
		pSingleList->next = pSelectNode;
	}
	return 0;
}
int bubbleSortSingleList(SINGLELIST *pSingleList)
{
	SINGLELIST *pTempNode;
	int bSwitchNode = TRUE;
	int tempData;

	while(TRUE)
	{
		pTempNode = pSingleList->next;
		bSwitchNode = FALSE;
		while(pTempNode->next)
		{
			if(pTempNode->data > pTempNode->next->data)
			{
				tempData = pTempNode->data;
				pTempNode->data = pTempNode->next->data;
				pTempNode->next->data = tempData;
				bSwitchNode = TRUE;
			}
			pTempNode = pTempNode->next;
		}
		if(!bSwitchNode)
			break;

	}
	return 0;

}
SINGLELIST * pivot(SINGLELIST *from,SINGLELIST *end)
{
	SINGLELIST *pFirstNode,*pTempNode,*pNextNode;
	pFirstNode = from;
	pTempNode = from->next;
	from->next = end;

	while(pTempNode!=end)
	{
		pNextNode = pTempNode->next;
		if(pTempNode->data <from->data)
		{
			pTempNode->next = pFirstNode;
			pFirstNode = pTempNode;
		}
		else
		{
			pTempNode->next = from->next;
			from->next = pTempNode;
		}
		pTempNode = pNextNode;
		
	}
	return pFirstNode;

}
SINGLELIST * quickSort(SINGLELIST *from,SINGLELIST *end)
{

	SINGLELIST *pFirstNode,*pSecondFirstNode;
	if (!from || from == end || from->next==end)
	{
		return from;
	}
	pFirstNode = pivot(from,end);
	pFirstNode = quickSort(pFirstNode,from);
	pSecondFirstNode = quickSort(from->next,end);
	from->next = pSecondFirstNode;
	return pFirstNode;
}
int quickSortSingleList(SINGLELIST *pSingleList)
{
	SINGLELIST *pFirstNode = NULL;
	
	pFirstNode = quickSort(pSingleList->next,NULL);
	pSingleList->next = pFirstNode;
	return 0;
}
