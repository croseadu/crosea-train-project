#include "../include/memory.h"
#include "../include/common.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct _MemPool
{

}MemPool, *LPMemPool;

static void *poolAlloc(unsigned int size)
{
  //return allocate(&myAllocator.memoryPool);
  return NULL;
}
static void poolFree(void *ptr)
{
  //deAllocate(&myAllocator.memoryPool);
}

static void *poolRealloc(void *ptr, unsigned int newSize)
{
  return NULL;
}

typedef struct _Allocation
{
  unsigned int size;
  unsigned int allocationIdx;
  struct _Allocation *nextAllocation;
  char ptr[1];
}Allocation, *LPAllocation;

static struct _Allocator
{
  unsigned int nextAllocationIdx;
  LPAllocation pAllocations;
  MemPool memoryPool;
}myAllocator;

static BOOL isAllocatorInitialized = FALSE;

static void initAllocator()
{
  if (isAllocatorInitialized)
    return;
  isAllocatorInitialized = TRUE;
  myAllocator.nextAllocationIdx = 0;
  myAllocator.pAllocations = NULL;
  //initializeMemoryPool(&myAllocator.memoryPool);
}
void destroyAllocator()
{
  if (!isAllocatorInitialized)
    return;
  if (myAllocator.pAllocations != NULL) {
    printf ("Memory Leak Detected!");
  }
}

void * myMalloc(unsigned int size)
{
  //initAllocator();
  //return (size);
  return malloc(size);
}

void myFree(void *ptr)
{
  //assert(isAllocatorInitialized);
  //myAllocator.free(ptr);
  free(ptr);
}

void * myRealloc(void *ptr, unsigned int newSize)
{
  //assert(isAllocatorInitialized);
  //return myAllocator.m_realloc(ptr,newSize);
  return realloc(ptr,newSize);
}
