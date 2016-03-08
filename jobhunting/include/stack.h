#ifndef MY_STACK_H
#define MY_STACK_H
#include "common.h"


#define INIT_STACK_SIZE 10
#define INCRE_STACK_SIZE 5


typedef struct _Stack
{
	char *top;
	char *base;

	unsigned int elementSize;
	unsigned int capability;	
	Printer  printer;
}Stack, *LPStack;


BOOL createStack(LPStack *,unsigned int elementSize, Printer printer);
void destroyStack(LPStack *);

BOOL pushToStack(LPStack , const void *data);
void getTopOfStack(LPStack, void *data);
void popFromStack(LPStack);
BOOL isStackEmpty(const LPStack);



#endif
