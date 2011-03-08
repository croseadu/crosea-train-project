
#include "../include/common.h"
#include "../include/stack.h"
#include "../include/circularQueue.h"
#include "../include/singleList.h"

typedef struct _NODE
{
  char *pData;
  BOOL bVisited;
}NODE, LP_NODE;

#define MAX_WEIGHT 65535

int main()
{

  char buf[4096];
  unsigned int weight[2048];
  FILE *fp;
  int index, curIndex;
  int line, column;
  int *pAdjWeight = NULL;
  int i,j;

  
  if ((fp = fopen("inputData.txt", "r")) == NULL)
    {
      printf ("Cannot Open File inputData.txt\n");
      exit(-1);
    }

  line = 0;
  column = -1;
  while (fgets(buf, 4095, fp))
    {
      index = 0;
      curIndex = 0;

      while (buf[curIndex] == '\t' || buf[curIndex] == ' ')
	curIndex++;

      while (sscanf(buf+curIndex, "%d", &weight[index]))
	{
	  index++;
	  while (isdigit(buf[curIndex]))
	    curIndex++;
	  while (buf[curIndex] == '\t' || buf[curIndex] == ' ')
	    curIndex++;
	  if (buf[curIndex] == '\n')
	    break;
	}
      if (column != -1 && column != index)
	break;

      column = index;
      if (NULL == pAdjWeight)
	{
	  pAdjWeight = (int *)malloc(sizeof(int)*column*column);
	  if (NULL == pAdjWeight)
	    {
	      printf("Out Of Memory in Line %d, File %s", __LINE__, __FILE__);
	      exit(OVERFLOW);
	    }
	}
      for (index = 0; index < column; index++)
	{
	  *(pAdjWeight + line * column + index) = weight[index];
	}
      line++;
    }


  if (line != column)
    {
      printf("Edge Data Error\n");
      free(pAdjWeight);
      exit(-1);
    }

  printf("\nInput Graph:\n");
  for (i = 0; i < line; i++)
    {
      printf("[Node V[%d]]:", i);
      for (j = 0; j < column; j++)
	{
	  if (i != j && *(pAdjWeight + i * column + j) != MAX_WEIGHT)
	    printf("(V[%d], V[%d], %d)", i,j,*(pAdjWeight + i * column + j));
	}
      
       putchar('\n');
    }






  return 0;
}
