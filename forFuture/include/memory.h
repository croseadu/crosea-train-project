#ifndef _MY_MEMORY_H
#define _MY_MEMORY_H

void *myMalloc(unsigned int size);
void myFree(void *);
void *myRealloc(void *, unsigned int newSize);

#define MALLOC myMalloc
#define FREE myFree
#define REALLOC myRealloc
#endif
