#ifndef _MY_COMMON_H
#define _MY_COMMON_H


typedef enum
{
	False,
	True,
} BOOL;

typedef void (*Printer)(const void *);

typedef void (*Visitor)(const void *);

typedef BOOL (*Less)(const void *lhs, const void *rhs);
typedef BOOL (*Pred)(const void *);


#endif
