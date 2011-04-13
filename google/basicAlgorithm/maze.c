
#include "../include/stack.h"
#include "../include/listQueue.h"

#define START(i, j) (i == 1 && j == 1)
#define END(i, j) (i == 8 && j== 8) 

enum DIRECT_TO_NEXT
{
  U = 0,
  E = 1,
  D = 2,
  W = 3,
};

typedef struct
{
  int i;
  int j;
  enum DIRECT_TO_NEXT next;
  int di;
}TRACE, *LP_TRACE;

typedef struct
{
  int i;
  int j;
}POS;

POS nextPos(int i, int j, enum DIRECT_TO_NEXT next)
{
  POS temp;
  if (next == U)
    {
      temp.i = i - 1;
      temp.j = j;
    }
  else if (next == E)
    {
      temp.i = i;
      temp.j = j+1;
    }
  else if (next == D)
    {
      temp.i=i+1;
      temp.j = j;
    }
  else if (next == W)
    {
      temp.i = i;
      temp.j = j - 1;
    }
  else
    assert(0);
  return temp;
}

#define M 10

int map[M][M] = 
{
  {1,1,1,1,1,1,1,1,1,1},
  {1,0,0,1,0,0,0,1,0,1},
  {1,0,0,1,0,0,0,1,0,1},
  {1,0,0,0,0,1,1,0,0,1},
  {1,0,1,1,1,0,0,0,0,1},
  {1,0,0,0,1,0,0,0,0,1},
  {1,0,1,0,0,0,1,0,0,1},
  {1,0,1,1,1,0,1,1,0,1},
  {1,1,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1}
};
int *footPrint;
int *cannotPass;
POS *prevNode;
int *flag;
BOOL findOnePass(LP_STACK pStack);
int main()
{

  LP_STACK pStack;
  LP_LIST_QUEUE pQueue;
  BOOL bFound;
  int i, j;

  footPrint = (int *)malloc(M*M*sizeof(int));
  cannotPass = (int *)malloc(M*M*sizeof(int));

  if (NULL == footPrint
      || NULL == cannotPass)
    {
      printf("Out Of Memory in Line %d, File %s", __LINE__, __FILE__);
      exit(OVERFLOW);
    }
  createStack(&pStack, sizeof(TRACE));
  bFound = findOnePass(pStack);
  if (bFound == FALSE)
    {
      printf("No Pass Exist\n");
    }
  else
    {
      char *pDumpBuffer;
      pDumpBuffer = (char *)malloc(M*M*sizeof(char));
      if (NULL == pDumpBuffer)
	{
	  printf("Out Of Memory In LIne %d, FUnction %s", __LINE__, __FILE__);
	  exit(OVERFLOW);
	}
      for (i = 0; i < M; i++)
	for (j = 0; j < M; j++)
	  {
	    if (START(i, j))
	      *(pDumpBuffer + i * M + j) = 'S';
	    else if (END(i, j))
	      *(pDumpBuffer + i * M + j) = 'E';
	    else if (map[i][j])
      	      *(pDumpBuffer + i * M + j) = '#';
	    else 
	      *(pDumpBuffer + i * M + j) = ' ';
	  }

      while (!isStackEmpty(pStack))
	{
	  TRACE tempTrace;
	  pop (pStack, &tempTrace);
	  i = tempTrace.i;
	  j = tempTrace.j;
	  if (!START(i, j) && !END(i, j))
	    *(pDumpBuffer + i * M + j) = '.';
	}

      printf("\bPath:\n");
      for (i = 0; i < M; i++)
	{
	  for (j = 0; j < M; j++)
	    {
	      putchar('[');
	      putchar((*(pDumpBuffer + i * M + j)));
	      putchar(']');
	    }
	  putchar('\n');
	}
    }
  destroyStack(pStack);
  free (footPrint);
  free (cannotPass);

  /*******************************/
  printf("\nFind Shortest path, Width Traverse");
#define LINK(i, j, i1, j1) ((i1 <= i+1 && i1 >= i-1) && (j1 <= j+1 && j1 >= j-1))
  prevNode = (POS *)malloc(M*M*sizeof(POS));
  flag = (int *)malloc(M*M*sizeof(int));

  if (NULL == prevNode
      || NULL == flag)
    {
      printf("Out Of Memory in Line %d, File %s", __LINE__, __FILE__);
      exit(OVERFLOW);
    }  
  memset(prevNode, 0, sizeof(POS)*M*M);
  memset(flag, 0, sizeof(int)*M*M);
  {
    POS tempPos;
    int k;
    createListQueue(&pQueue, sizeof(POS));

    tempPos.i = 1; 
    tempPos.j = 1;
    *(flag + i*M + j) = 1;
    insertToQueueTail(pQueue, &tempPos);
    while (!isQueueEmpty(pQueue))
      {
	    int m,n;
	    POS prev;

	getFromQueueHead(pQueue, &tempPos);
	if (END(tempPos.i, tempPos.j))
	  break;
	
	    m = tempPos.i;
	    n = tempPos.j;
	    prev.i = m;
	    prev.j = n;

	for (k = 0; k < 4; k++)
	  {
	    tempPos = nextPos(m,n,k);

	    if (!map[tempPos.i][tempPos.j] &&
		!(*(flag + tempPos.i * M + tempPos.j)))
	      {
		*(prevNode + tempPos.i*M + tempPos.j) = prev;
		*(flag + tempPos.i * M + tempPos.j) = 1;
		insertToQueueTail(pQueue, &tempPos);
	      }
	  }
      }
    assert(END(tempPos.i, tempPos.j));

    {
      char *pDumpBuffer;
      pDumpBuffer = (char *)malloc(M*M*sizeof(char));
      if (NULL == pDumpBuffer)
	{
	  printf("Out Of Memory In LIne %d, FUnction %s", __LINE__, __FILE__);
	  exit(OVERFLOW);
	}
      for (i = 0; i < M; i++)
	for (j = 0; j < M; j++)
	  {
	    if (START(i, j))
	      *(pDumpBuffer + i * M + j) = 'S';
	    else if (END(i, j))
	      *(pDumpBuffer + i * M + j) = 'E';
	    else if (map[i][j])
      	      *(pDumpBuffer + i * M + j) = '#';
	    else 
	      *(pDumpBuffer + i * M + j) = ' ';
	  }
  
      do
	{
	  tempPos = *(prevNode + tempPos.i * M + tempPos.j);
	  i = tempPos.i;
	  j = tempPos.j;
	  *(pDumpBuffer + i * M + j) = '.';
	} while (!START(tempPos.i, tempPos.j));

      printf("\bPath2:\n");
      for (i = 0; i < M; i++)
	{
	  for (j = 0; j < M; j++)
	    {
	      putchar('[');
	      putchar((*(pDumpBuffer + i * M + j)));
	      putchar(']');
	    }
	  putchar('\n');
	}

    }

    

  }
  free (prevNode);
  free (flag);
  /******************************/
  return 0;
}


BOOL findOnePass(LP_STACK pStack)
{
  TRACE tempTrace;
  POS tempPos;
  int i, j;

  memset(cannotPass, 0, sizeof(int)*M*M);
  memset(footPrint, 0, sizeof(int)*M*M);

  for (i = 0; i < M; i++)
    for (j = 0; j < M; j++)
      if (map[i][j])
	*(cannotPass + i*M + j) = 1;

  tempTrace.i = 1;
  tempTrace.j = 1;
  tempTrace.di = 1;
  tempTrace.next = U;
  tempPos = nextPos(1,1, U);
  push (pStack, &tempTrace);
  *(footPrint + 1 * M + 1) = 1;
  
  while (!isStackEmpty(pStack))
    {
      i = tempPos.i;
      j = tempPos.j;
      if (END(i,j))
	return TRUE;
      else if (!(*(cannotPass + i*M + j) 
	    || *(footPrint + i*M + j)))
	{
	  tempTrace.i = i;
	  tempTrace.j = j;
	  tempTrace.di = 1;
	  tempTrace.next = U;
	  *(footPrint + i*M + j) = 1;
	  tempPos = nextPos(i,j, U);
	  push (pStack, &tempTrace);
	  //printf("\nPut %d %d to Stack", i, j);
	}
      else
	{
	  pop (pStack, &tempTrace);
	  //printf ("\nerase %d %d from Stack", tempTrace.i, tempTrace.j);
	  while (tempTrace.di >=4 && !isStackEmpty(pStack))
	    {
	      pop(pStack, &tempTrace);
	      //printf ("\nerase %d %d from Stack", tempTrace.i, tempTrace.j);
	    }
	  if (tempTrace.di >=4)
	    return FALSE;
	  tempTrace.di++;
	  tempTrace.next = (tempTrace.next)+1;
	  tempPos = nextPos(tempTrace.i, tempTrace.j, tempTrace.next);
	  push (pStack, &tempTrace);
	  //printf("\nPut %d %d to Stack", tempTrace.i, tempTrace.j);
	}
    }
  return FALSE;
}
