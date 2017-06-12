#include "memory.h"


#include <stdlib.h>
#include <assert.h>



void *myAlloc(size_t size)
{
	return malloc(size);
}


void myFree(void *p)
{
	free(p);
}

void *myReAlloc(void *p, size_t size)
{
	
	return realloc(p, size);
}



