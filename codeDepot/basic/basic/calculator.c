#include "stack.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


enum Operator
{
	ADD,
	SUB,
	MUL,
	DIV,
	LEFT_P,
	RIGHT_P,
	POUND,
	OpCount,
};

typedef enum Operator OpType;

OpType
getOpcode(const char c)
{

	switch(c) {
		case '+': return ADD;
		case '-': return SUB;
		case '*': return MUL;
		case '/': return DIV;
		case '(': return LEFT_P;
		case ')': return RIGHT_P;
		case '#': return POUND;
	}

	return OpCount;
}

BOOL
lessOp(const void *lhs, const void *rhs)
{
	OpType leftOp = *(OpType *)lhs;
	OpType rightOp = *(OpType *)rhs;

	return leftOp < rightOp ? True : False;
}


enum OPCompareResult
{
	OpLess,
	OpEqual,
	OpGreater,
	InvalidSeq,	
};

enum OPCompareResult
compareOpcode(OpType curOp, OpType opOnStack)
{
	switch(curOp) {
		case ADD:
		case SUB:
			switch(opOnStack) {
				case ADD:
				case SUB:
				case MUL:
				case DIV:
					return OpLess;
				case LEFT_P:
				case POUND:
					return OpGreater;
				default:
					break;


			}
			break;
		
		case MUL:
		case DIV:
			switch (opOnStack) {
				case MUL:
				case DIV:
					return OpLess;
				case ADD:
				case SUB:
				case LEFT_P:
				case POUND:
					return OpGreater;
			
				default:
					break;
			}			
			break;

		case LEFT_P:
			switch (opOnStack) {
				case RIGHT_P:
					break;
				default:
					return OpGreater;
			}
			

		case RIGHT_P:
			switch(opOnStack) {
				case LEFT_P:
					return OpEqual;
				case ADD:
				case SUB:
				case DIV:
				case MUL:
					return OpLess;
				default:
				break;
			}
			break;			

		case POUND:
			switch (opOnStack) {
				case POUND:
					return OpEqual;
				case ADD:
				case SUB:
				case MUL:
				case DIV:
					return OpLess;
				default:
					break;
			}

	}

	return InvalidSeq;

}

int doCalc(int left, int right, OpType op)
{
	switch(op) {
		case ADD: return left + right;
		case SUB: return left - right;
		case MUL: return left * right;
		case DIV: return left/right;
		default: break;
	}
	assert(0 && "Invalid OP");
	return 0;
}


int main()
{
	LPStack pOperandStack = NULL;
	LPStack pOperatorStack = NULL;
	char buf[4096] = {'\0'};
	FILE *fp = NULL;
	int size;
	int idx;
	int number;
	OpType opcode, opcodeOnStack;
	int leftOperand, rightOperand;
	enum OPCompareResult compare;
	int result;

	if (NULL ==(fp = fopen("input.txt", "r"))) {
		goto cleanup;
	}
	
	if (False == createStack(&pOperandStack, sizeof(int))) {
		goto cleanup;
	}

	if (False == createStack(&pOperatorStack, sizeof(OpType))) {
		goto cleanup;
	}

	fscanf(fp, "%s", buf);
	size = strlen(buf);

	if (size == 0)
		goto cleanup;

	buf[size] = '#';
	++size;
	buf[size] = '\0';

	idx = 0;
	opcode = POUND;
	pushToStack(pOperatorStack, &opcode);	
	skipSpace(buf, &idx);
	while (isStackEmpty(pOperatorStack) == False || idx < size) {
		if (idx < size) {
			if (isdigit(buf[idx])) {
				sscanf(buf+idx, "%d", &number);
				pushToStack(pOperandStack, &number);
				while(isdigit(buf[idx]))
					++idx;
				skipSpace(buf, &idx);	
			} else {
				opcode =getOpcode(buf[idx]);
				getTopOfStack(pOperatorStack, &opcodeOnStack);
				compare = compareOpcode(opcode, opcodeOnStack);
				if (compare == InvalidSeq) {
					printf("\nInvalid Seq\n");
					break;
				}
				if(compare == OpGreater) {
					pushToStack(pOperatorStack, &opcode);
					++idx;
					skipSpace(buf, &idx);
				} else if (compare == OpEqual) {
					popFromStack(pOperatorStack);
					++idx;
					skipSpace(buf, &idx);
				} else {
					popFromStack(pOperatorStack);
					if (getSizeOfStack(pOperandStack) < 2) {
						printf("\nNot Enough Operand\n");
						break;
					}
					getTopOfStack(pOperandStack, &rightOperand);
					popFromStack(pOperandStack);
					getTopOfStack(pOperandStack, &leftOperand);
					popFromStack(pOperandStack);
					result = doCalc(leftOperand, rightOperand, opcodeOnStack);
					pushToStack(pOperandStack, &result);
				}			
			}

		} else {


		}
	}



	if (idx < size ||
	    isStackEmpty(pOperatorStack) == False ||
	    getSizeOfStack(pOperandStack) != 1) {
		printf("Invalid Expression\n");
	}

	getTopOfStack(pOperandStack, &number);
	printf("result = %d\n",number);



cleanup:
	if (fp != NULL) {
		fclose(fp);
	}
	if (pOperandStack != NULL) {
		destroyStack(&pOperandStack);
	}
	if (pOperatorStack != NULL) {
		destroyStack(&pOperatorStack);
	}

	return 0;
}
