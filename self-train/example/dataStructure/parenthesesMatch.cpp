#include <iostream>
#include "stack.h"


using namespace MyUtil;

inline bool isParentheses(const char t)
{
  if (t == '[' || t == '{' || t == '('
      || t == ']' || t == '}' || t == ')')
    return true;
 
  return false;
}

int main()
{
  Stack<char> myStack;
  char t;

  while (std::cin>>t)
    {
      if (!isParentheses(t))
        {
          std::cout<<"Not parentheses in Input"<<std::endl;
          return 0;
        }
      if (t == '}' || t == ']' || t == ')')
        {
          char top;
          if (myStack.empty())
            {
              top = '!';
            }
          else
            myStack.pop(top);
          if ((t == ']' && top != '[')
              || (t == '}' && top != '{')
              || (t == ')' && top != '('))
            {
              std::cout<<"Mismatch for :"<<t<<std::endl;
              return 0;
            }
        }
      else
        myStack.push(t);
    }

    if (!myStack.empty())
      {
        std::cout<<"MisMatch, Stack isn't empty"<<std::endl;
        return 0;
      }

    std::cout<<"Matched"<<std::endl;

  return 0;
}
