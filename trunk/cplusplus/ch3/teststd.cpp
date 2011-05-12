#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cin;
using std::cout;

int main()
{
  string inputString;
  vector<string> v_string(10, "hi");

  while(cin>>inputString)
    v_string.push_back(inputString);


  for(vector<string>::size_type i = 0; i < v_string.size(); i++)
    cout<<v_string[i]<<std::endl;

  return 0;
}
