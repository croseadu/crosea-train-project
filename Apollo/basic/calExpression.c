#include "stack.h"

#include "common.h"
#include "utils.h"


#include <stdio.h>
#include <assert.h>
#include <string.h>


typedef enum _Operator
{
	ADD = 0,
	SUB,
	MUL,
	DIV,
	LEFT_P,
	RIGHT_P,
	LAST_OP,
}Operator;


void
operatorPrinter(const void *data)
{
	Operator op = *(const Operator *)data;
	
	printf(" %c ", "+-*/()"[op]);

}

BOOL
executeOneOpFromStack(
	LPStack pOperatorStack,
	LPStack pOperandStack);

int
doCalculation(Operator op, int left, int right)
{
	switch(op) {
		case ADD: return left + right;
		case SUB: return left - right;
		case MUL: return left * right;
		case DIV: return left / right;
	
		default:
			assert(0 && "Invalid Op");
			break;


	}

	return 0;
}


BOOL
executeOneOpFromStack(
	LPStack pOperatorStack,
	LPStack pOperandStack)
{
	Operator opcode = LAST_OP;
	int result;
	int rightOperand, leftOperand;


	assert(isStackEmpty(pOperatorStack) == False);

	getTopFromStack(pOperatorStack, &opcode);
	popFromStack(pOperatorStack);
			
	if (getSizeOfStack(pOperandStack) < 2)
		return False;

	getTopFromStack(pOperandStack, &rightOperand);
	popFromStack(pOperandStack);

	getTopFromStack(pOperandStack, &leftOperand);
	popFromStack(pOperandStack);

	result = doCalculation(opcode, leftOperand, rightOperand);
	pushToStack(pOperandStack, &result);	
		
	return True;
}


typedef enum _Priority
{
	EQ_P,
	LESS_P,
	BIG_P,
	INVALID_P,

}Priority;

/*

|onStack\Cur	|	ADD	|	SUB	|	MUL	|	DIV	|	LEFT_P	|	RIGHT_P	|
|	ADD	|	>	|	>	|	<	|	<	|	<	|	>	|
|	SUB	|	>	|	>	|	<	|	<	|	<	|	>	|
|	MUL	|	>	|	>	|	>	|	>	|	<	|	>	|
|	DIV	|	>	|	>	|	>	|	>	|	<	|	>	|
|	LEFT_P	|	<	|	<	|	<	|	<	|	<	|	=	|
|	RIGHT_P	|	x	|	x	|	x	|	x	|	x	|	x	|


*/
const Priority lookup[LAST_OP][LAST_OP] = 
{
	{BIG_P, BIG_P, LESS_P, LESS_P, LESS_P, BIG_P},
	{BIG_P, BIG_P, LESS_P, LESS_P, LESS_P, BIG_P},
	{BIG_P, BIG_P, BIG_P, BIG_P, LESS_P, BIG_P},
	{BIG_P, BIG_P, BIG_P, BIG_P, LESS_P, BIG_P},
	{LESS_P, LESS_P, LESS_P, LESS_P, LESS_P, EQ_P},
	{INVALID_P, INVALID_P, INVALID_P, INVALID_P,INVALID_P,INVALID_P}
};

Operator
getOpcode(const char c)
{
	switch(c) {
		case '+': return ADD;
		case '-': return SUB;
		case '*': return MUL;
		case '/': return DIV;
		case '(': return LEFT_P;
		case ')': return RIGHT_P;
		default:
			break;
	}
	printf("Parse OP %c", c);
	assert(0 && "Not a valid op");
	return LAST_OP;
}

int main()
{
	LPStack pOperatorStack = NULL;
	LPStack pOperandStack = NULL;
	char expression[4096] = {'\0'};
	int i,j, n;
	int temp;
	Operator opInStack, curOp;
	Priority priority;


	if (False == createStack(&pOperatorStack,
				 sizeof(Operator),
				 operatorPrinter)) {
		goto lexit;
	}


	if (False == createStack(&pOperandStack,
				 sizeof(int),
				 intPrinter)) {
		goto lexit;
	}


	FILE *fp = fopen("expression.txt", "r");
	if (fp == NULL) {
		goto lexit;
	}	


	fgets(expression, 4095, fp);
	n = strlen(expression);
	if (n == 0) {
		printf("Invalid Expression\n");
		goto lexit;
	}
	j = 0;
	for (i = 0; i < n; ++i) {
		if (expression[i] == ' ' || expression[i] == '\n')
			continue;
		if (i != j) {
			expression[j] = expression[i];
		}
		++j;
	}

	n = j;
	expression[n] = '\0';
	i = 0;
	while (i < n || isStackEmpty(pOperatorStack) == False) {
		if (i == n) {
			if (executeOneOpFromStack(pOperatorStack, pOperandStack) == False)
				break;			
		} else {
			if (isdigit(expression[i])) {
				int temp = expression[i] - '0';
				++i;
				while (i < n && isdigit(expression[i])) {
					temp *= 10;
					temp += expression[i] - '0';
					++i;
				}
			
				pushToStack(pOperandStack, &temp);
			} else if (isStackEmpty(pOperatorStack) == True){
					curOp = getOpcode(expression[i]);
					++i;
					pushToStack(pOperatorStack, &curOp);
			} else {
				curOp = getOpcode(expression[i]);
				getTopFromStack(pOperatorStack, &opInStack);
				
				priority = lookup[opInStack][curOp];
				if (priority == EQ_P) {
					++i;
					popFromStack(pOperatorStack);
				} else if (priority == LESS_P) {
					++i;
					pushToStack(pOperatorStack, &curOp);
				} else if (priority == BIG_P){
					if ( False == executeOneOpFromStack(pOperatorStack, pOperandStack))
						break;
				} else {
					break;
				}	 
			}	
		}
	}
	

	if (isStackEmpty(pOperatorStack) == True &
	    i == n &&
	    getSizeOfStack(pOperandStack) == 1) {
		getTopFromStack(pOperandStack, &temp);
		printf("\n%s = %d\n", expression, temp);	
	} else {
		printf("Invalid Expression\n");
	}


lexit:
	if (pOperatorStack != NULL) {
		destroyStack(&pOperatorStack);
	}
	if (pOperandStack != NULL) {
		destroyStack(&pOperandStack);
	}


	return 0;
}






















