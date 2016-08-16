#ifndef _MY_MEMORY_H
#define _MY_MEMORY_H

void *myAlloc(size_t size);
void myFree(void *ptr);
void *myRealloc(void *ptr, size_t newSize);

#endif

