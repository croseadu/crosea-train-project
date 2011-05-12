

#include <string>
using std::string;


int sum(const int &v1)
{
  
  return v1+1;
}

extern void sum3(int (&array)[10]);
int sum2(int v2)
{
  int v3;
  int a[10];
  int b[20];
  v3 = sum(0);
  sum3(a);
  sum3(b);

  return v3;

}
