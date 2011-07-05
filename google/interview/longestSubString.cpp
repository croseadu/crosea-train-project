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


int main()
{
  string first("abccddefghkaaibc");
  string second("cbabcfghdefghk");

  vector< vector<int> > length;

  int i, j;
  int max = 0, end = -1;
  cout<<"First :"<<first<<endl<<"Second :"<<second<<endl;
  for (i = 0; i < first.size(); i++)
    {
      length.push_back(vector<int>(second.size(), 0));
      for (j = 0; j < second.size(); j++)
	{
	  if (first[i] != second[j])
	    {
	      length[i][j] = 0;
	    }
	  else if (i == 0 || j == 0)
	    {
	      length[i][j] = 1;
	      if (1 > max)
		{
		  max = 1;
		  end = i;
		}
	    }
	  else
	    {
	      length[i][j] = 1 + length[i-1][j-1];
	      if (length[i][j] > max)
		{
		  max = length[i][j];
		  end = i;
		}
	    }
	}
    }

  cout<<endl<<"Max SubString, length :"<<max<<" is "<<string(first.begin()+end-max+1, first.begin()+end+1)<<endl;
  return 0;
}
