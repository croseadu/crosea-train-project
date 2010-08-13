#include "../../include/my.h"
#include "../../include/util.h"
#include "../../include/stack.h"

#define LESS -1
#define GREAT 1
#define EQUAL 0
#define UNKNOWN 2

//  + - * / ( ) #
// +
// -
// *
// /
// (
// )
// #
int priorityTable[7][7]
{
{1,1,-1,-1,-1,1,1},
{1,1,-1,-1,-1,1,1},
{1,1,1,1,-1,1,1},	
{1,1,1,1,-1,1,1},
{-1,-1,-1,-1,-1,0,2},
{2,2,2,2,2,2,2},
{-1,-1,-1,-1,-1-}
}

int compute(const char operator, int op0, int op1);

int main()
{
	char c, *inputBuffer;
	char curOperator;
	TOKEN curToken;
	int maxElements, curIndex, data;
	LP_STACK pOperatorStack, pOperandStack;
	STATUS result;

	inputBuffer = (char *)malloc(sizeof(char) * INIT_BUFFER_SIZE);
	if (NULL == inputBuffer)
	{
		Print(("Out of Memory when allocate inputBuffer"));
		exit(-1);
	}	
	maxElements = INIT_BUFFER_SIZE;

	c = getchar();
	curIndex = 0;
	while (c != '\n')
	{
		inputBuffer[curIndex++] = c;
		c = getchar();

		if (curIndex >= maxElements - 2)
		{
			maxElements += INCRE_BUFFER_SIZE;
			inputBuffer = (char *)realloc(inputBuffer, sizeof(char) * maxElements);
			if (inputBuffer == NULL)
			{
				Print(("Out of Memory when enlarge input buffer"));
				exit(-1);
			}
		}
	}
	inputBuffer[curIndex++] = '#';
	inputBuffer[curIndex] = '\0';

	result = createStack(&pOperatorStack, sizeof(char));
	if (result != ok)
	{
		Print(("Out of Memory when create Stack\n"));
		free(inputBuffer);
		exit(-1);	
	}

	result = createStack(&pOperandStack, sizeof(int));
	if (result != ok)
	{
		Print(("Out of Memory when create Stack\n"));
		free(inputBuffer);
		destoryStack(pOperatorStack);
		exit(-1);	
	}
	
	curOperator = '#';
	push(pOperatorStack, &curOperator);
	
	curIndex = 0;
	getNextOperOrOpnd(inputBuffer, &curIndex, &curToken);
	while(!isStackEmpty(pOperator))
	{
		if (curToken.tokenType == OPEREND)
		{
			push(pOperandStack, &curToken.operand);
		}
		else
		{
			getTop(pOperatorStack, &curOperator);
			switch(priorityCompare(curOperator, curToken.operator))
			{
			case LESS:
				push(pOperatorStack, &curToken.operator);
				getNextOperOrOpnd(inputBuffer, &curIndex, &curToken);
				break;
			case GREAT:
				{
					int data1, data2;
					
					if (isStackEmpty(pOperandStack))
					{
						Print(("Error when compute expr\n"));
						exit(-1);
					}
					pop(pOperandStack, &data1);
					if (isStackEmpty(pOperandStack))
					{
						Print(("Error when compute expr\n"));
						exit(-1);
					}
					pop(pOperandStack, &data2);
					
					data = compute(curOperator, data1, data2);
					push(pOperandStack, &data);
					pop(pOperatorStack, &curOperator);
					break;
				}
			case EQUAL:
				pop(pOperatorStack, &curOperator);
				getNextOperOrOpnd(inputBuffer, &curIndex, &curToken);
				break;
			default:
				{
					Print(("Error when compute expr\n"));
					exit(-1);	
				}
				
				
			}
		}
	}

	getTop(pOperand, &data);
	if (isStackEmpty(pOperandStack))
	{
		Print(("Error when compute expr\n"));
		exit(-1);
	}

	Print(("\nFinal Result = %d\n", data));
	
	free(inputBuffer)
	destoryStack(pOperatorStack);
	destoryStack(pOperandStack);

	return 0;

}

int compute(const char operator, int op0, int op1)
{
	switch(operator)
	{
	case '+':
		return op0+op1;
	case '-':
		return op0-op1;
	case '*':
		return op0*op1;
	case '/':
		return op0/op1;
	default:
		{
			Print(("Error when compute two operand\n"));
			exit(-1);
		}
	}
}



