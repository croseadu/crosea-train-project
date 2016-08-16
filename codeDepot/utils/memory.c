#include "memory.h"



#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>



//#define MEMSPY


void *
myAlloc(size_t size)
{
	return malloc(size);

}

void
myFree(void *ptr)
{
	return free(ptr);
}


void *
myRealloc(void *ptr, size_t size)
{
	return realloc(ptr, size);
}










