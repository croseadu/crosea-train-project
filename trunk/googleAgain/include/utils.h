#ifndef _MY_UTILS_H
#define _MY_UTILS_H

#include <assert.h>
#include <stdio.h>

#define ASSERT(x) \
  do {		  \
  if (!(x))       \
    printf("assert!!!, %s",#x); \
    assert(x); \
  } while(0)


void skipSpace(char **pp);
void skipDigit(char **pp);
void expectWhat(char **pp, const char c);
void advanceToWhat(char **p, const char c);

#endif
