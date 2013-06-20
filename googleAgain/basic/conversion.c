#include <stdio.h>
#include <stdlib.h>
#include "../include/stack.h"



int main()
{
  LPStack pStack;
  int data, mod;

  initStack(&pStack, sizeof(unsigned int));
  
  scanf("%d", &data);
  if (data <= 0) {
    printf("Invalid input data\n");
    goto cleanup;
  }
  
  mod = 2;
  while (data) {
    int left = data%mod;
    push(pStack, &left);
    data /= mod;
  }

  printf("Convert to %d :", mod);
  while (!isStackEmpty(pStack)) {
    unsigned int out;
    pop(pStack, &out);
    printf("%d", out);
  }
  putchar('\n');

 cleanup:
  destroyStack(&pStack);
  return 0;
}
