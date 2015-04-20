#include <stdio.h>
#include <stdlib.h>

enum BOOL
{
  True,
  False,
};

typedef void (*Printer)(void *data);
typedef BOOL (*Less)(void *lhs, void *rhs);
typedef BOOL (*Equal)(void *lhs, void *rhs);
typedef void (*Visitor)(void *data);
typedef BOOL (*Pred)(void *data);

