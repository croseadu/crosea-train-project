#include "stack.h"
#include "utils.h"


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>














int main()
{


	LPStack pStack;
	char strs[4096];
	unsigned int i;
	char dummy;
	char newstr[4096];
	unsigned int size;




	if (False == createStack(&pStack, sizeof(char), dummyPrint)) {
		exit(-1);		
	}


	scanf("%s", strs);
	i = 0;
	while(strs[i] != '\0' && strs[i] != '\n') {
		if (strs[i] == '#') {
			if (False == isStackEmpty(pStack)) {
				pop(pStack, &dummy);
			}
		} else {
			push(pStack, &strs[i]);
		}
	
		++i;
	}


	size = getSizeOfStack(pStack);
	if (size > 0) {
		newstr[size] = 0;
		while (size-- > 0) {
			assert(isStackEmpty(pStack) == False);
			pop(pStack, &newStr[size]);
		}
		assert(iStackEmpty(pStack) == True);
		printf("Final input is:%s\n", newStr);

	} else {
		printf("\nFinal input is empty!\n");
	}


	destroyStack(&pStack);
	return 0;
}
