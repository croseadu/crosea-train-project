#include "stack.h"





#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void
printInBinary(unsigned int num);

int main()
{
	
	int data;
	char c;	

	while(1) {
		printf("\nPls type the number which you want to conver to binary fomrat:");
		scanf("%d", &data);
		if (data >= 0)
			printInBinary(data);
		printf("Continue? Y/N:");
		c = getchar();
		if (c == '\n')
			c = getchar();
		if (c == 'N' || c == 'n')
			break;
		c = getchar();
	}



	return 0;
}


void
printInBinary(unsigned int num)
{
	LPStack pStack = NULL;
	unsigned int bit;

	if (False == createStack(&pStack, sizeof(unsigned int))) 
		exit(-1);

	while(1){
		bit = (num & 0x1) != 0 ? 1 : 0;
		pushToStack(pStack, &bit);
		if (num < 2)
			break;	
		num >>= 1;
	}

	printf(" Binary:0b");
	while(isStackEmpty(pStack) == False) {
		bit = 0;
		getTopOfStack(pStack, &bit);
		popFromStack(pStack);
		printf("%d", bit);
	}

	printf("\n");
	

	destroyStack(&pStack);
}
