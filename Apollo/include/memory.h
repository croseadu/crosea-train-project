#ifndef _MY_MEMORY_H
#define _MY_MEMORY_H


void *myAlloc(size_t size);
void myFree(void *p);

void *myReAlloc(void *p, size_t size);


#endif

