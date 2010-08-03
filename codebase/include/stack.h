
#define INIT_STACK_SIZE 10
#define INCRE_STACK_SIZE 5

typedef struct _STACK
{
	void *pData;
	unsigned int top;
	unsigned int maxElements;
	unsigned int sizeOfElement;
}STACK, *LP_STACK;


STATUS createStack(LP_STACK *ppStack, unsigned int sizeOfElement);
void destoryStack(LP_STACK pStack);
STATUS push(LP_STACK pStack, void *pData);
STATUS pop(LP_STACK pStack, void *pData);
STATUS getTop(const LP_STACK pStack, void *pData);
STATUS isStackEmpty(const LP_STACK pStack);
