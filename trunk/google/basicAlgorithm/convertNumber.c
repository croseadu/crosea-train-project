#include "../include/stack.h"


int main()
{
  int inputNumber, remain, convertType, iterNum;
  LP_STACK pStack = NULL;

  printf("Input a number:");
  scanf("%d", &inputNumber);

  if (inputNumber < 0)
    {
      printf("Don't Support Negative Num now\n");
      return 0;
    }

  createStack(&pStack, sizeof(int));
  
  convertType = 8;
  if (inputNumber)
    {
      iterNum = inputNumber;
      while (remain = (iterNum % convertType))
	{
	  push(pStack, &remain);
	  iterNum = iterNum/convertType;
	}
    }
  else
    {
      push(pStack, &inputNumber);
    }
  
  printf("\n The number in is :");
  while (!isStackEmpty(pStack))
    {
      pop(pStack, &remain);
      putchar(('0' + remain));
    }

  printf("same as %o\n", inputNumber);


  destroyStack(pStack);

  return 0;
}
