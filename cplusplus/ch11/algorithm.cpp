#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include <iterator>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

int main()
{
  vector<int> vec_i(9,20);
  vector<string> vec_s(30, "_TAT_");
  
  string output;
  output = accumulate(vec_s.begin(),vec_s.end(), string("start_"));
  output += "_end";

  int acc;
  acc = accumulate(vec_i.begin(),vec_i.end(),0);
  cout<<output<<endl<<acc<<endl;
  
  fill(vec_i.begin(), vec_i.begin()+vec_i.size()/2,100);
  for(vector<int>::const_iterator p = vec_i.begin(); p != vec_i.end();p++)
    cout<<*p<<" ";

  vector<int> vec_2;
  fill_n(back_inserter(vec_2), 10, 5);
  //cout<<vec_2;
  copy(vec_i.begin(),vec_i.end(), back_inserter(vec_2));
  replace(vec_2.begin(),vec_2.end(), 5,15);
  cout<<endl;
  for(vector<int>::const_iterator p = vec_2.begin(); p != vec_2.end();p++)
    cout<<*p<<" ";
  cout<<endl;
  cout<<"After erase duplicate element"<<endl;
  sort(vec_2.begin(), vec_2.end());
  vector<int>::iterator end_unique = unique(vec_2.begin(), vec_2.end());
  vec_2.erase(end_unique, vec_2.end());
  for(vector<int>::const_iterator p = vec_2.begin(); p != vec_2.end();p++)
    cout<<*p<<" ";
  cout<<endl;
  return 0;
}
