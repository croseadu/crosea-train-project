#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define BOOL int

#define INIT_SIZE 10
#define INCREMENT_SIZE 10
#define isOperator(c) (c=='+' || c=='-' || c=='*' || c=='/' || c== '(' || c==')')
typedef struct{
	int *base;
	int *top;
	int maxLength;
}DATASTACK,*LPDATASTACK;
typedef struct{
	char *base;
	char *top;
	int maxLength;
}OPERATORSTACK,*LPOPERATORSTACK;

int initDataStack(LPDATASTACK *ppDataStack);
int getTopOfDataStack(LPDATASTACK pDataStack);
int pushDataStack(LPDATASTACK pDataStack,int data);
int popDataStack(LPDATASTACK pDataStack,int *pData);
int destroyDataStack(LPDATASTACK pDataStack);

int initOptrStack(LPOPERATORSTACK *ppOptrStack);
char getTopOfOptrStack(LPOPERATORSTACK pOptrStack);
int pushOptrStack(LPOPERATORSTACK pOptrStack,char optr);
int popOptrStack(LPOPERATORSTACK pOptrStack,char *pOptr);
int destroyOptrStack(LPOPERATORSTACK pOptrStack);
BOOL isOptrStackEmpty(LPOPERATORSTACK pOptrStack);
