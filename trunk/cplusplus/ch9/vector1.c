#include <vector>
#include <list>
#include <string>

using std::string;
using std::vector;
using std::list;

int main()
{
  int ia[7]= {0};
  string sa[6] = {"ab","cd","ef","gh","ij","kl"
  };


  vector<string> svec(sa, sa+6);
  list<int> ilist(ia+4, ia+6);
  vector<int> ivec(ia, ia+8);
  list<string> slist(sa+6, sa);



  return 0;
}
