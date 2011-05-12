#include <vector>
#include <string>
#include <map>
#include <set>

using std::vector;
using std::string;
using std::map;
using std::set;




int main()
{
  vector<string> text;
  string filename;
  ifstream file;
  string line;
  string word;
  map<string, set> word_line;

  cout<<"The File you want to query:"<<std::endl;
  cin>>filename;
  file.open(filename);
  
  while(getline(file, line))
    {
      istringstream s(line);

      text.push_back(line);
      while(s>>word)
	{

	}
    }


  file.close();
  return 0;
}
