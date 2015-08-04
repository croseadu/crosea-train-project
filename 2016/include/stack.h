#ifndef _MY_StACK_H
#define _MY_STACK_H

#include "common.h"

#define INIT_STACK_SIZE 10
#define INCRE_STACK_SIZE 5

typedef struct _STACK
{
	char *top;
	char *base;
	unsigned int capacity;
	unsigned int elementSize;
	Printer printer;
}Stack, *LPStack;


enum BOOL createStack(LPStack *ppStack,
		      unsigned int elementSize,
		      Printer printer);

void destroyStack(LPStack *ppStack);

enum BOOL isStackEmpty(const LPStack pStack);
unsigned int getStackSize(const LPStack pStack);
void popFromStack(LPStack pStack);
enum BOOL pushToStack(LPStack pStack, const void *data);
void getTopFromStack(const LPStack pStack, void *data);

#endif


