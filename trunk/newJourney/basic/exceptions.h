#ifndef _MY_EXCEPTIONS_H
#define _MY_EXCEPTIONS_H
#include <iostream>
#include <string>
using std::string;
using std::ostream;

class MyException
{
  string failMsg;
public:
  explicit MyException(const char *msg):failMsg(msg){}
  explicit MyException(const string &msg):failMsg(msg){}
  void print(ostream &out) const
  {
    out<<failMsg<<std::endl;
  }
};

ostream & operator<<(ostream &out, const MyException &e)
{
  e.print(out);
  return out;
}
#endif
