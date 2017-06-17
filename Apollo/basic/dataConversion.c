#include "stack.h"


#include "utils.h"

#include <stdio.h>
#include <assert.h>








int main()
{

	LPStack pStack = NULL;
	int temp, data;
	char hex[]=  "0123456789ABCDEF";


	if (False == createStack(&pStack,
				 sizeof(unsigned int),
				 intPrinter)) {
		goto lexit;
	}


	printf("Input a number:");

	scanf("%d", &temp);
			
	while(temp != 0) {
		data = temp % 16;
		temp >>= 4;
		pushToStack(pStack, &data);
	} 
	
	
	printf("  convert to : 0x");
	while (isStackEmpty(pStack) == False) {
		getTopFromStack(pStack, &data);
		putchar(hex[data]);
		popFromStack(pStack);
	}
	printf("\n");
lexit:

	if (pStack != NULL)
		destroyStack(&pStack);


	return 0;
}

