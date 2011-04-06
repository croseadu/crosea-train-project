#include "../include/common.h"

#define MAXKEY 65535
#define MINKEY 0

#define K 5
#define MAX_NUM 4096
#define MAX_NAME_SIZE 50


void inputNext(int in[], int arrayNum, int array[K][MAX_NUM], int index[]);
void createLoserTree(int b[], int LoserTree[]);
void adjustLoserTree(int b[], int LoserTree[], int adjustIndex);


int main()
{
  char fileName[MAX_NAME_SIZE];
  int forMinKey;
  int b[K+1];
  int data[K][MAX_NUM];
  int indexArray[K];
  char buf[MAX_NUM];
  int index, curIndex;
  int LoserTree[K];
  int *result;
  FILE *fp;
  int i;

  for (i = 0; i < K; i++)
    {
      memset(fileName, 0, MAX_NAME_SIZE*sizeof(char));
      sprintf(fileName,"%d.txt", (i+1));
      fp = fopen (fileName, "r");
      if (NULL == fp)
	{
	  printf("Can't Open File %s\n", fileName);
	  exit(-1);
	}

      index = 0;
      while (fgets(buf, 4095, fp))
	{
	  curIndex = 0;

	  while (buf[curIndex] == '\t' || buf[curIndex] == ' ')
	    curIndex++;

	  while (sscanf(buf+curIndex, "%d", &data[i][index]))
	    {
	      index++;
	      while (isdigit(buf[curIndex]))
		curIndex++;
	      while (buf[curIndex] == '\t' || buf[curIndex] == ' ')
		curIndex++;
	      if (buf[curIndex] == '\n')
		break;
	    }
	  assert(index < 4096);

	}

      fclose(fp);
      data[i][index] = MAXKEY; 
    }

  printf("\nAll Buffer which need merged:\n");
  for (i = 0; i < K; i++)
    {
      index = 0;
      while (data[i][index] != MAXKEY)
	printf("%5d", data[i][index++]);
      putchar('\n');
    }

  printf("\bStart Merging:\n");
  result = (int *)malloc(sizeof(int)*K*MAX_NUM);

  for (i = 0; i < K; i++)
    {
      indexArray[i] = 0;
      inputNext(b, i, data, indexArray);
    }

  b[K] = MINKEY;
  createLoserTree(b, LoserTree);
  curIndex = 0;
  while (b[LoserTree[0]] != MAXKEY)
    {
      result[curIndex++] = b[LoserTree[0]];
      inputNext(b, LoserTree[0], data, indexArray);
      adjustLoserTree(b, LoserTree, LoserTree[0]);
    }
  result[curIndex++] = MAXKEY;
  printf("\bResult: ");
  i = 0;
  while (result[i] != MAXKEY)
    printf("%5d", result[i++]);
  
  putchar('\n');
  free(result);
  return 0;
}

void inputNext(int in[], int arrayNum, int array[K][MAX_NUM], int index[])
{
  in[arrayNum] = array[arrayNum][index[arrayNum]++];
}

void createLoserTree(int b[], int LoserTree[])
{
  int i;
  for (i = 0; i <= K; i++)
    LoserTree[i] = K;
  for (i = K-1; i >=0; i--)
    {
      adjustLoserTree(b, LoserTree, i);
      printf("\nL:%d %d %d %d %d %d", 
	     LoserTree[0],
	     LoserTree[1],
	     LoserTree[2],
	     LoserTree[3],
	     LoserTree[4],
	     LoserTree[5]);
      putchar('\n');
    }
}

void adjustLoserTree(int b[], int LoserTree[], int adjustIndex)
{
  int s, t, temp;

  s = adjustIndex;
  t = (s+K)/2;
  while (t > 0)
    {
      if (b[s] > b[LoserTree[t]])
	{
	  temp = s;
	  s = LoserTree[t];
	  LoserTree[t] = temp;
	}
      t = t/2;
    }
  LoserTree[0] = s;
}



