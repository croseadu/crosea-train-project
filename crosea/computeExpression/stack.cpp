#include <StdAfx.h>
#include "my.h"
// all data stack utility
int initDataStack(LPDATASTACK *ppDataStack)
{
	(*ppDataStack) = (LPDATASTACK)malloc(sizeof(DATASTACK));
	if (!(*ppDataStack))
		return FALSE;
	(*ppDataStack)->base = NULL;
	(*ppDataStack)->base = (int *)malloc(sizeof(int)*INIT_SIZE);
	if (!(*ppDataStack)->base)
		return FALSE;
	(*ppDataStack)->top = (*ppDataStack)->base;
	(*ppDataStack)->maxLength = INIT_SIZE;
	return TRUE;
}
int getTopOfDataStack(LPDATASTACK pDataStack)
{
	if (pDataStack->base != pDataStack->top)
		return *(pDataStack->top-1);
}
int pushDataStack(LPDATASTACK pDataStack,int data)
{
	if (!pDataStack)
		return FALSE;
	if (pDataStack->top - pDataStack->base >= pDataStack->maxLength)
	{
		pDataStack->base = (int *)realloc(pDataStack->base,sizeof(int)*(pDataStack->maxLength*INCREMENT_SIZE));
		if (!pDataStack->base)
			return FALSE;	
		pDataStack->maxLength +=INCREMENT_SIZE;
	}
	*pDataStack->top++ = data;
	return TRUE;

}
int popDataStack(LPDATASTACK pDataStack,int *pData)
{
	if (pDataStack->base == pDataStack->top) 
		return FALSE;
	*pData = *--pDataStack->top;
	return TRUE;
}
int destroyDataStack(LPDATASTACK pDataStack)
{
	if (!pDataStack)
		return TRUE;
	if (pDataStack->base)
		free(pDataStack->base);
	return TRUE;
}


// all operator stack utility
int initOptrStack(LPOPERATORSTACK *ppOptrStack)
{
	(*ppOptrStack) = (LPOPERATORSTACK)malloc(sizeof(OPERATORSTACK));
	if (!(*ppOptrStack))
		return FALSE;
	(*ppOptrStack)->base = NULL;
	(*ppOptrStack)->base = (char *)malloc(sizeof(char)*INIT_SIZE);
	if (!(*ppOptrStack)->base)
		return FALSE;
	(*ppOptrStack)->top = (*ppOptrStack)->base;
	(*ppOptrStack)->maxLength = INIT_SIZE;
	return TRUE;
}
char getTopOfOptrStack(LPOPERATORSTACK pOptrStack)
{
	if (pOptrStack->base != pOptrStack->top)
		return *(pOptrStack->top-1);
	else
		return '(';
}
int pushOptrStack(LPOPERATORSTACK pOptrStack,char optr)
{
	if (!pOptrStack)
		return FALSE;
	if (pOptrStack->top - pOptrStack->base >= pOptrStack->maxLength)
	{
		pOptrStack->base = (char *)realloc(pOptrStack->base,sizeof(char)*(pOptrStack->maxLength*INCREMENT_SIZE));
		if (!pOptrStack->base)
			return FALSE;	
		pOptrStack->maxLength +=INCREMENT_SIZE;
	}
	*pOptrStack->top++ = optr;
	return TRUE;

}
int popOptrStack(LPOPERATORSTACK pOptrStack,char *pOptr)
{
	if (pOptrStack->base == pOptrStack->top) 
		return FALSE;
	*pOptr = *--pOptrStack->top;
	return TRUE;
}
int destroyOptrStack(LPOPERATORSTACK pOptrStack)
{
	if (!pOptrStack)
		return TRUE;
	if (pOptrStack->base)
		free(pOptrStack->base);
	return TRUE;
}
BOOL isOptrStackEmpty(LPOPERATORSTACK pOptrStack)
{
	if (!pOptrStack)
		return TRUE;
	if (pOptrStack->base == pOptrStack->top)
		return TRUE;
	return FALSE;

}