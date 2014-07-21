#ifndef _MY_COMMON_H
#define _MY_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define True 1
#define False 0

typedef int Result;
typedef int bool;

typedef bool (*LessFunc)(char *lhs, char *rhs);
typedef bool (*EqualFunc)(char *lhs, char *rhs);
typedef void (*Printer)(char *data);
typedef void (*Visitor)(char *data);
typedef bool (*Pred)(char *data);

enum SORT_ALGORITHM
{
  BUBBLE_SORT = 0,
  INSERT_SORT,
  SELECT_SORT,
  QUICK_SORT,
  MERGE_SORT,
  SHELL_SORT,
  RADIX_SORT,
  HEAP_SORT
};

#endif
