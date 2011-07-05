
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


int a[]={0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};

int main()
{
  int n = sizeof(a)/sizeof(a[0]);
  int i, j;

  vector<int> max(n, 0);
  vector<int> pre(n, -1);
      int maxSeq;
      int maxIndex;

  max[0] = 1;
  for (i = 1; i < n; i++)
    {
      maxSeq = 0;
      maxIndex = -1;
      for (j = 0; j < i; j++)
	if (max[j] > maxSeq && a[j] < a[i])
	  {
	    maxSeq = max[j];
	    maxIndex = j;
	  }
      max[i] = 1 + maxSeq;
      pre[i] = maxIndex;
    }

  cout<<endl;

  maxSeq = 0;
  i = 0;
  for(vector<int>::const_iterator p = max.begin(); p != max.end(); p++)
    {
      cout<<*p<<":";
      if (maxSeq < *p)
	{
	  maxSeq = *p;
	  maxIndex = i;
	}
      i++;
    }
  cout<<endl;
  cout<<a[maxIndex]<<":";
  while(pre[maxIndex] != -1)
    {
      maxIndex = pre[maxIndex];
      cout<<a[maxIndex]<<":";
    }
  cout<<endl;
  
  

  return 0;
}
