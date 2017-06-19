#include "stack.h"

#include "common.h"



#include <stdio.h>
#include <assert.h>



typedef enum _Operator
{
	ADD,
	SUB,
	MUL,
	DIV,
	LEFT_P,
	RIGHT_P,
	LAST_OP,
}Operator;


BOOL
executeOneOpFromStack(
	LPStack pOperatorStack,
	LPStack pOperandStack)
{
	Operator opcode = LAST_OP;
	int result;
	int rightOperand, leftOperand;


	assert(isStackEmpty(pOperatorStack) == False);

	getTopFromStack(pOperatorStack, opcode);
	popFromStack(pOperatorStack);
			
	if (getSizeOfStack(pOperandStack) < 2)
		return False;

	getTopFromStack(pOperandStack, &rightOperand);
	popFromStack(pOperandStack);

	getTopFromStack(pOperandStack, &leftOperand);
	popFromStack(pOperandStack);

	doCalculation(opcode, leftOperand, rightOperand);
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
	



}



Priority
compareOpcode(Operator opOnStack, Operator curOp)
{
}


int main()
{
	LPStack pOperatorStack = NULL;
	LPStack pOperandStack = NULL;
	char expression[4096] = {'\0'};


	if (False == createStack(&pOperatorStack,
				 sizeof(Operator),
				 operatorPrinter)) {
		goto lexit;
	}


	if (False == createStack(&pOperandStack,
				 sizeof(int),
				 intPrinter)) {
		goto lexit:
	}


	FILE *fp = fopen("expression.txt", "r");
	if (fp == NULL) {
		goto lexit;
	}	


	fscanf(fp,"%s", expression);
	
	n = strlen(expression);
	if (n == 0) {
		printf("Invalid Expression\n");
		goto lexit;
	}
	
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
				
			} else {
				Operator opInStack, curOp;
				getTopFromStack(pOperatorStack, &opInStack);
				
				Priority priority = compareOpcode(opInStack, curOp);
				if (priority == EQ_P) {
					++i;
					popFromStack(pOperatorStack);
				} else if (priority == Less_P) {
					++i;
					pushToStack(pOperatorStack, &curOp);
				} else if (priority == BIG_P){
					executeOneOpFromStack(pOperatorStack, pOperandStack);
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
		destroyStack(&pOprandStack);
	}


	return 0;
}






















