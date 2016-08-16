#ifndef _MY_COMMON_H
#define _MY_COMMON_H


typedef enum{
	True = 0,
	False = 1

}BOOL;


#define INIT_SIZE 10
#define INCRE_SIZE 5



typedef void (*Visitor)(void *);
typedef void (*Printer)(const void *);

typdeef BOOL (*less)(const void *lhs, const void *rhs);
typedef BOOL (*Pred)(const void *);


#ifndef NDEBUG
#define DBG(x) x
#else
#define DBG(x)
#endif

#endif
