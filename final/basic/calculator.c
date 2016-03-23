#include "stack.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static int calc(int lhs, int rhs, char op);

static int
calc(int lhs, int rhs, char op)
{
	int result = 0;
	switch(op) {
		default:
			assert(0 && "unknown op");
			break;
		case '+': 
			return lhs + rhs;
		case '-':
			return lhs - rhs;
		case '*':
			return lhs * rhs;
		case '/':
			return lhs / rhs;
	}
	return 0;
}

static int compare(char top, char cur);
static int compare(char top, char cur)
{
	switch(top) {
		case '+':
		case '-':
		{
			switch(cur) {
				case '+':
				case '-':
				case ')':
					return 1;
				case '*':
				case '/':
					return -1;
				case '(':
					return -1;
				default:
					assert(0 && "invalid");
					return 0;
			}
		}
		break;
		case '*':
		case '/':
		{	
			switch(cur) {
				case '+':
				case '-':
				case '*':
				case '/':
				case ')':
					return 1;
				case '(':
					return -1;
				default:
					assert(0 && "invalid");
					return 0;
			}
		}
		break;
		case '(':
		{
			switch(cur) {
				case ')':
					return 0;
				case '+':
				case '-':
				case '*':
				case '/':
				case '(':
					return -1;
				default:
					assert(0 && "invalid");
			}
		
		}
		break;
		case ')':
		{
			assert(0 && "Invalid");
		}
		break;
		deafult:
		{
			assert(0 && "Invalid");
		}
		break;
	}
	return 0;
}

int main()
{

	char strs[4096] = {0};
	unsigned int i;
	unsigned int size;
	int precede;
	int lhs,rhs, result;
	char curOp, curStackTop;
	LPStack pOperatorStack, pOperandStack;


	printf("\nPls input an expression:");
	scanf("%s", strs);
	
	i = 0;
	while(strs[i] != '\n' && strs[i] != '\0')
		++i;


	if (i == 0) {
		printf("!Empty expression!");
		return 0;
	}
	size = i;
	
	if (False == createStack(&pOperatorStack, sizeof(char), dummyPrint)) {
		exit(-1);
	}
	if (False == createStack(&pOperandStack, sizeof(int), dummyPrint)) {
		destroyStack(&pOperatorStack);
		exit(-1);
	}

	i = 0;
	while (i < size || False == isStackEmpty(pOperatorStack)) {
		if (i < size) {
			if (isdigit(strs[i])) {
				sscanf(strs+i, "%d", &result);
				push(pOperandStack, &result);
				while(i < size && isdigit(strs[i]))
					++i;	
			} else {
				curOp = strs[i];
				if (isStackEmpty(pOperatorStack) == True) {
					push(pOperatorStack, &curOp);
					++i;
				} else {
					getTop(pOperatorStack, &curStackTop);
					precede = compare(curStackTop, curOp);
					switch(precede) {
						case 0:
							pop(pOperatorStack, &curStackTop);
							++i;
							break;
						case -1:
							push(pOperatorStack, &curOp);
							++i;
							break;
						case 1:
							pop(pOperatorStack, &curStackTop);
							pop(pOperandStack, &rhs);
							pop(pOperandStack, &lhs);
							result = calc(lhs, rhs, curStackTop);
							push(pOperandStack, &result);
							break;
					}
				}	
			}
		} else {
			pop(pOperatorStack, &curStackTop);
			pop(pOperandStack, &rhs);
			pop(pOperandStack, &lhs);
			result = calc(lhs, rhs, curStackTop);
			push(pOperandStack, &result);
		}
	}
	

	if (i < size || isStackEmpty(pOperatorStack) == False) {

	}
	if (sizeOfStack(pOperandStack) != 1) {

	}
	printf("\nResult = ");
	pop(pOperandStack, &result);
	printf("%d\n", result);




	destroyStack(&pOperatorStack);
	destroyStack(&pOperandStack);

	return 0;
}
