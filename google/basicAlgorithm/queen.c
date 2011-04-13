#include "../include/common.h"
BOOL valid(int ppos[][8]);
void trial(int ppos[][8], int queens);
void output(int ppos[][8]);

int main()
{
  int pos[8][8];

  memset(pos, 0, sizeof(pos));
  

  trial(pos, 0);
}
void trial(int ppos[][8], int queens)
{
  if (queens >= 8)
    {
      output(ppos);
    }
  else
    {
      int i;
      for (i = 0; i < 8; i++)
	{
	  ppos[queens][i] = 1;
	  if (valid(ppos))
	    trial(ppos, queens+1);
	  ppos[queens][i] = 0;
	}

    }
}
void output(int ppos[][8])
{
  int i, j;

  printf("\nValid:\n");
  for (i = 0; i < 8; i++)
    {
      for (j = 0; j < 8; j++)
	{
	  char c = ppos[i][j] + '0';
	  putchar(c);
	}
      putchar('\n');
    }

}

BOOL valid(int ppos[][8])
{
  int i, temp;

  for (i = 0; i < 8; i++)
    {
      temp = 0;
      temp = ppos[0][i] + ppos[1][i]+ ppos[2][i]+ ppos[3][i]+ 
	ppos[4][i]+ ppos[5][i]+ ppos[6][i]+ ppos[7][i];
      if (temp >=2)
	return FALSE;
    }

  temp = 0;
  temp = ppos[0][0] + ppos[1][1] + ppos[2][2]+ ppos[3][3]
    + ppos[4][4]+ ppos[5][5]+ ppos[6][6]+ ppos[7][7];
  if (temp >= 2)
    return FALSE;
  
  temp = 0;
  temp = ppos[7][0] + ppos[6][1] + ppos[5][2] + ppos[4][3] + 
    ppos[3][4] + ppos[2][5] + ppos[1][6] + ppos[0][7];
  if (temp >= 2)
    return FALSE;
  return TRUE;

}
