// allSort.cpp : Defines the entry point for the console application.
//
//	all sort algorithm for array,like insert sort,select sort,quick sort,shell sort, heap sort
//
//	author:CroseaDu
//
//
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

typedef int BOOL;
typedef struct {
	int *data;
	int maxLength;
	int curLength;
}DATAARRAY;

static int shellStep[4]={9,7,3,1};

static int initDataArray(DATAARRAY **ppDataArray);
static int getInputData(const char* inputCharArray,int *index,int *pTempData);
static int printDataArray(const DATAARRAY *pDataArray);
static int bubbleSort(const DATAARRAY *pDataArray);
static int insertSort(const DATAARRAY *pDataArray);
static int selectSort(const DATAARRAY *pDataArray);
static int shellSort(const DATAARRAY *pDataArray);
static int quickSort(const DATAARRAY *pDataArray);
static int heapSort(const DATAARRAY *pDataArray);
static int mergeSort(const DATAARRAY *pDataArray);
static int mergeInsertSort(const DATAARRAY *pDataArray);

int main(int argc, char* argv[])
{
	int curIndex;
	int hr;
	int maxArraySize = 0;
	int tempData;
	char tempChar;
	char *inputCharArray=NULL;
	DATAARRAY *pDataArray=NULL;

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
	if(initDataArray(&pDataArray))
	{
		printf("out of memory when create data Array\n");
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
		pDataArray->data[++pDataArray->curLength] = tempData;
	}
	printDataArray(pDataArray);
	printf("after sort");
	//bubbleSort(pDataArray);
	//insertSort(pDataArray);
	//selectSort(pDataArray);
	//shellSort(pDataArray);
	//quickSort(pDataArray);
	//heapSort(pDataArray);
	mergeSort(pDataArray);
	printDataArray(pDataArray);
exit:
	if(inputCharArray)
		free(inputCharArray);
	if(pDataArray)
	{
		if(pDataArray->data)
			free(pDataArray->data);
		free(pDataArray);
	}
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
int printDataArray(const DATAARRAY *pDataArray)
{
	int i,j;
	for(i=1;i<=pDataArray->curLength;i++)
	{
		printf("%5d%s",pDataArray->data[i],(++j%5)?"":"\n");
	}
	if((j-1)%5)
		putchar('\n');
	return 0;
}
int initDataArray(DATAARRAY **ppDataArray)
{
	(*ppDataArray) = (DATAARRAY *)malloc(sizeof(DATAARRAY));
	if (!(*ppDataArray))
		return 1;
	(*ppDataArray)->data = (int *)malloc(sizeof(int)*INIT_SIZE);
	if(!((*ppDataArray)->data))
		return 1;
	(*ppDataArray)->curLength = 0;
	(*ppDataArray)->maxLength = INIT_SIZE;
	return 0;
}
int bubbleSort(const DATAARRAY *pDataArray)
{
	int i,j,tempData;
	BOOL bHaveSwitch = FALSE;

	for(i = pDataArray->curLength;i>1;i--)
	{
		bHaveSwitch = FALSE;
		for(j = 1;j<i;j++)
		{
			if(pDataArray->data[j] >pDataArray->data[j+1])
			{
				bHaveSwitch = TRUE;
				tempData = pDataArray->data[j];
				pDataArray->data[j] = pDataArray->data[j+1];
				pDataArray->data[j+1] = tempData;
			
			}
		
		}
		if(!bHaveSwitch)
			break;
	
	}
	return 0;
}
int insertSort(const DATAARRAY *pDataArray)
{
	int i,j;

	for(i=2;i<=pDataArray->curLength;i++)
	{
		if(pDataArray->data[i] < pDataArray->data[i-1])
		{
			pDataArray->data[0] = pDataArray->data[i];
			for(j=i-1;pDataArray->data[j]>pDataArray->data[0];j--)
			{
				pDataArray->data[j+1] = pDataArray->data[j];
			}
			pDataArray->data[j+1] = pDataArray->data[0];
		}
	
	}

	return 0;
}
int selectMinFromArray(const int *pData,int from,int end)
{
	int minIndex = from,i;
	for(i=from+1;i<=end;i++)
	{
		if(pData[i]<pData[minIndex])
			minIndex = i;
	}
	return minIndex;
}
int selectSort(const DATAARRAY *pDataArray)
{
	int i,minIndex,tempData;

	for(i=1;i<pDataArray->curLength;i++)
	{
		minIndex = selectMinFromArray(pDataArray->data,i,pDataArray->curLength);
		tempData = pDataArray->data[i];
		pDataArray->data[i] = pDataArray->data[minIndex];
		pDataArray->data[minIndex] = tempData;
	}
	return 0;
}
int shellSort(const DATAARRAY *pDataArray)
{
	int i,j,k,step;
	for(i =0;i<4;i++)
	{
		step = shellStep[i];
		for(j=1+step;j<=pDataArray->curLength;j++)
		{
			pDataArray->data[0] = pDataArray->data[j];
			for(k=j-step;k>0 &&pDataArray->data[k] > pDataArray->data[0];k -=step)
			{
				pDataArray->data[k+step] = pDataArray->data[k]; 
			}
			pDataArray->data[k+step] = pDataArray->data[0];
		
		}
	}
	return 0;

}
int pivot(int *pData,int from,int end)
{
	int tempData;
	tempData = pData[from];
	while(from < end)
	{
		while(from<end && pData[end]>=tempData)
			end--;
		pData[from] = pData[end];
		while(from<end && pData[from]<=tempData)
			from++;
		pData[end] = pData[from]; 
	
	}
	pData[from] = tempData;
	return from;
}
int quickSortArray(int *pData,int from,int end)
{
	int pivotPosition;
	if(from >= end)
		return 0;
	pivotPosition = pivot(pData,from,end);
	quickSortArray(pData,from,pivotPosition-1);
	quickSortArray(pData,pivotPosition+1,end);
	return 0;

}
int quickSort(const DATAARRAY *pDataArray)
{
	quickSortArray(pDataArray->data,1,pDataArray->curLength);
	return 0;

}
int heapAdjust(int *pData,int from,int end)
{
	int i,tempData;
	tempData = pData[from];
	for(i = from*2;i<=end;i *=2)
	{
		if(i+1<=end && pData[i+1]>pData[i])
			i++;
		if(pData[i]>tempData)
			pData[i/2] = pData[i];
		else
			break;
	}
	pData[i/2] = tempData;
	return 0;
}
int heapSort(const DATAARRAY *pDataArray)
{
	int i,tempData;
	for(i = pDataArray->curLength/2;i>=1;i--)
	{
		heapAdjust(pDataArray->data,i,pDataArray->curLength);	
	}
	for(i = pDataArray->curLength;i>1;i--)
	{
		tempData = pDataArray->data[i];
		pDataArray->data[i] = pDataArray->data[1];
		pDataArray->data[1] = tempData;
		heapAdjust(pDataArray->data,1,i-1);
	}
	return 0;

}
int mergeArray(int *pDataSrc,int *pDataDst,int length)
{

	int i = 0;
	int j = length/2;
	int index = 0;

	for(;i<length/2&&j<length;)
	{
		if(pDataSrc[i]<=pDataSrc[j])
			pDataDst[index++] = pDataSrc[i++];
		else
			pDataDst[index++] = pDataSrc[j++];	
	}
	while(i<length/2)
	{
		pDataDst[index++] = pDataSrc[i++];
	}
	while(j<length)
	{
		pDataDst[index++] = pDataSrc[j++];
	}
	return 0;
}
int mergeSortArray(int *pDataSrc,int *pDataDst,int length)
{
	int middle;
	int *pTempDataBuffer = NULL;

	if(length<=0)
		return 0;
	else if(length==1)
	{
		pDataDst[0] = pDataSrc[0];
		return 0;
	}
	middle = length/2;
	pTempDataBuffer = (int *)malloc(sizeof(int)*(length));
	if(!pTempDataBuffer)
	{
		exit(0);
	}
	mergeSortArray(pDataSrc,pTempDataBuffer,middle);
	mergeSortArray(pDataSrc+middle,pTempDataBuffer+middle,length-middle);
	mergeArray(pTempDataBuffer,pDataDst,length);
	free(pTempDataBuffer);
	return 0;
}

int mergeSort(const DATAARRAY *pDataArray)
{
	mergeSortArray(pDataArray->data+1,pDataArray->data+1,pDataArray->curLength);
	return 0;
}
