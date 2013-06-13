#include "stack.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

bool isBrace(const char p)
{
  if (p == '(' 
      ||p == '[' 
      ||p == '{' 
      ||p == ')' 
      ||p == ']' 
      ||p == '}')
    return true;
  return false;
}

bool isMatch(const char p1, const char p2)
{
  if (p1 == ')')
    return p2 == '(';
  if (p1 == '}')
    return p2 == '{';
  if (p1 == ']')
    return p2 == '[';
  return false;
}

int main()
{
  std::string input;

  getline(cin, input);
  
  const char *toCharString = input.c_str();
  const char *p = toCharString;
  Stack<char> *brace;
  initStack(&brace);

  bool matched = true;
  while (*p != 0){
    if (isBrace(*p))
      {
	if (*p == '(' || *p == '[' || *p == '{')
	  push(brace, *p);
	else
	  {
	    if (isEmpty(brace))
	      {
		matched = false;
		break;
	      }
	    char temp;
	    pop(brace, temp);
	    if (!isMatch(*p, temp))
	      {
		matched = false;
		break;
	      }
	  }
      }
    ++p;
  }
  if (!matched || !isEmpty(brace))
    cout<<endl<<"It doesn't Match"<<endl;
  else
    cout<<endl<<"It Matched!!!"<<endl;
  destroyStack(&brace);


}


