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


const int n = 9;
void count(int a[n], const int row);
void nonRecursiveCount(const int size);

int many;
int main()
{
  int a[n];


  many = 0;
  count(a, 0);
  //nonRecursiveCount(n);

  cout<<n<<" Queens Puzzle Possible Solution :"<<many<<endl;
  return 0;
}


bool valid(int aa[n], const int size)
{
  for (int i = 0; i < size-1; i++)
    for(int j = i+1; j < size; j++)
      {
	
	if (aa[i] == aa[j] 
	    || std::abs(aa[j] - aa[i]) == j-i)
	  return false;
      }
  return true;
}

bool curValid(int aa[n], const int curIndex)
{
  if (curIndex > 0)
    {
      int i;
      for (i = 0; i < curIndex; i++)
	if(aa[i] == aa[curIndex]
	   || std::abs(aa[i] - aa[curIndex]) == curIndex - i)
	  return false;
    }

  return true;

}

void count(int a[n], const int row)
{
  if (row >= n)
    {
      if (valid(a, n))
	many++;
      return;
    }

  for (int i = 0; i < n; i++)
    {
      a[row] = i;
       if (curValid(a, row))
	count(a, row+1);
    }
}


void nonRecursiveCount(const int size)
{

  int k = 0;
  int x[n];
  int i;

  for(i = 0; i < n; i++)
    {
      x[i] = 0;
    }

  
  while(k >= 0)
    {
    
      if (k >= n)
	{
	  if (valid(x, n))
	    many++;
	  k--;
	}
      else
	{

	  
	  while(++x[k] <= n)
	    {
	      if (curValid(x, k))
		break;
	    }
	  

	  if (x[k] <= n)
	    {
	      //x[k]++;
		k++;
	    }
	  else
	    {
	      x[k] = 0;
	      k--;
	    }

	}
    }

}
