#include "stack.h"


#include "common.h"
#include <assert.h>



int main()
{
	LPStack pStack;
	char buf[4096] = {'\0'};
	char *ptr;	
	char topValue;

	if (False == createStack(&pStack,
				 sizeof(char),
				 printer)) {
		printf("Failed to create Stack");
		exit(-1);		
	}

	printf("Start line edit, # is backspace:\n");
	scanf("%s", buf);

	while (*ptr != '\0' && *ptr != '\n') {
		if (*ptr == '#') {
			if (!isStackEmpty(pStack)) {
				popFromStack(pStack);
			}
		} else {
			pushToStack(pStack, ptr);
		}
		++ptr;
	}


	printf("It is :\n");
	while (!isStackEmpty(pStack)) {
		getTopFromStack(pStack, &topValue);
		popFromStack(pStack);
		putchar(topValue);
	}

	putchar('\n');
cleanup:

	destroyStack(&pStack);

	return 0;
}
