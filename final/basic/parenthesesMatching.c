#include "stack.h"

#include "utils.h"


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>







int main()
{

	LPStack pStack;
	char strs[4096];
	char curTop;
	unsigned int i;
	bool matched;
	
	if (False == createStack(&pStack, sizeof(char), dummyPrint)) {
		exit(-1);
	}


	
	printf("Input a string of parentheses:");
	scanf("%s", strs);
	

	i = 0;
	matched = True;

	while (strs[i] != '\n' && strs[i] != '\0') {
		if (strs[i] == '(' || strs[i] == '{' || strs[i] == '[') {
			push(pStack, &strs[i]);
		} else {
			if (strs[i] != '}' && strs[i] != ')' && strs[i] != ']') {
				printf("\nInvalid Input!");
				matched = False;
				break;
			}			

			if (isStackEmpty(pStack) == True) {
				matched = False;
				break;
			}	
			
			pop(pStack, &curTop);
			switch (strs[i]) {
				default:
					assert(0);
					break;
				case '}':
					if (curTop != '{')
						matched = False;
					break;
				case ')':
					if (curTop != '(')
						matched = False;
					break;
				case ']':
					if (curTop != '[')
						matched = False;
					break;

			}		
		}		
		++i;
		
	}
	

	if (isStackEmpty(pStack) == True && matched == True) {
		printf("\n Matched Parentheses!");
	} else {
		printf("\n Not Matched!");
	}


	destroyStack(&pStack);


	return 0;
}
