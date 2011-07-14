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
  // A 50 x 20, B 20 x 1, C 1 x 10, D 10 x 100.
  // min Cost 7000;
  
  int a[4][2]={{50,20}, {20, 1}, {1, 10}, {10, 100}};

  vector< vector<int> > cost;

  int i, j;
  for (i = 0; i < 4; i++)
    cost.push_back(vector<int>(4, 0));

  for (int s = 1; s < 4; s++)
    for (i = 0; i < 4-s; i++)
      {
	int min = 0xFFFFFFF;
	for(j = i; j < i+s; j++)
	  {
	    int temp;
	    temp = cost[i][j] + cost[j+1][i+s] + a[i][0]*a[j+1][0]*a[i+s][1];
	    if (min > temp)
	      min =temp;
	  }
	cost[i][j] = min;
      }
  
  
  
  
  cout<<"Cost : "<< cost[0][3]<<endl;
  return 0;
}
