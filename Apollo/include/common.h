#ifndef _MY_COMMON_H
#define _MY_COMMON_H


enum Bool
{
	True = 0,
	False,
};

typedef enum Bool BOOL;


#define INIT_SIZE 10
#define INCRE_SIZE 5


typedef void (*Printer)(const void *);
typedef BOOL (*Less)(const void *, const void *);
typedef BOOL (*Pred)(const void *);

typedef void (*Visitor)(void *);



#endif
