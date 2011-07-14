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
  string first("kltten");
  string second("slttlng");
  vector< vector<int> > dist;
  int i,j;


  for(i = 0; i <= first.size(); i++)
    dist.push_back(vector<int>(second.size()+1, 0));

  for (i = 1; i <= first.size(); i++)
    for (j = 1; j <= second.size(); j++)
      {
	if (first[i-1] == second[j-1])
	  {
	    dist[i][j] = dist[i-1][j-1];
	  }
	else
	  {
	    int min = i+j;
	    if (dist[i][j-1] < min)
	      min = dist[i][j-1];
	    if (dist[i-1][j] < min)
	      min = dist[i-1][j];
	    if (dist[i-1][j-1] < min)
	      min = dist[i-1][j-1];
	    min++;
	    dist[i][j] = min;
	  }
      }
  cout<<endl<<"Min Step :"<<dist[first.size()][second.size()]<<endl;

  i = first.size();
  j = second.size();
  cout<<first<<endl<<second<<endl;
  while (dist[i][j])
    {
      if (first[i-1] == second[j-1])
	{
	  i--;
	  j--;
	}
      else
	{
	  if (dist[i][j] == dist[i][j-1] + 1)
	    cout<<"Insert :"<<second[j---1]<<endl;
	  else if (dist[i][j] == dist[i-1][j] + 1)
	    cout<<"Delete :"<<first[i---1]<<endl;
	  else if (dist[i][j] == dist[i-1][j-1] + 1)
	    {
	      cout<<"Change first "<<first[i-1]<<":"<<i<<" same as second "<<second[j-1]<<":"<<j<<endl;
	      i--;
	      j--;
	    }
	  else
	    cout<<"Impossible!!!!"<<endl;
	}

    }

  return 0;
}
