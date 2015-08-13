#ifndef _MY_COMMON_H
#define _MY_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum BOOL 
{
 True = 1,
 False = 0
};

typedef void (*Printer)(const void *data);
typedef enum BOOL (*Less)(const void *lhs, const void *rhs);
typedef enum BOOL (*Pred)(const void *data);
typedef void (*Visitor)(void *data);



#define INIT_SIZE 10
#define INCRE_SIZE 5


enum BOOL isEOF(const char in);

void skipSpace(char **ppChar);


enum BOOL match(const char in, const char ref);
void advanceTill(char **ppChar, const char ref);

#include "myMemory.h"

#endif
