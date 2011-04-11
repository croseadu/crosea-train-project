#include "../include/common.h"


typedef struct _GLIST 
{
  BOOL bIsAtom;
  union
  {
    char value;
    struct
    {
      struct _GLIST *hp;
      struct _GLIST *tp;
    }list;
  };
}GLIST, *LP_GLIST;

// (a, (b, (c,d, ()), e), ())
int main()
{
  STATUS status;






  return 0;
}

int calcDepth(const LP_GLIST pGList)
{
  LP_GLIST pIter;
  int max = 0;

  if (pGList == NULL)
    return 1;
  else if (pGList->bIsAtom)
    return 0;
  
  pIter = pGList->hp;
  while (pIter)
    {
      temp = calcDepth(pIter);
      if (temp > max)
	max = temp;
      pIter = pIter->tp;
    }
  return 1+max;
}
int calcLength(const LP_GLIST pGList)
{

}
STATUS createGList(LP_GLIST *ppGlist, const char *string)
{

}
