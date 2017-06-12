

#include "utils.h"
#include <stdint.h>
#include <stdio.h>

void 
defaultPrinter(
	const void *ptr)
{
	printf(" %p ", ptr);
}

BOOL 
defaultLess(
	const void *left, 
	const void *right)
{
	return  (intptr_t)left < (intptr_t)right ? True : False;
}

void 
intPrinter(
	const void *ptr)
{
	int val = *(const int *)ptr;
	printf("%5d", val);
}


BOOL
intLess(
	const void *left, 
	const void *right)
{
	int leftVal = *(int *)left;
	int rightVal = *(int *)right;

	return leftVal < rightVal ? True : False;

}






