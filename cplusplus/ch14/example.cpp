#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class finance
{
public:
  
  friend std::ostream& operator<<(std::ostream&, const finance &);

  finance(const char *name):department_name(name),
			    employee_num(0),total_salary(0.0){};
  ~finance(){};
  void set_manager(const char *name, unsigned int salary)
  {
    manager_name = string(name);
    add_employee(name, salary);
  };
  void add_employee(const char *name, unsigned int salary)
  {
    employee_name.push_back(name);
    total_salary += (double)salary;
    employee_num++;
  };

private:
  string department_name;
  string manager_name;
  vector<string> employee_name;
  unsigned int employee_num;
  double total_salary;
};


std::ostream& operator<<(std::ostream &out, const finance& dep)
{
  out<<"Dep: "<<dep.department_name<<std::endl<<"Manager: "<<dep.manager_name<<std::endl;
  out<<"Employee: "<<std::endl;
  for(vector<string>::const_iterator p = dep.employee_name.begin(); 
      p != dep.employee_name.end(); p++)
    {
      out<<*p<<std::endl;
    }
  
  double average_salary;
  average_salary = dep.total_salary/dep.employee_num;
  out<<"Average Salary: "<<average_salary<<std::endl;
  return out;
}


int main()
{

  finance dte("Develope Tool Team");

  dte.set_manager("LiPing Gao", 500000);
  dte.add_employee("Liang Wang", 450000);
  std::cout<<dte;

  return 0;

}
