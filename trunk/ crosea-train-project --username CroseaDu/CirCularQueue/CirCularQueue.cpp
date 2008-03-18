// CirCularQueue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#define TRUE 1
#define FALSE 0
#define ERROR_IN_INPUT 1
#define END_OF_INPUT 2

#define INIT_SIZE 20
#define INCREMENT_SIZE 20

int getInputData(const char* inputCharArray,int *index,int *pTempData);

int main(int argc, char* argv[])
{
	LPCIRCULARQUEUE pCircularQueue = NULL;
	char tempChar;
	char *inputCharArray = NULL;	
	int maxArraySize, curIndex, tempData, hr;

	printf("input all data which create the circular queue");
	inputCharArray = (char *)malloc(INIT_SIZE*sizeof(char));
	if(!inputCharArray)
	{
		printf("out of memory\n");
		goto exit;
	}
	maxArraySize = INIT_SIZE;
	printf("please input data for build circular queue:\n");
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
	if(initCircularQueue(&pCircularQueue))
	{
		printf("out of memory when create circular queue\n");
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
		insertCircularQueue(pCircularQueue,tempData);
	}


exit:

	destroyCircularQueue(pCircularQueue);
	return 0;
}
int printCircularQueue(const LPCIRCULARQUEUE pCircularQueue)
{
	if (!pCircularQueue)
	{
		printf("circular queue don't exist");
		return 0;
	}
	if (pCircularQueue->end == pCircularQueue->front)
	{
		printf("circular queue is empty");
		return 0;	
	}



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
