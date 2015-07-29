#include <stdlib.h>
#include "myMemory.h"

void *myAlloc(size_t size)
{
  return malloc(size);
}

void *myReAlloc(void *ptr, size_t size)
{
  return realloc(ptr, size);
}

void myFree(void *ptr)
{
  free(ptr);
}
