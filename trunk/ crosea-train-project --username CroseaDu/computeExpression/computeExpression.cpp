// computeExpression.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "my.h"

#define POP_BRACKET 1
#define DO_OPERATE	2

enum OPTR_PRIORITY
{
	RIGHT_BRACKET_PRIORITY = 0,
	ADD_SUB_PRIORITY,
	MUL_DIV_PRIORITY,
	LEFT_BRACKET_PRIORITY,
};

BOOL isNeedDoOperate(char optrInStack,char optrCur);
int doOperate(char optr,int data1,int data2,int *result);
int getDataFromInput(char *inputCharArray,int *pIndex,int *pTempData);


int main(int argc, char* argv[])
{
	char *inputCharArray = NULL;
	char c, optr;
	int maxArraySize,index = 0;
	int hr;
	int data1, data2,result,tempData;

	LPDATASTACK pDataStack = NULL;
	LPOPERATORSTACK pOptrStack = NULL;



	inputCharArray = (char *)malloc(sizeof(char)*INIT_SIZE);
	if (!inputCharArray)
	{
		printf("out of memory!");
		goto exit;
	}
	maxArraySize = INIT_SIZE;
	c = getchar();
	while(c == ' ')
		c = getchar();
	while(c!='\n')
	{
		if (index >= maxArraySize-2)
		{
			inputCharArray = (char *)realloc(inputCharArray,(maxArraySize+INCREMENT_SIZE)*sizeof(char));
			if(!inputCharArray)			
			{
				printf("out of memory when increase input array\n");
				goto exit;
			}
			maxArraySize +=INCREMENT_SIZE;
		}
		if (isdigit(c)||isOperator(c))
		{
			inputCharArray[index++] = c;
			c = getchar();
		}
		else if (c == ' ')
		{
			c = getchar();
		}
		else
		{
			printf("invalid input!");
			goto exit;
		}
	}	
	inputCharArray[index] = 0;
	initDataStack(&pDataStack);
	initOptrStack(&pOptrStack);
	printf("array is %s\n",inputCharArray);
	if (!pDataStack || ! pOptrStack)
	{
		printf("can't create stack");
		goto exit;
	
	}
	index = 0;
	while(!isOptrStackEmpty(pOptrStack) || inputCharArray[index] != 0)
	{
		if (inputCharArray[index] == 0)
		{
			if (!popOptrStack(pOptrStack,&optr) ||
				!popDataStack(pDataStack,&data2) ||
				!popDataStack(pDataStack,&data1) )
			{
				printf("error when need pop optr data from stack");
				goto exit;	
			}
			else
			{
				doOperate(optr,data1,data2,&result);
				pushDataStack(pDataStack,result);
			}
		
		}
		else if (isdigit(inputCharArray[index]))	
		{
			if(getDataFromInput(inputCharArray,&index,&tempData))
			{
				printf("push %d to data stack\n",tempData);
				pushDataStack(pDataStack,tempData);	
			}
			else
			{
				printf("can't get data from input");
				goto exit;
			}

		}
		else if (isOperator(inputCharArray[index]))
		{
			if (hr = isNeedDoOperate(getTopOfOptrStack(pOptrStack),inputCharArray[index]))
			{
				if (hr == POP_BRACKET)
				{
					if (!popOptrStack(pOptrStack,&optr))
					{
						printf("error when need pop optr from stack");
						goto exit;
					}
					index++;
				}
				else if ( hr ==  DO_OPERATE)
				{
					if (!popOptrStack(pOptrStack,&optr) ||
						!popDataStack(pDataStack,&data2) ||
						!popDataStack(pDataStack,&data1) )
					{
						printf("error when need pop optr data from stack");
						goto exit;	
					}
					else
					{
						doOperate(optr,data1,data2,&result);
						pushDataStack(pDataStack,result);
					}
					
				}
			}
			else
			{				
				printf("push %c to optr stack\n",inputCharArray[index]);
				pushOptrStack(pOptrStack,inputCharArray[index]);
				index++;
			}
		}
		else
		{
			printf("not digit not optr");
			goto exit;
		}

	
	}


	popDataStack(pDataStack,&result);
	printf("\n%s = %d\n",inputCharArray,result);
exit:
	if (!inputCharArray)
		free(inputCharArray);
	destroyOptrStack(pOptrStack);
	destroyDataStack(pDataStack);
	if (pDataStack)
		free(pDataStack);
	if (pOptrStack)
		free(pOptrStack);
	return 0;
}

enum OPTR_PRIORITY getOptrPriority(const char optr)
{
	if (optr == ')')
		return RIGHT_BRACKET_PRIORITY;
	else if (optr == '+' || optr == '-')
		return ADD_SUB_PRIORITY;
	else if (optr == '*' || optr == '/' )
		return MUL_DIV_PRIORITY;
	else if (optr == '(')
		return LEFT_BRACKET_PRIORITY;

}

BOOL isNeedDoOperate(char optrInStack,char optrCur)
{
	enum OPTR_PRIORITY priorityOfCurOptr, priorityOfOptrInStack;

	priorityOfCurOptr = getOptrPriority(optrCur);
	priorityOfOptrInStack = getOptrPriority(optrInStack);

	if (priorityOfCurOptr == LEFT_BRACKET_PRIORITY )
		return FALSE;
    else if (priorityOfCurOptr == RIGHT_BRACKET_PRIORITY)
	{
		if (priorityOfOptrInStack == LEFT_BRACKET_PRIORITY)
			return POP_BRACKET;
		else
			return DO_OPERATE;
	}

	else if (priorityOfCurOptr == MUL_DIV_PRIORITY)
	{
		if (priorityOfOptrInStack == MUL_DIV_PRIORITY )
			return DO_OPERATE;
		else
			return FALSE;
	}
	else if (priorityOfOptrInStack == MUL_DIV_PRIORITY || priorityOfOptrInStack == ADD_SUB_PRIORITY )
		return DO_OPERATE;
	else 
		return FALSE;
		
}

int getDataFromInput(char *inputCharArray,int *pIndex,int *pTempData)
{
	int tempData = inputCharArray[(*pIndex)++] - '0';

	while(isdigit(inputCharArray[*pIndex]))
	{
		tempData *= 10;
		tempData += (inputCharArray[*pIndex] - '0');
		(*pIndex)++;	
	}
	*pTempData = tempData;
	return 1;
}
int doOperate(char optr,int data1,int data2,int *result)
{
	if (optr == '+')
	{
		*result = data1+data2;
		printf("\n %d add %d = %d",data1,data2,*result);
	}
	else if (optr == '-')
	{
		*result = data1-data2;
		printf("\n %d sub %d = %d",data1,data2,*result);
	}
	else if (optr == '*')
	{
		*result = data1*data2;
		printf("\n %d mul %d = %d",data1,data2,*result);
	}
	else if (optr == '/')
	{
		*result = data1/data2;
		printf("\n %d div %d = %d",data1,data2,*result);
	}
	return 1;

}