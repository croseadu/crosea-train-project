#include "stack.h"
#include "common.h"
#include <assert.h>

void printer(const void *data)
{
	const char c = *(const char *)data;
	printf(" %c ", c);

}




int main()
{

	LPStack pStack;
	char buf[4096] = {'\0'};
	char *ptr;
	char topValue;	

	if (False == createStack(&pStack,
				 sizeof(char),
				 printer)) {
		printf("Failed to create stack!\n");
		exit(-1);
	}

	printf("\nPlease type a series of parenthese:");
	scanf("%s",buf);
	printf("\ninput string is %s:",buf);

		
	ptr = buf;
	skipSpace(&ptr);
	while (*ptr != '\0' && *ptr != '\n') {
		if (*ptr == '(' || *ptr == '[') {
			pushToStack(pStack, ptr);
			++ptr;
			skipSpace(&ptr);
		} else {
			if (*ptr != ')' && *ptr != ']' ) {
				break;
			}
			if (isStackEmpty(pStack)) {
				break;
			}
			getTopFromStack(pStack, &topValue);
			popFromStack(pStack);
			if (*ptr == ')' && topValue != '(')
				break;
			if (*ptr == ']' && topValue != '[')
				break;
			++ptr;
			skipSpace(&ptr);
		
		}

	}

	if (isStackEmpty(pStack) &&
	    (*ptr == '\0' || *ptr == '\n')) {
		printf("\nMatch parenthese");
	} else {
		printf("\nMismatch parenthese");
	}

cleanup:
	destroyStack(&pStack);

	return 0;
}
