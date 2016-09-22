#include "stack.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main()
{
	LPStack pStack = NULL;
	char buf[4096] = {'\0'};
	int idx;
	int len;
	char t;


	if (False == createStack(&pStack, sizeof(char))) {
		goto cleanup;
	}


	scanf("%s", buf);
	len = strlen(buf);
	idx = 0;

	while (idx < len) {
		if (buf[idx] == '#') {
			if (False == isStackEmpty(pStack)) {
				popFromStack(pStack);
			}
		} else {
			pushToStack(pStack, buf+idx);
		}
		
		++idx;
	}
	

	
	len = getSizeOfStack(pStack);
	buf[len] = '\0';
	while(len-- > 0) {
		getTopOfStack(pStack, &t);
		popFromStack(pStack);
		buf[len] = t;
	} 
	printf("\n%s\n", buf);


cleanup:
	if (pStack) {
		destroyStack(&pStack);
	}

	return 0;
}
