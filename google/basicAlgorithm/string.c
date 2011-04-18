#include "../include/common.h"

void calcNext(int *next,const char *sub, int length)
{
  int i,j;

  next[1] = 0;
  for (i = 1, j = next[1]; i < length;)
    {
      if (j == 0 || sub[i] == sub[j])
	{
	  
	  i++;
	  j++;
	  if (sub[i] == sub[j])
	    next[i] = next[j];
	  else
	    next[i] = j;
	}
      else
	j = next[j];
    }
  printf("\nKMP Next:");
  for (i = 1; i <= length;i++)
    {
      printf("%3d", next[i]);
    }
  putchar('\n');
}

int main()
{
  const char * string = " abdabcdaebababfccaddbae";
  const char * sub = " ababcababcd";
  int i, j;
  int mainLength = strlen(string)-1;
  int subLength = strlen(sub)-1;
  int *next;

  i = 1; j = 1;
  while (i <= mainLength && j <= subLength)
    {
      if (string[i] == sub[j])
	{
	  i++;
	  j++;
	}
      else
	{
	  i = i - (j-1) + 1;
	  j= 1;
	}
    }
  if (j > subLength)
    {
      printf("\nFound Sub, in string+%d\n", i-j+1);
    }
  else
    {
      printf("\nFailed\n");
    }

  // Use KMP
  next = (int *)malloc(sizeof(int) * (subLength+1));
  if (NULL == next)
    {
      printf("Out Of Memory when allocate Next in Line %d, File %s", __LINE__, __FILE__);
      exit(OVERFLOW);
    }

  calcNext(next, sub, subLength);

  i = 1; j = 1;
  while (i <= mainLength && j <= subLength)
    {
      if (j == 0 || string[i] == sub[j])
	{
	  i++; j++;
	}
      else
	{
	  j = next[j];
	}
    }

    if (j > subLength)
    {
      printf("\nKMP Found Sub, in string+%d\n", i-j+1);
    }
  else
    {
      printf("\nKMP Failed\n");
    }

  free(next);
}
