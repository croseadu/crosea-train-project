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
  }data;
}GLIST, *LP_GLIST;


int main()
{






  return 0;
}
