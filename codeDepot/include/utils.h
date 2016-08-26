#ifndef _MY_UTILS_H
#define _MY_UTILS_H


#include "common.h"

#define AlignTo64(x)  ( ((x)&7 != 0) ? ((x)&(~7) + 8) : (x) )




void defaultPrinter(const void *);

BOOL defaultLess(const void *lhs, const void *rhs);










#endif

