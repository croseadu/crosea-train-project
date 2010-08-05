
#include "../include/my.h"
#include "../include/util.h"



STATUS getNextNumber(const char *inputBuffer, int *pCurIndex, int *pData)
{
	int index, data;
	
	index = *pCurIndex;
	data = 0;

	while (1)
	{
		switch (inputBuffer[index])
		{
			case ' ':
			case '\t':
				index++;
				break;
			case '\0':
				return END;
			case '0':
				data = 0;
				index++;
				if (inputBuffer[index] != ' ' 
				    && inputBuffer[index] != '\t'
                                    && inputBuffer[index] != '\0')
					return ERROR;
				else
				{
					*pData = data;
					*pCurIndex = index;
					return OK;
				}
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				do
				{
					data *= 10;
					data += inputBuffer[index++] - '0';	
				}while(isdigit(inputBuffer[index]));
				
				if (inputBuffer[index] != ' ' 
				    && inputBuffer[index] != '\t'
                                    && inputBuffer[index] != '\0')
					return ERROR;
				else
				{
					*pData = data;
					*pCurIndex = index;
					return OK;
				}	

			default:
				*pCurIndex = index;
				return ERROR;
			
		}
	}


}

STATUS getNextOperOrOpnd(const char *inputBuffer, int *pCurIndex, TOKEN *pToken)
{

	int index = *pCurIndex;
	int data = 0;

	while (1)
	{
		switch (inputBuffer[index])
		{
			case ' ':
			case '\t':
				index++;
				break;
			case '\0':
				return END;
			case '+':
			case '-':
			case '*':
			case '/':
			case '(':
			case ')':
				pToken->tokenType = OPERATOR;
				pToken->tokenValue.operator = inputBuffer[index++];
				*pCurIndex = index;
				return OK;
			case '0':
				if (isdigit(inputBuffer[index + 1]))
					return ERROR;

				pToken->tokenType = OPEREND;
				pToken->tokenValue.operand = 0;
				*pCurIndex = index;		
				return OK;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				do
				{
					data *= 10;
					data += inputBuffer[index++] - '0';	
				}while(isdigit(inputBuffer[index]));
				
				pToken->tokenType = OPEREND;
				pToken->tokenValue.operand = data;	
				*pCurIndex = index;
				return OK;	

			default:
				*pCurIndex = index;
				return ERROR;
		}
	}

}
