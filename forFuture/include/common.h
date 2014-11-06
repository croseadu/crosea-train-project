#ifndef _MY_COMMON_H
#define _MY_COMMON_H
#define TRUE 1
#define FALSE 0

typedef int BOOL;

typedef void (*Printer)(void *);
typedef void (*Visitor)(void *in, void *argument);

typedef BOOL (*CompareFunc)(void *lhs, void *rhs);
typedef BOOL (*PredFunc)(void *in, void *argument);



#define INIT_SIZE 10
#define INCRE_SIZE 5





#endif
