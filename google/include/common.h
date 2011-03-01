#ifndef _COMMON_H
#define _COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0

#define OK 0

#ifndef OVERFLOW
#define OVERFLOW 2
#endif

#define ERROR 1

#define R_EQ 0
#define R_LT -1
#define R_GT 1

typedef int BOOL;
typedef int STATUS;
typedef int S_RESULT;

#endif
