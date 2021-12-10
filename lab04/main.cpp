#include <iostream>
#include <cassert>
#include <cmath>
#include "lab04.h"

using namespace std;

int main() {

  // TASK 1: Add code to do the following:
  //  - Create a local EmployeeRecord object
  //  - Initialize the EmployeeRecord using EmployeeRecord_init
  //  - Print the EmployeeRecord using EmployeeRecord_print

  EmployeeRecord emp;
  EmployeeRecord_init(&emp, "Weronika", "F", 20, 4);
  EmployeeRecord_print(&emp);


  // TASK 2: Add code to do the following:
  //  - Create a Company with the name "eecsSoft"
  //  - Add EXACTLY three Employees to the company, using the Employee
  //    constructor and the Company hire_employee function
  //  - Print the company to cout using the << operator

  Company eecsSoft("eecsSoft");

  Employee richard("Richard", "M", 23, 7);
  Employee ronald("Ronald", "M", 21, 5);
  Employee dom("Dom", "F", 17, 2);

  eecsSoft.hire_employee(richard);
  eecsSoft.hire_employee(ronald);
  eecsSoft.hire_employee(dom);
  
  cout << eecsSoft;

  // TASK 2 - Add code to do the following:
  //  - Promote one employee at the company
  //  - Demote one employee at the company
  //  - Print the company to cout using the << operator

  eecsSoft.promote_employee("Ronald");
  eecsSoft.demote_employee("Richard");

  cout << eecsSoft;

}
