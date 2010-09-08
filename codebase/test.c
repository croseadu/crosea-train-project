#include "include/my.h"
#include "include/stack.h"


int main()
{
	LP_STACK pStack = NULL;
	int data;

	createStack(&pStack, sizeof(int));

	data = 0;
	push (pStack, &data);
	data = 1;
	push (pStack, &data);
	data = 2;
	push (pStack, &data);

	pop(pStack, &data);
	printf("\nFirst is %d", data);

	pop(pStack, &data);
	printf("\nSecond is %d", data);

	pop(pStack, &data);
	printf("\nThird is %d", data);

	destoryStack(pStack);


	return 0;
}
