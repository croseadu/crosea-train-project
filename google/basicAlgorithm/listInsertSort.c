#include "../include/common.h"


typedef struct _NODE
{
  int value;
  int next;
}NODE, *LP_NODE;

#define INIT 20
#define INCRE 20

int main()
{
  FILE *fp;
  char buf[4096];
  int weight[4096];
  int index, curIndex;
  int numOfData;
  int maxElement;
  NODE *pHead;
  int i;
  int last;
  int p;

  if ((fp = fopen("input/listInsertSort.txt", "r")) == NULL)
    {
      printf ("Cannot Open File listInsertSort.txt\n");
      exit(-1);
    }

  numOfData = 0;
  pHead = (LP_NODE)malloc(sizeof(NODE)*INIT);
  if (NULL == pHead)
    {
      fclose(fp);
      exit(OVERFLOW);
    }
  maxElement = INIT-1;

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
      if (index > maxElement - numOfData)
	{
	  pHead = realloc(pHead, sizeof(int) * (maxElement + 1 + INCRE));
	  maxElement += INCRE;
	  if (pHead == NULL)
	    {
	      fclose(fp);
	      printf ("Out Of Memory in Line %d, File %s", __LINE__, __FILE__);
	      exit(OVERFLOW);
	    }
	}
      i = 0;
      while (i < index)
	{
	  (pHead + numOfData + 1)->value = weight[i];
	  i++;
	  numOfData++;
	}
    }

  i = 0;
  while (i <= numOfData)
    {
      (pHead + i)->next = i+1;
      i++;
    }
  (pHead + numOfData + 1)->next = 0;

  printf("\nInputData is :\n");
  for (i = 1; i <= numOfData; i++)
    {
      printf("%5d", (pHead + i)->value);
      if (i && i%10 == 0 )
	putchar('\n');
    }

  printf("\nStart ListInsert Sort");
  (pHead + 1)->next = 0;
  last = 1;
  for (i = 2; i <= numOfData; i++)
    {
      if ((pHead + i)->value >= (pHead+last)->value)
	{
	  (pHead+last)->next = i;
	  (pHead+i)->next = 0;
	  last = i;
	}
      else 
	{
	  int prev = 0;
	  while ((pHead + (pHead+prev)->next)->value <= (pHead+i)->value)
	    prev = (pHead+prev)->next;
	  (pHead+i)->next = (pHead+prev)->next;
	  (pHead+prev)->next = i;
	}
    }
  printf("\nResult:\n");
  printf("Header:[%d] ** ", pHead->next);
  for (i = 1; i <= numOfData; i++)
    {
      printf("a[%d]%d(%d)  ", i, (pHead + i)->value, (pHead+i)->next);
      if (i && i%10 == 0 )
	putchar('\n');
    }
  putchar('\n');
  printf ("rearrange:\n");

  p = pHead->next;
  i = 1;
  while (i < numOfData)
    {
      while (p < i)
	{
	  p = (pHead+p)->next;
	}
	    

	  if (p > i)
	    {
	      NODE tempNode;			
	      int temp;
	      tempNode = *(pHead+i);
	      *(pHead+i) = *(pHead+p);
	      *(pHead+p) = tempNode;
	      temp = (pHead+i)->next;
	      (pHead+i)->next = p;
	      p = temp;
	    }
	  else
	    p = (pHead+p)->next;
      i++;
    }

  for (i = 1; i <= numOfData; i++)
    {
      printf("%5d", (pHead + i)->value);
      if (i && i%10 == 0 )
	putchar('\n');
    }

  free(pHead);
  fclose(fp);
  return 0;
}
