
#include "myMemory.h"
#include <stdio.h>
#include <stdlib.h>


void *myAlloc(size_t size)
{
  return alloc(size);
}

void myFree(void *ptr)
{
  free(ptr);
}

void *myReAlloc(void *ptr, size_t size)
{
	return realloc(ptr, size);
}





