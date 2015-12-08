#ifndef MY_COMMON_H
#define My_COMON_H


enum bool
{
  True = 0,
  False = 1,
};

typedef enum bool BOOL;


typedef void (*Printer)(const void *);
typedef void (*Visitor)(const void *);

typedef BOOL (*Predicate)(const void *);
typedef BOOL (*Less)(const void *lhs, const void *rhs);




#endif
