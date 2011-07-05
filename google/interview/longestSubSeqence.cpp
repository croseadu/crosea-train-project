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
  string first("agbhkcdiiabgkcodkef");
  string second("cbaabbccddeeffi");

  int i; // first.size();
  int j; // second.size();
  vector< vector<int> > result;
  
  cout<<"First Size:"<<first.size()<<" Second Size: "<<second.size()<<endl;
  for (i = 1; i <= first.size(); i++)
    {
      result.push_back(vector<int>(second.size(), 0));
      //cout<<"Result[][]"<<result[i-1][j-1];
      for (j = 1; j <= second.size(); j++)
	{
	  if (first[i-1] == second[j-1])
	    {
	      result[i-1][j-1] = 1 + ((i > 1 && j > 1)?result[i-2][j-2]:0);
	    }
	  else if (i > 1 && j > 1)
	    result[i-1][j-1] = (result[i-2][j-1] > result[i-1][j-2])
	      ?result[i-2][j-1]:result[i-1][j-2];
	  else if (i > 1)
	    result[i-1][j-1] = result[i-2][j-1];
	  else if (j > 1)
	    result[i-1][j-1] = result[i-1][j-2];
	  else
	    result[i-1][j-1] = 0;
	}
    }
  
  cout<<"Max Sub Seq :"<<result[first.size()-1][second.size()-1]<<endl;

  vector<char> seq;
  seq.push_back('\0');
  i = first.size()-1;
  j = second.size()-1;
  while(i >= 0 && j >= 0 && result[i][j])
    {  
      if (first[i] == second[j])
	{
	  seq.insert(seq.begin(),first[i]);
	  i--;
	  j--;
	}
      else if (i > 1 && j > 1)
	{
	  if (result[i-1][j] > result[i][j-1])
	    i--;
	  else
	    j--;
	}
      else if (i > 1)
	i--;
      else 
	j--;
    }


  cout<<endl;
  for (vector<char>::const_iterator p = seq.begin(); p!= seq.end(); p++)
    {
      cout<<*p;
    }
  cout<<endl;

  return 0;
}
