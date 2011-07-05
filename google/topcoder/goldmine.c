#include <stdio.h>


int mines [][7] ={ {100, 000, 000, 000, 000, 000, 000},
		   {100, 000, 000, 000, 000, 000, 000},
		   {100, 000, 000, 000, 000, 000, 000},
		   {100, 000, 000, 000, 000, 000, 000},
		   {100, 000, 000, 000, 000, 000, 000} };
/*
 { {00, 30, 30, 40, 0, 0, 0},
		    {20, 20, 20, 10, 10, 10, 10} };
*/
const int totalMiners = 8;
int maxProfit[5][8+1];

int mineProfit[5][7];

int main()
{
  
  int numOfMines = sizeof(mines)/(7*sizeof(int));
  int i, j, k;

  for (i = 0; i < numOfMines; i++)
    {
      int possibility = 0;
      for (j = 0; j < 7; j++)
	possibility += mines[i][j];
      if (possibility != 100)
	{
	  printf("Wrong Possiblity in Mine[%d]", i);
	  exit(-1);
	}

    }


  for (i = 0; i< numOfMines; i++)
    {
      for (j = 0; j < 7; j++)
	{
	  int profit = 0;
	  for (k = 0; k < 7; k++)
	    {
	      if (mines[i][k])
		{
		  if (j < k)
		    profit += j * 60 * mines[i][k];
		  else if (j == k)
		    profit += j * 50 * mines[i][k];
		  else
		    profit += (k * 50 - 20 * (j - k))*mines[i][k];
		 }
	    }
	  profit = profit/100;
	  mineProfit[i][j] = profit;
	  printf("\nMine %d, if miners %d profit = %d", i, j, profit);
	}
    }
  putchar('\n');
  
  for (i = 0; i < numOfMines; i++)
    {
      for (j = 1; j <= totalMiners && j <= 6*(i+1); j++)
	{
	  // maxProfit[i][t] = maxOf { maxProfit[i-1][t],
	  //                           maxProfit[i-1][t-1] + mineProfit[i][1],
	  //                           maxProfit[i-1][t-2] + mineProfit[i][2],
	  //                           maxProfit[i-1][t-3] + mineProfit[i][3], ...}
	  int profit = -21*j;
	  for (k = 0; k <=6 && k <= j; k++)
	    {
	      int temp = 0;
	      
	      if (j > k && i == 0)
		continue;
	      
	      if (j - k > 6*i)
		continue;

	      temp = mineProfit[i][k];
	      if (i != 0)
		temp += maxProfit[i-1][j-k];
	      if (temp > profit)
		profit = temp;
	    }
	  maxProfit[i][j] = profit;
	}
    }
  putchar('\n');
  printf("maxProfit[2][4] = %d\n", maxProfit[4][8]);
  return 0;
}

