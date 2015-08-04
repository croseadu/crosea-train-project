#include "stack.h"

#include <assert.h>


void printElement(const void *data)
{
	int val = *(int *)data;
	printf("%5d", val);
}

int main()
{
	LPStack pStack;
	int data, rem, div;


	if (False == createStack(&pStack, 
				  sizeof(unsigned int),
				  printElement)) {

		printf("Failed to create Stack!");
		exit(-1);
	}

	printf("\nPlease type a non-zero data you want to convert to 0x...:");
	scanf("%d", &data);
	if (data < 0) {
		printf("invalid data\n");
		goto cleanup;
	} else { printf("\n Input Data is %d", data);}

	

	div = data;
	do {
		rem = div % 2;
		div = div / 2;
		pushToStack(pStack, &rem);
	}while(div != 0);

	printf("\nConvert to 0x");
	while (!isStackEmpty(pStack)) {
		getTopFromStack(pStack, &data);
		popFromStack(pStack);
		printf("%d", data);

	}






cleanup:
	destroyStack(&pStack);

	return 0;
}
