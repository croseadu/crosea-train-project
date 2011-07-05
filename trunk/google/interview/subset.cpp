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

int a[]={-7,-3,-2,5,8};
int main()
{
  vector<int> input;
  int min, max;
  int i;

  for (i = 0; i < 5; i++)
    input.push_back(a[i]);

  min = max = 0;

  for (vector<int>::const_iterator p = input.begin(); 
       p != input.end(); p++)
    {
      if (*p > 0)
	max += *p;
      else 
	min += *p;
    }
  
  cout<<"Max :"<<max<<"Min ::"<<min<<endl;

  vector< vector<bool> > isSum;
  vector< vector<bool> > needIt;
  isSum.push_back(vector<bool>(max-min+1, false));
  needIt.push_back(vector<bool>(max-min+1, false));

  for (int i = 0; i < input.size(); i++)
    {
      isSum.push_back(vector<bool>(max-min+1, false));
      needIt.push_back(vector<bool>(max-min+1, false));

      for(int j = min; j <= max; j++)
	{
	  if (isSum[i][j-min] == true)
	    {
	      isSum[i+1][j-min] = true;
	      needIt[i+1][j-min] = false;
	    }
	  else if (j == input[i])
	    {
	      isSum[i+1][j-min] = true;
	      needIt[i+1][j-min] = true;
	    }
	  else if (j - input[i] >= min 
		   && j - input[i] <= max
		   && isSum[i][j - input[i] - min] == true)
	    {
	      isSum[i+1][j-min] = true;
	      needIt[i+1][j-min] = true;
	    }
	}
    }

  for (i = 0; i < isSum[5].size();i++)
    {
      cout<<"["<<min+i<<" :"<<isSum[5][i]<<" ] ";
    }
  int sum = 8;
  cout<<endl<<sum<<" = ";
  for (i = 5; i > 0; i--)
    {
      if (needIt[i][sum-min])
	{
	  sum -= input[i-1];
	  cout<<input[i-1]<<"+";
	}
    }
  cout<<endl;
 

  return 0;
}
