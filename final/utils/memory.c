
#include "myMemory.h"
#include <stdio.h>
#include <stdlib.h>


void *myAlloc(unsigned int size)
{
  return malloc(size);
}

void myFree(void *ptr)
{
  free(ptr);
}

void *myReAlloc(void *ptr, unsigned int size)
{
	return realloc(ptr, size);
}





