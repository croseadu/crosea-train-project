#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <iostream>
#include <sstream>

using std::vector;
using std::string;
using std::map;
using std::set;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::cin;
using std::endl;


int main()
{
  vector<string> text;
  string filename;
  ifstream file;
  string line;
  string word;
  map<string, set<int> > word_line;
  int lineNumber;

  cout<<"The File you want to query:"<<std::endl;
  cin>>filename;
  file.open(filename.c_str());
  
  if (!file)
    {
      cout<<"Cannot Open File: "<<filename<<endl;
      return 0;
    }
  lineNumber = 0;
  while(getline(file, line))
    {
      istringstream ss(line);
      lineNumber++;

      text.push_back(line);
      while(ss>>word)
	{
	  map<string, set<int> >::iterator p = word_line.find(word);
	  if (p != word_line.end())
	    {
	      p->second.insert(lineNumber);
	    }
	  else
	    {
	      set<int> t;
	      t.insert(lineNumber);
	      word_line.insert(make_pair(word, t));
	    }
	}
    }

  cout<<endl<<"What Word you want count"<<endl;
  cin>>word;
  map<string, set<int> >::iterator p = word_line.find(word);
  if (p == word_line.end())
    {
      cout<<word<<" Doesn't Exist"<<endl;
    }
  else
    {
      set<int> s1 = p->second;
      for(set<int>::iterator pp = s1.begin(); pp != s1.end(); pp++)
	{
	  cout<<*pp<<": "<<text[*pp-1]<<endl;
	}
    }

  file.close();
  return 0;
}
