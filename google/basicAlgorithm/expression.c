#include "../include/stack.h"

typedef struct 
{
  int value;
  char operator;
  BOOL bIsOperand;
}TOKEN, *LP_TOKEN;

#define END 2

int calc(int op1, int op2, char oper);
int compare(char cur, char top);

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
			case '\n':
			case '\0':
				return END;
			case '+':
			case '-':
			case '*':
			case '/':
			case '(':
			case ')':
			case '#':
				pToken->bIsOperand = FALSE;
				pToken->operator = inputBuffer[index++];
				*pCurIndex = index;
				return OK;
			case '0':
				if (isdigit(inputBuffer[index + 1]))
					return ERROR;

				pToken->bIsOperand = TRUE;
				pToken->value = 0;
				index++;
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
				
				pToken->bIsOperand = TRUE;
				pToken->value = data;	
				*pCurIndex = index;
				return OK;	

			default:
				*pCurIndex = index;
				return ERROR;
		}
	}

}

int main()
{
  char input[4096];
  FILE *fp;
  STATUS result;
  int index = 0;
  TOKEN tempToken, topToken;
  LP_STACK pOperStack;
  LP_STACK pOpndStack;
  int compareResult;
  int computeResult;

  fp = fopen("input/expr.txt", "r");
  if (NULL == fp)
    {
      printf("\nCannot Open File expr.txt\n");
      exit(-1);
    }
  memset(input, 0, sizeof(input));
  fscanf(fp, "%s", input);
  printf("\nInput: %s \n", input);

  createStack(&pOperStack, sizeof(TOKEN));
  createStack(&pOpndStack, sizeof(TOKEN));
  
  tempToken.bIsOperand = FALSE;
  tempToken.operator = '#';
  push (pOperStack, &tempToken);

  result = getNextOperOrOpnd(input, &index, &tempToken);
  while (!isStackEmpty(pOperStack))
    {
      if (tempToken.bIsOperand)
	{
	  push (pOpndStack, &tempToken);
	  result = getNextOperOrOpnd(input, &index, &tempToken);
	  if (result == END)
	    {
	      tempToken.operator = '#';
	      tempToken.bIsOperand = FALSE;
	    }
	}
      else
	{
	  getTop(pOperStack, &topToken);
	  compareResult = compare(tempToken.operator, topToken.operator);
	  if (compareResult == 0)
	    {
	      pop(pOperStack, &tempToken);
	      result = getNextOperOrOpnd(input, &index, &tempToken);
	      if (result == END)
		{
		  tempToken.operator = '#';
		  tempToken.bIsOperand = FALSE;
		}
	    }
	  else if (compareResult > 0)
	    {
	      push (pOperStack, &tempToken);
	      result = getNextOperOrOpnd(input, &index, &tempToken);
	      if (result == END)
		{
		  tempToken.operator = '#';
		  tempToken.bIsOperand = FALSE;
		}
	    }
	  else if (compareResult < 0)
	    {
	      pop (pOperStack, &topToken);
	      assert(topToken.operator == '+' 
		     || topToken.operator == '-' 
		     || topToken.operator == '*' 
		     || topToken.operator == '/');
	      {
		int op1, op2, op0;
		char oper;
		oper = topToken.operator;
		pop (pOpndStack, &topToken);
		op2 = topToken.value;
		pop (pOpndStack, &topToken);
		op1 =  topToken.value;
		op0 = calc(op1, op2, oper);
		topToken.bIsOperand = TRUE;
		topToken.value = op0;
		push (pOpndStack, &topToken);
	      }
	    }
	}
    }

  assert(result == END);
  assert(!isStackEmpty(pOpndStack));
  pop (pOpndStack, &topToken);
  computeResult = topToken.value;
  assert(isStackEmpty(pOpndStack));
  printf("\bFinal Result : %d\n", computeResult);

  destroyStack(pOperStack);
  destroyStack(pOpndStack);
  return 0;
}

int calc(int op1, int op2, char oper)
{
  switch(oper)
    {
    case '+':
      return op1+op2;
    case '-':
      return op1-op2;
    case '*':
      return op1*op2;
    case '/':
      return op1/op2;
    default:
      assert(0);
     
    }
  
}
int compare(char cur, char top)
{
  if (cur == '#')
    {
      if (top == '#')
	return 0;
      else 
	return -1;
    }
  if (cur == ')')
    {
      if (top == '(')
	return 0;
      else
	return -1;
    }
  if (cur == '*' || cur == '/')
    {
      if (top == '+' || top == '-')
	return 1;
      if (top == '*' || top == '/')
	return -1;
      if (top == '(' || top == '#')
	return 1;
    }
  if (cur == '+' || cur == '-')
    {
      if (top == '(' || top == '#')
	return 1;
      else
	return -1;
    }
  if (cur == '(')
    return 1;
}
