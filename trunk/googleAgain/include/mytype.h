#ifndef _MY_TYPE_H
#define _MY_TYPE_H

typedef int bool;

enum STATUS
{
  true = 1,
  false = 0
};


typedef void (* VisitFunc)(void *val);
typedef bool (* PredFunc)(void *val);
typedef void (* PrintFunc)(void *val);
typedef bool (* CompareFunc)(void *lhs, void *rhs);

#endif
