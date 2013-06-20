#include <stdio.h>
#include "../include/stack.h"



static bool isValidInput(const char c)
{
  if (c == '(' 
      || c == ')'
      || c == '['
      || c == ']'
      || c == '{'
      || c == '}')
    return true;
  return false;
}

static bool isOpenBrace(const char c)
{
  if (c == '('
      || c == '{'
      || c == '[')
    return true;
  return false;
}

static bool match(const char open, const char close)
{
  if ((open == '(' && close == ')')
      || (open == '[' && close == ']')
      || (open == '{' && close == '}'))
    return true;
  return false;
}

int main()
{
  LPStack pStack;
  char buf[4096];
  char *p = buf;
  bool isMatched = true;

  initStack(&pStack, sizeof(char));

  printf("Please input the string :\n");
  scanf("%s", buf);
  
  while (*p != '\0') {
    char c = *p;
    if (!isValidInput(c)) {
      isMatched = false;
      break;
    }

    if (isOpenBrace(c)) {
      push (pStack, &c);
    }
    else {
      char top;
      pop(pStack, &top);
      if (!match(top, c)) {
	isMatched = false;
	break;
      }
    }
    ++p;
  }

  if (!isMatched || !isStackEmpty(pStack))
    printf("\nNot Matched!!!");
  else
    printf("\nDo Macthed!!!");
  destroyStack(&pStack);
  return 0;
}
