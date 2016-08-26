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
