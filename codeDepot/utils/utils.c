#include "utils.h"


BOOL
defaultLess(const void *lhs, const void *rhs)
{
	return (unsigned int)lhs < (unsigned int)rhs;
}


void defaultPrinter(const void *data)
{
	printf("  %p  ", data);
}


BOOL
lessInt(const void *lhs, const void *rhs)
{
	int lhsVal = *(int *)lhs;
	int rhsVal = *(int *)rhs;

	return lhsVal < rhsVal ? True : False;
}


void
printInt(const void *data)
{
	int val = *(int *)data;
	printf("%5d", val);
}

