#include "memory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>


void *myAlloc(unsigned int size)
{
	return malloc(size);
}


void myFree(void *ptr)
{
	free(ptr);
}

