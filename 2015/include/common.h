#ifndef _MY_COMMON_H
#define _MY_COMMON_H

enum BOOL{
  True = 0,
  False = 1;
};

typedef void (*VisitFunc)(void *data, void *parameter);
typedef void (*PrintFunc)(void *data, void *parameter);
typedef BOOL (*LessFunc)(void *lhs, void *rhs);
typedef BOOL (*EqualFunc)(void *lhs, void *rhs);
typedef BOOL (*PredFunc)(void *lhs, void *parameter); 

#endif
