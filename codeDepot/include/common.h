#ifndef _MY_COMMON_H
#define _MY_COMMON_H


enum _BOOL
{
  True = 0,
  False = 1,
};

typedef enum _BOOL BOOL;

#define INIT_SIZE 10
#define INCRE_SIZE 5



typedef void (*Printer)(const void *);
typedef void (*Visitor)(void *);


typedef BOOL (*Less)(const void *lhs, const void *rhs);
typedef BOOL (*Equal)(const void *lhs, const void *rhs);


typedef BOOL (*Pred)(const void *);

#endif
