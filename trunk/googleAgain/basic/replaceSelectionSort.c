#include "../include/mytype.h"
#include <stdio.h>
#include <stdlib.h>


const static int w = 6;

typedef struct _Rec
{
  int key;
  int rc;
}Rec;

#define MAX_KEY 0x7FFFFFFF
void adjustLoserTree(int *loserTree, Rec *workArea, int idx);
void createLoserTree(int *loserTree, Rec *workArea, FILE *fp);
void outputOneSection(int *loserTree, Rec *workArea, FILE *fp, int *pRc, int *pRMax);
int main()
{
  int loserTree[w];
  Rec workArea[w];
  int rc, rmax;
  FILE *fp;

  rc = rmax = 1;

  if ((fp = fopen("sort.txt", "r")) == NULL) {
    printf("Can't Open Input file\n");
    exit(-1);
  }
  
  createLoserTree(loserTree, workArea, fp);

  while (rc != rmax+1) {
    outputOneSection(loserTree, workArea, fp, &rc, &rmax);
    ++rc;
  }

  return 0;
}

void adjustLoserTree(int *loserTree, Rec *workArea, int idx)
{
  int s = idx;
  int t = (s+w)/2;
  int temp;

  while (t > 0) {
    if (workArea[loserTree[t]].rc < workArea[s].rc 
	|| workArea[loserTree[t]].rc == workArea[s].rc 
	&& workArea[loserTree[t]].key < workArea[s].key) {
      temp = s;
      s = loserTree[t];
      loserTree[t] = temp;
    }
    t = t/2;
  }
  loserTree[0] = s;
}

void createLoserTree(int *loserTree, Rec *workArea, FILE *fp)
{
  int i;
  int data;

  for (i = 0; i < w; ++i) {
    workArea[i].key = 0;
    workArea[i].rc = 0;
    loserTree[i] = 0;
  }
  for (i = w-1; i >= 0; --i) {
    fscanf(fp, "%d", &data);
    workArea[i].key = data;
    workArea[i].rc = 1;
    adjustLoserTree(loserTree, workArea, i);
  }


}

void outputOneSection(int *lt, Rec *workArea, FILE *fp, int *pRc, int *pRmax)
{
  int miniMax;
  int data;

  printf ("\nSection %3d: ", *pRc);
  while (workArea[lt[0]].rc == *pRc) {
    printf("%5d", workArea[lt[0]].key);
    miniMax = workArea[lt[0]].key;

    if (feof(fp) || fscanf(fp, "%d", &data) < 1) {
      workArea[lt[0]].rc = *pRmax+1;
      workArea[lt[0]].key = MAX_KEY;
    }
    else {
      if (data < miniMax) {
	workArea[lt[0]].rc = *pRc+1;
	*pRmax = *pRc+1;
	workArea[lt[0]].key = data;
      }
      else {
	workArea[lt[0]].rc = *pRc;
	workArea[lt[0]].key = data;
      }
    }
    adjustLoserTree(lt, workArea, lt[0]);
  }

  putchar('\n');
}
