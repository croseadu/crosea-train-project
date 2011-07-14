#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;
using std::istringstream;
using std::pair;
using std::make_pair;

/*
  {1, 0}
  {0, 1}
or
  {0, 1}
  {1, 0}

*/
void count(int i, int j, int n);
long long many = 0;
long long much = 0;
  const int n = 6;
  const int h = 3;
  int a[n][n];

bool validMatrix(int a[n][n]);
void nonRecursiveCount(const int size);
int row[n];
int column[n];

int main()
{
 
  int i;
  for (i = 0; i < n; i++)
    row[i] = column[i] = 0;

  a[0][0] = 0;
  count(0, 0, n);

  a[0][0] = 1;
  row[0]++;
  column[0]++;
  count(0, 0, n);
  cout<<"Many :"<<many<<endl;

  for (i = 0; i < n; i++)
    row[i] = column[i] = 0;

  nonRecursiveCount(n);
  cout<<" Much : "<<much<<endl;
  return 0;
}

bool validMatrix(int a[n][n])
{
  int i = 0,j = 0;

  for(i = 0; i < n; i++)
    {
      int t= 0;
      for(j = 0; j < n; j++)
	t+=a[i][j];
      if (t != h)
	return false;
    }

  for(i = 0; i < n; i++)
    {
      int t= 0;
      for(j = 0; j < n; j++)
	t+=a[j][i];
      if (t != h)
	return false;
    }
  return true;
}

bool valid(int i, int j, int value)
{
      int t = 0;
      for(int k = 0; k <=j; k++)
	if (a[i][k] == value)
	  t++;
      if (t > h)
	return false;

      t = 0;
      for(int k = 0; k <=i; k++)
	if (a[k][j] == value)
	  t++;
      if (t > h)
	return false;

      return true;

}

inline void NEXT(int &i, int &j)
{
  if (j < n-1)
    j++;
  else
    {
      i++;
      j = 0;
    }
}

inline void PREV(int &i, int &j)
{
  if (j > 0)
    j--;
  else
    {
      i--;
      j = n-1;
    }
}


void count(int i, int j, int n)
{
  if (i == n-1 && j == n-1)
    {
      if ( validMatrix(a))
	many++;
      return;
    }
  
  NEXT(i, j);

  a[i][j] = 0;
  if(i+1-column[j] <= h && j+1-row[i] <= h)
    count(i, j, n);

  a[i][j] = 1;
  row[i]++;
  column[j]++;
  if (row[i] <= h && column[j] <= h)
    count(i, j, n);
  row[i]--;
  column[j]--;
}


void nonRecursiveCount(const int size)
{

  int i, j;
  i = 0; j = 0;

  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++)
      a[i][j] = -1;

  i = 0; j = 0;
  while(i >= 0)
    {
      if (i == n-1 && j == n-1)
	{
	  a[i][j] = 0;
	  if (validMatrix(a))
	    much++;
	  a[i][j] = 1;
	  if (validMatrix(a))
	    much++;
	  j--;
	}
      else
	{
	  a[i][j]++;
	  
	  if (a[i][j] < 2)
	    {
	      if (a[i][j] == 0)
		{
		  if (i+1-column[j] <= h && j+1-row[i] <= h)
		    NEXT(i, j);
		}
	      else
		{
		  row[i]++;
		  column[j]++;
		  if (row[i] <= h && column[j] <= h)
		    {
		      NEXT(i, j);
		    }
		}
	    }
	  else
	    {
	      a[i][j] = -1;
	      row[i]--;
	      column[j]--;
	      PREV(i, j);
	    }

	}
    }
}
