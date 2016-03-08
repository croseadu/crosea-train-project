#ifndef _MY_COMMON_H
#define _MY_COMMON_H


enum BOOL
{
  True = 0,
  False
};

typedef enum BOOL bool;


typedef void (*Printer)(const void *);
typedef bool (*Less)(const void *lhs, const void *rhs);
typedef bool (*Pred)(const void *);

typedef void (*Visitor)(const void *);






#endif
