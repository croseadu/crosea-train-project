#include "../../include/my.h"
#include "../../include/stack.h"

int main()
{
	int data, oridata;
	int temp;
	LP_STACK pStack = NULL;
		

	printf("Please input a data:\n");
	scanf("%d", &data);

	oridata = data;
	createStack(&pStack, sizeof(int));

	while (data%8)
	{
		temp = data%8;
		data = data/8;
		push(pStack,&temp);
	}
	printf("\nAfter Transform format:");
	while(!isStackEmpty(pStack))
	{
		pop(pStack, &temp);
		putchar(('0'+temp));
	}
	putchar('\n');
	printf("\nsystem output %o\n", oridata);

	destoryStack(pStack);

	return 0;
}
