#include <stdio.h>

#include "../include/stack.h"

typedef struct _Token
{
  bool isOperand;
  union
  {
    int operand;
    char op;
  }content;
}Token, *LPToken;

bool getNextToken(char **pp, LPToken pToken)
{
  char *p = *pp;
  unsigned int data = 0;

  while (1) {
    switch(*p) {
    case ' ':
    case '\t':
      {
	++p;
	break;
      }
    case '\0':
      {
	pToken->isOperand = false;
	pToken->content.op = '#';
	return true;
      }
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
      {
	pToken->isOperand = false;
	pToken->content.op = *p;
	++p;
	*pp = p;
	return true;
      }
    case '0':
      {
	if (!data) {
	  pToken->isOperand = true;
	  pToken->content.operand = 0;
	  ++p;
	  *pp = p;
	  return true;
	}
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
      {
	data *= 10;
	data += *p - '0';
	++p;
	if (!isdigit(*p)) {
	  *pp = p;
	  pToken->isOperand = true;
	  pToken->content.operand = data;
	  return true;
	}
      }
    default:
      return false;
    }

  }
}

static int getIdx(const char op)
{
  if (op == '+')
    return 0;
  if (op == '-')
    return 1;
  if (op == '*')
    return 2;
  if (op == '/')
    return 3;
  if (op == '(')
    return 4;
  if (op == ')')
    return 5;
  if (op == '#')
    return 6;
  return -1;
}


static const pred[][7] = {
   //+, -, *, /, (, ), #
// +
// -
// *
// /
// (
// )
// #
  { 1, 1,-1,-1, -1, 1, 1},
  { 1, 1,-1,-1, -1, 1, 1},
  { 1, 1, 1, 1, -1, 1, 1},
  { 1, 1, 1, 1, -1, 1, 1},
  {-1,-1,-1,-1, -1, 0, 0xFF},
  {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
  {-1,-1,-1,-1,-1, 0xFF, 0}
};

int doCalc(const char op, int lhs, int rhs)
{
  switch(op) {
  case '+': return lhs+rhs;
  case '-': return lhs-rhs;
  case '*': return lhs*rhs;
  case '/': return lhs/rhs;
  default:
    break;
  }
  printf("Invalid Operation in %s", __func__);
  return 0;
}

int main()
{
  
  LPStack pOperandStack;
  LPStack pOperationStack;
  char buf[4096];
  char *p = buf;
  Token curToken;

  initStack(&pOperandStack, sizeof(int));
  initStack(&pOperationStack, sizeof(char));

  char op = '#';
  push(pOperationStack, &op);
  
  scanf("%s", buf);
  getNextToken(&p, &curToken);

  while (!isStackEmpty(pOperationStack)) {
    if (curToken.isOperand) {
      push(pOperandStack, &curToken.content.operand);
      getNextToken(&p, &curToken);
    }
    else {
      char topOp;
      int topPred;
      getTop(pOperationStack, &topOp);
      
      topPred = pred[getIdx(topOp)][getIdx(curToken.content.op)];
      switch(topPred) {
      case 0:
	{
	  pop(pOperationStack, &topOp);
	  getNextToken(&p, &curToken);
	  break;
	}
      case 1:
	{
	  int lhs, rhs;
	  int result;

	  pop(pOperationStack, &topOp);
	  pop(pOperandStack, &rhs);
	  pop(pOperandStack, &lhs);
	  
	  result = doCalc(topOp, lhs, rhs);
	  push(pOperandStack, &result);
	  break;
	}
      case -1:
	{
	  push(pOperationStack, &curToken.content.op);
	  getNextToken(&p, &curToken);
	  break;
	}
      default:
	{
	  printf("Invalid expression since top vs cur is impossible\n");
	  break;
	}
      }

    }
  }

  if (*p != '\0' || !isStackEmpty(pOperationStack)
      || sizeOfStack(pOperandStack) != 1) {
    printf ("Wrong in expression, Failed to calculate\n");
  }
  else {
    int result;
    pop(pOperandStack, &result);
    printf("\n%s = %d\n", buf, result);
  }

  destroyStack(&pOperationStack);
  destroyStack(&pOperandStack);

  return 0;
}
