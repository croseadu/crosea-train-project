

#include "../include/utils.h"
#include <ctype.h>



void skipSpace(char **pp)
{
  char *p = *pp;
  while(*p == ' ' || *p == '\t')
    ++p;
  *pp = p;
}

void skipDigit(char **pp)
{
  while (isdigit(**pp))
    ++(*pp);
}

void expectWhat(char **pp, const char c)
{
  ASSERT(**pp == c);
  ++(*pp);
}

void advanceToWhat(char **pp, const char c)
{
  while (**pp && **pp != c)
    ++(*pp);
}
