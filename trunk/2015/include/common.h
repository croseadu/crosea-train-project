#ifndef _MY_COMMON_H
#define _MY_COMMON_H

typedef enum{
  True = 0,
  False = 1,
} BOOL;

typedef void (*VisitFunc)(void *data, void *parameter);
typedef void (*PrintFunc)(void *data);
typedef BOOL (*LessFunc)(void *lhs, void *rhs);
typedef BOOL (*EqualFunc)(void *lhs, void *rhs);
typedef BOOL (*PredFunc)(void *lhs, void *parameter); 

#endif
