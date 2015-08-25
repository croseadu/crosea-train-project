#include "stack.h"


#include "common.h"


#include <assert.h>


enum Operator
{
	ADD = 0,
	SUB,
	MUL,
	DIV,
	L_SQUARE,
	R_SQUARE,
	FAKE_OP,
};

char *opName[] = {
	"+",
	"-",
	"*",
	"/",
	"(",
	")",
	"#"
};



typedef struct _Token
{
	enum BOOL isValid;
	enum BOOL isOperator;
	union {
		int val;
		enum Operator op;		
	}content;
}Token, *LPToken;


enum Comparison
{
	LessThan 	= -1,
	EqualWith 	= 0,
	BigThan	 	= 1,
	InvalidCompare 	= 2,
};


enum Comparison  
precede(enum Operator top, enum Operator cur)
{
	enum Comparison result = InvalidCompare;
	
	switch (top) {
		default:
			printf("Invalid Op:top");
			return result;
		case ADD:
		case SUB:
			switch(cur) {
				default:
					printf("Invalid Op sequence!");
					return result;

				case ADD:
				case SUB:
					result = BigThan;
					return result;		
				case MUL:
				case DIV:
					result = LessThan;
					return result;
				case L_SQUARE:
					result = LessThan;
					return result;
				case FAKE_OP:
				case R_SQUARE:
					result = BigThan;
					return result;

			}
			break;
		case MUL:
		case DIV:
			switch(cur) {
				default:
					printf("Invalid Op sequence!");
					return result;
				case ADD:
				case SUB:
				case MUL:
				case DIV:
					result = BigThan;
					return result;
				case L_SQUARE:
					result = LessThan;
					return result;
				case FAKE_OP:
				case R_SQUARE:
					result = BigThan;
					return result;

			}
			break;


		case L_SQUARE:
			switch(cur) {
				default:
					printf("Invalid op sequence!");
					return result;
				case R_SQUARE:
					result = EqualWith;
					return result;
				case ADD:
				case MUL:
				case DIV:
				case SUB:
				case L_SQUARE:
					result = LessThan;
					return result;

			}
		case FAKE_OP:
			switch(cur) {
				default:
					printf("Invalid Op Sequence");
					return result;
				case ADD:
				case SUB:
				case DIV:
				case MUL:
				case L_SQUARE:
					result = LessThan;
					return result;
				case FAKE_OP:
					result = EqualWith;
					return result;
			}
	}

	return result;
}



int doCalc(enum Operator op, int lhsVal, int rhsVal)
{
	int result = 0;
	switch(op) {
		case ADD:
			result = lhsVal + rhsVal;
			break;
		case SUB:
			result = lhsVal - rhsVal;
			break;
		case MUL:
			result = lhsVal * rhsVal;
			break;
		case DIV:
			result = lhsVal/rhsVal;
			break;
		default:
			assert(0 && "Invalid Op in DoCal\n");
			break;


	}

	return result;

}

void
getNextToken(char **pptr, LPToken pToken)
{
	char *ptr;
	unsigned int val;
	skipSpace(pptr);
	
	ptr = *pptr;

	
		switch(*ptr) {
			case '\0':
			case '\n':
				pToken->isValid = False;
				*pptr = ptr;
				return;
			case '+':
				pToken->isValid = True;
				pToken->isOperator = True;
				pToken->content.op = ADD;
				++ptr;
				*pptr = ptr;
				return;
			case '-':
				pToken->isValid = True;
				pToken->isOperator = True;
				pToken->content.op = SUB;
				++ptr;
				*pptr = ptr;
				return;
			case '*':
				pToken->isValid = True;
				pToken->isOperator = True;
				pToken->content.op = MUL;
				++ptr;
				*pptr = ptr;
				return;
			case '/':
				pToken->isValid = True;
				pToken->isOperator = True;
				pToken->content.op = DIV;
				++ptr;
				*pptr = ptr;
				return;
			case '(':
				pToken->isValid = True;
				pToken->isOperator = True;
				pToken->content.op = L_SQUARE;
				++ptr;
				*pptr = ptr;
				return;
			case ')':
				pToken->isValid = True;
				pToken->isOperator = True;
				pToken->content.op = R_SQUARE;
				++ptr;
				*pptr = ptr;
				return;
				
			case '#':
				pToken->isValid = True;
				pToken->isOperator = True;
				pToken->content.op = FAKE_OP;
				++ptr;
				*pptr = ptr;
				return;

			
				
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				val = *ptr - '0';
				++ptr;
				while (isdigit(*ptr)) {
					val *= 10;
					val += *ptr - '0';
					++ptr;
				}	
				pToken->isValid = True;
				pToken->isOperator = False;
				pToken->content.val = val;
				*pptr = ptr;
				return;
			case '0':
				++ptr;
				*pptr = ptr;
				pToken->isValid = True;
				pToken->isOperator = False;
				pToken->content.val = 0;
				return;					
		}

	return;

}

void 
operandPrinter(const void *val)
{
	int  operand = *(int *)val;
	printf(" %d ", operand);

}

void 
operatorPrinter(const void *val)
{
	enum Operator op = *(enum Operator *)val;
	char opChar;
	switch(op) {
		case ADD: opChar = '+'; break;
		case SUB: opChar = '-'; break;
		case MUL: opChar = '*'; break;
		case DIV: opChar = '/'; break;
		case L_SQUARE: opChar = '('; break;
		case R_SQUARE: opChar = ')'; break;
		case FAKE_OP: opChar = '#'; break;
		default:
			printf("unknown op");
			return;

	}
	printf(" %c ", opChar);
}

int main()
{

	LPStack 	pOperandStack 		= NULL;
	LPStack 	pOperatorStack 		= NULL;
	char 		buf[4096] 		= {'\0'};
	int		i			= 0;
	char*		ptr			= NULL;
	enum Operator	topOperatorVal;
	unsigned int    topOperandVal;
	int		lhsVal;
	int 		rhsVal;
	int    		calVal;
	enum Comparison compareResult;
	Token		curToken;
	int		step = 0;


	if (False == createStack(&pOperandStack,
				 sizeof(int),
				 operandPrinter)) {

		printf("Failed to create Stack");
		goto cleanup;
	}


	if (False == createStack(&pOperatorStack,
				 sizeof(enum Operator),
				 operatorPrinter)) {

		printf("Failed to create Stack");
		goto cleanup;
	}



	printf("Please input an expression, only contain integer operand:\n");
	scanf("%s", buf);
	ptr = buf;
	while(*ptr != '\n' && *ptr != '\0') {
		if (*ptr == '#') {
			break;
		}
		++ptr;
	}
	if (*ptr == '#') {
		printf("Invalid input\n");
		goto cleanup;
	}

//	*ptr = '#';
	ptr = buf;
	topOperatorVal = FAKE_OP;
//	pushToStack(pOperatorStack, &topOperatorVal);
	getNextToken(&ptr, &curToken);	
	while (!isStackEmpty(pOperatorStack) || curToken.isValid) {
		if (curToken.isValid) {
			if (!curToken.isOperator) {
				printf("\nStep %d, push operand %d", ++step, curToken.content.val);
				pushToStack(pOperandStack, &curToken.content.val);
				getNextToken(&ptr, &curToken);
			} else {
				if (isStackEmpty(pOperatorStack)) {
					printf("\nStep %d, push operator %s", ++step, opName[curToken.content.op]);
					pushToStack(pOperatorStack, &curToken.content.op);
					getNextToken(&ptr, &curToken);

				} else {
					getTopFromStack(pOperatorStack, &topOperatorVal);
					compareResult = precede(topOperatorVal, curToken.content.op);
					if (compareResult == InvalidCompare) {
						break;
					}
					switch(compareResult) {
						default:
							assert(0 && "Impossible");
							break;
						case EqualWith:
							printf("\nStep %d, pair parenthese", ++step);
							popFromStack(pOperatorStack);
							getNextToken(&ptr, &curToken);
							break;
						case LessThan:
							printf("\nStep %d, push operator %s", ++step, opName[curToken.content.op]);
							pushToStack(pOperatorStack, &curToken.content.op);
							getNextToken(&ptr, &curToken);
							break;
						case BigThan:
			
							getTopFromStack(pOperandStack, &rhsVal);
							popFromStack(pOperandStack);
							getTopFromStack(pOperandStack, &lhsVal);
							popFromStack(pOperandStack);
							calVal = doCalc(topOperatorVal, lhsVal, rhsVal);
							pushToStack(pOperandStack, &calVal);
							popFromStack(pOperatorStack);

							printf("\nStep %d, lhs %d Op: %s rhs %d", ++step, lhsVal, opName[topOperatorVal], rhsVal);
							break;				
					}

				}
			}

		} else {
			// Reach end, should do operation for OP on Stack
			getTopFromStack(pOperatorStack, &topOperatorVal);
			popFromStack(pOperatorStack);
			getTopFromStack(pOperandStack, &rhsVal);
			popFromStack(pOperandStack);
			getTopFromStack(pOperandStack, &lhsVal);
			popFromStack(pOperandStack);
			calVal = doCalc(topOperatorVal, lhsVal, rhsVal);
			pushToStack(pOperandStack, &calVal);
			printf("\nStep %d, lhs %d Op: %s rhs %d", ++step, lhsVal, opName[topOperatorVal], rhsVal);
		}	

	}

	if (curToken.isValid || !isStackEmpty(pOperatorStack) || getStackSize(pOperandStack) != 1) {
		printf("\nFailed to evaluate expression");
		goto cleanup;
	}

	getTopFromStack(pOperandStack, &topOperandVal);
	printf("\n%s = %d\n", buf, topOperandVal);

cleanup:
	if (pOperandStack != NULL) {
		destroyStack(&pOperandStack);
	}
	if (pOperatorStack != NULL) {
		destroyStack(&pOperatorStack);
	}



	return 0;
}
