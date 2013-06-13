#include "stack.h"
#include <vector>
#include <ctype.h>
#include <iostream>
#include <string>
#include <assert.h>
#include "exceptions.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

class AddSubOperator;
class MulDivOperator;
class BraceOperator;
class BoundaryOperator;

class Operator
{
public:
  static const int Pred[7][7];
  enum Kind
  {
    ADD = 0,
    SUB,
    MUL,
    DIV,
    L_BRACE,
    R_BRACE,
    SHARP
  };
  Kind kind;

public:
  virtual int doCalc(const vector<int> &v) const = 0;
  virtual int Compare(const Operator *rhs, bool isOrder = true) const = 0;
  virtual int Compare(const AddSubOperator *rhs ,bool isOrder = false) const = 0;
  virtual int Compare(const MulDivOperator *rhs, bool isOrder = false)const = 0;
  virtual int Compare(const BraceOperator *rhs, bool isOrder = false) const= 0;
  virtual int Compare(const BoundaryOperator *rhs, bool isOrder = false) const = 0;
};

class BraceOperator:public Operator
{
  bool isStart;
public:
  bool isLeftBrace() const
  {
    return isStart;
  }
  explicit BraceOperator(const char op)
  {
    if (op == '(')
      isStart = true;
    else if (op == ')')
      isStart = false;
    else
      cout<<"Shoud not Hit here, invalid op for brace"<<endl;
    kind = op == '('?Operator::L_BRACE:Operator::R_BRACE;
  }
  int doCalc(const vector<int> &v) const
  {
    cout<<"Should not Hit here, no Calc for Brace"<<endl;
    return -1;
  }
  virtual int Compare(const Operator *rhs, bool isOrder = true) const
  {
    return rhs->Compare(this);
  }
  virtual int Compare(const AddSubOperator *rhs, bool isOrder = false) const
  {
    if (isStart)
      return -1;
    else
      return 1;
  }
  virtual int Compare(const MulDivOperator *rhs, bool isOrder = false) const
  {
    if (isStart)
      return -1;
    else
      return 1;
  }
  virtual int Compare(const BraceOperator *rhs, bool isOrder = false) const
  {
    if (!isStart && rhs->isStart)
      return 0;
    if (rhs->isStart && isStart == rhs->isStart)
      return -1;
    else
      return 0xFF;
  }
  virtual int Compare(const BoundaryOperator *rhs, bool isOrder = false) const
  {
    return -1;
  }
};


 
class Operation
{
public:
  virtual int operator()(int lhs, int rhs) const = 0;
};

const int Operator::Pred[7][7] =
    { {1,1,-1,-1,-1,1,1},
      {1,1,-1,-1,-1,1,1},
      {1,1,1,1,-1,1,1},
      {1,1,1,1,-1,1,1},
      {-1,-1,-1,-1,-1,0,1},
      {1,1,1,1,0xFF,1,1},
      {-1,-1,-1,-1,-1,0xFF,0},
    };

class AddOp:public Operation
{
public: 
virtual int operator()(int lhs, int rhs) const
  {
    return lhs+rhs;
  }
};
class SubOp:public Operation
{
public: 
virtual int operator()(int lhs, int rhs) const
  {
    return lhs-rhs;
  }
};
class MulOp:public Operation
{
public :
virtual int operator()(int lhs, int rhs) const
  {
    return lhs*rhs;
  }
};
class DivOp:public Operation
{
public :
virtual int operator()(int lhs, int rhs) const
  {
    return lhs/rhs;
  }
};

class AddSubOperator:public Operator
{
  Operation *Action;
public:
  explicit AddSubOperator(const char op)
  {
    if (op == '+')
      Action = new AddOp();
    else if (op == '-')
      Action = new SubOp();
    kind = op == '+'?Operator::ADD:Operator::SUB;
  }

 virtual int doCalc(const vector<int> &v) const
  {
    assert(v.size()==2);
    return (*Action)(v[0],v[1]);
  }

  ~AddSubOperator()
  {
    delete Action;
  }

  virtual int Compare(const Operator *rhs, bool isOrder = true) const
  {
    //cout<<"ADDSUB1";
    return rhs->Compare(this);
  }
  virtual int Compare(const AddSubOperator *rhs, bool isOrder = false) const
  {
    return 1;
  }
  virtual int Compare(const MulDivOperator *rhs, bool isOrder = false) const
  {
    return 1;
  }
  virtual int Compare(const BraceOperator *rhs, bool isOrder = false) const
  {
    if (rhs->isLeftBrace())
      return -1;
    else
      return 0xFF;
  }
  virtual int Compare(const BoundaryOperator *rhs, bool isOrder = false) const
  {
    return -1;
  }

};

class MulDivOperator:public Operator
{
  Operation *Action;
public:
  explicit MulDivOperator(const char op)
  {
    if (op == '*')
      Action = new MulOp();
    else if (op == '/')
      Action = new DivOp();
    kind = op == '*'?Operator::MUL:Operator::DIV;
  }
  int doCalc(const vector<int> &v) const
  {
    assert(v.size()==2);
    return (*Action)(v[0],v[1]);
  }
  ~MulDivOperator()
  {
    delete Action;
  }
  virtual int Compare(const Operator *rhs, bool isOrder = true) const
  {
    return rhs->Compare(this);
  }
  virtual int Compare(const AddSubOperator *rhs, bool isOrder = false) const
  {
    return -1;
  }
  virtual int Compare(const MulDivOperator *rhs, bool isOrder = false) const
  {
    return 1;
  }
  virtual int Compare(const BraceOperator *rhs, bool isOrder = false) const
  {
    if (rhs->isLeftBrace())
      return -1;
    else
      return 0xFF;
  }
  virtual int Compare(const BoundaryOperator *rhs, bool isOrder = false) const
  {
    return -1;
  }
};


class BoundaryOperator:public Operator
{
public:
  explicit BoundaryOperator(const char op)
  {
    kind = Operator::SHARP;
    assert(op == '#');
  }
  int doCalc(const vector<int> &v) const
  {
    cout<<"Should not Hit here, no Calc for Boundary"<<endl;
    return -1;
  }
  virtual int Compare(const Operator *rhs, bool isOrder = true) const
  {
    return rhs->Compare(this,false);
  }
  virtual int Compare(const AddSubOperator *rhs, bool isOrder = false) const
  {
    return 1;
  }
  virtual int Compare(const MulDivOperator *rhs, bool isOrder = false) const
  {
      return 1;
  }
  virtual int Compare(const BraceOperator *rhs, bool isOrder = false) const
  {
     return 1;
  }
  virtual int Compare(const BoundaryOperator *rhs, bool isOrder = false) const
  {
    return 0;
  }
};


Operator * create(const char op)
{
  if (op == '+' || op == '-')
    return new AddSubOperator(op);
  if (op == '*' || op == '/')
    return new MulDivOperator(op);
  if (op == '(' || op == ')')
    return new BraceOperator(op);
  if (op == '#')
    return new BoundaryOperator(op);
  return 0;
}

class Token
{
public:  
  Operator * pOperator;
  int number;
public:
  Token():pOperator(0), number(0){}
  explicit Token(unsigned int n):pOperator(0),number(n){}
  explicit Token(const char op):pOperator(create(op)),number(0){}
  bool isOperand() const { return pOperator == 0; }
};

void getNextToken(const char * &p, Token &t)
{
  if (isdigit(*p))
    {
      unsigned int number = *p - '0';
      ++p;
      while(isdigit(*p))
	{
	  number *= 10;
	  number += *p - '0';
	  ++p;
	}
      t = Token(number);
      cout<<"Next Token: "<<number;
    }
  else
    {
      t = Token(*p);
      cout<<"Next Token op:"<<*p;
      ++p;
    }
  
}

int main()
{
  string input;
  Stack<int> *pOperand;
  Stack<Operator *> *pOperator;
  
  getline(cin, input);
  if (input.size() == 0)
    return 0;

  initStack(&pOperand);
  initStack(&pOperator);

  input.append("#");
  const char *p = input.c_str();
  Token curToken;
  getNextToken(p, curToken);
  Operator *topOp;
  //cout<<input<<endl;
  push(pOperator, create('#'));

  try{
  while (!(!curToken.isOperand() 
	  && dynamic_cast<BoundaryOperator *>(curToken.pOperator))
	 || !dynamic_cast<BoundaryOperator *>(topOp = top(pOperator)))
    {
      if (curToken.isOperand())
	{
	  cout<<"Push Operand "<<curToken.number<<endl;
	  push(pOperand, curToken.number);
	  getNextToken(p,curToken);
	}
      else
	{
	  topOp = top(pOperator);
	  switch(topOp->Compare(curToken.pOperator))
	    {
	    case 1:
	      {
		pop(pOperator, topOp);
		
		cout<<"Do Calc Since top is higher;"<<endl;
		vector<int> v(2);
		
		pop(pOperand, v[1]);
		pop(pOperand, v[0]);
		push(pOperand, topOp->doCalc(v));
		break;
	      }
	    case 0:
	      {
		cout<<"Match Brace, pop stack"<<endl;
		pop(pOperator, topOp);
		getNextToken(p, curToken);
		break;
	      }
	    case -1:
	      {
		cout<<"Push Oper to Stack since top is lower"<<endl;
		push(pOperator, curToken.pOperator);
		getNextToken(p, curToken);
		break;
	      }
	    default:
	      {
		cout<<"Bad in expression"<<endl;
		return -1;
	      }
      
	    }
	}
    }
 }
  catch(MyException &e)
    {
      cout<<"Failed:"<<e;
    }
  int finalResult;
  pop(pOperand, finalResult);
  cout<<"Final Result : = "<<finalResult<<endl;

 cleanup:
  destroyStack(&pOperand);
  destroyStack(&pOperator);

  return 0;

}
