#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"
#include "../include/doubleLinkList.h"

typedef struct _POLY
{
  int exponent;
  float coefficient;
}Poly, *LPPoly;

static printCount = 0;
static void resetPrinter()
{
  printCount = 0;
}
static void print(void *val)
{
  
  LPPoly pItem = (LPPoly)val;
  if (printCount++ > 0)
    putchar('+');

  if (pItem->exponent > 0)
    printf("%f * X^^%d", pItem->coefficient, pItem->exponent);
  else
    printf("%f", pItem->coefficient);
}

static bool equal(void *lhs, void *rhs)
{
  LPPoly pLhs, pRhs;
  pLhs = (LPPoly)lhs;
  pRhs = (LPPoly)rhs;

  return pLhs->coefficient == pRhs->coefficient 
    && pLhs->exponent == pRhs->exponent;
}

static bool less(void *lhs, void *rhs)
{
  LPPoly pLhs, pRhs;
  pLhs = (LPPoly)lhs;
  pRhs = (LPPoly)rhs;

  return pLhs->exponent < pRhs->exponent; 
 }


void mergePoly(LPDoubleLinkList pResult,
	       LPDoubleLinkList pLhs,
	       LPDoubleLinkList pRhs)
{
  
}

int main()
{
  LPDoubleLinkList pListA, pListB, pListC;
  char buf[4096];
  FILE *fp;
  char *p = buf;
  float coff;
  int exp;

  if ((fp = fopen("inPoly.txt", "r")) == NULL) {
    printf("Couldn't open input file: %s", "inPoly.txt");
    exit(-1);
  }



  if (fread(buf, sizeof(char),4096, fp) <=0 ) {
    printf("Empty File\n");
    fclose(fp);
    exit(-1);
  }

  initDoubleLinkList(&pListA,sizeof(Poly), print, equal, less);
  initDoubleLinkList(&pListB,sizeof(Poly), print, equal, less);
  initDoubleLinkList(&pListC,sizeof(Poly), print, equal, less);
  
  
  skipSpace(&p);
  while (*p && *p != '\n') {
    Poly item;

    expectWhat(&p, '(');
    sscanf(p, "%f", &coff);

    advanceToWhat(&p, ',');
    expectWhat(&p, ',');
  
    sscanf(p, "%d", &exp);
    
    advanceToWhat(&p, ')');
    expectWhat(&p, ')');
    skipSpace(&p);

    item.exponent = exp;
    item.coefficient = coff;
    insertToDoubleLinkListTail(pListA, (void *)&item);
  }
  expectWhat(&p, '\n');
  printf("\nPoly A: ");
  resetPrinter();
  printDoubleLinkList(pListA);
  sortDoubleLinkList(pListA);
  printf("\nAfter Sorted: ");
  resetPrinter();
  printDoubleLinkList(pListA);

  skipSpace(&p);
  while (*p && *p != '\n') {
    Poly item;

    expectWhat(&p, '(');
    sscanf(p, "%f", &coff);

    advanceToWhat(&p, ',');
    expectWhat(&p, ',');
  
    sscanf(p, "%d", &exp);
    
    advanceToWhat(&p, ')');
    expectWhat(&p, ')');
    skipSpace(&p);

    item.exponent = exp;
    item.coefficient = coff;
    insertToDoubleLinkListTail(pListB, (void *)&item);
  }

  printf("\nPoly B: ");
  resetPrinter();
  printDoubleLinkList(pListB);
  sortDoubleLinkList(pListB);
  printf("\nAfter Sorted: ");
  resetPrinter();
  printDoubleLinkList(pListB);

  mergePoly(pListC, pListA, pListB);
  printf("\PolyC :");
  printDoubleLinkList(pListC);
  

 cleanup:
  destroyDoubleLinkList(&pListA);
  destroyDoubleLinkList(&pListB); 
  destroyDoubleLinkList(&pListC); 
  
  fclose(fp);

  return 0;
}
