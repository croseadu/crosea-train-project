#ifndef _MY_STACK_H
#define _MY_STACK_H

typedef struct _Stack
{
  char *base;
  unsigned int top;
}Stack, *LPStack;


BOOL createStack();
void destroyStack();


BOOL pushToStack(LPStack, const void *data);
void getTop(const LPStack, void *data);
void pop(LPStack);


BOOL isStackEmpty(const LPStack);





#endif
