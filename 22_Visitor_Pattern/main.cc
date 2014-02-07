/*
 * Vistor design pattern demo
 *
 * [Description]:
 * Some class has stable data structure, but the operation to its data is mutable.
 * Put all operation to separate visitor objects, 
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Declaration
class Employee;

// The vistor/modifyer interface
class IVisitor
{
public:
    // An operation
    virtual void Visit(Employee *employee) = 0;
};

// The element interface
class Employee
{
public:
    // Data
    string Name;
    double Income;
    int VacationDays;

    // Constructor
    Employee(string n, double i, int v)
        : Name(n), Income(i), VacationDays(v)
    { cout << "Employee " << Name << ": income " << Income
        << ", vacation day " << VacationDays << endl; }

    // Interface to modify member data
    virtual void Accept(IVisitor *visitor)
    { visitor->Visit(this); }
};

// An concrete data container
class Clerk : public Employee
{
public:
    // Constructor
    // Set original data
    Clerk() : Employee("Hank", 25000.0, 14) { }
};

// Another concrete data container
class Director : public Employee
{
public:
    // Constructor
    // Set original data
    Director() : Employee("Elly", 35000.0, 16) { }
};

// Another concrete data container
class President : public Employee
{
public:
    // Constructor
    // Set original data
    President() : Employee("Dick", 45000.0, 21) { }
};

// A concrete vistor/modifyer
class IncomeVisitor : public IVisitor
{
public:
    // An modificaton operation
    virtual void Visit(Employee *employee)
    {
        // Provide 10% pay raise
        employee->Income *= 1.10;
        cout << "employee " << employee->Name << 
            "'s new income: " << employee->Income << endl;
    }
};

// Another concrete vistor/modifyer
class VacationVisitor : public IVisitor
{
public:
    // Another modificaton operation
    virtual void Visit(Employee *employee)
    {
        // Provide 3 extra vacation days
        employee->VacationDays += 3;
        cout << "employee " << employee->Name << 
            "'s new vacation days: " << employee->VacationDays << endl;
    }
};

// Empolyee collections, apply bulk changes to a serial of elements
class Employees
{
private:
    // Collection
    vector<Employee*> employees;
public:
    // Add instance
    void Attach(Employee *employee)
    { employees.push_back(employee); }
    // Remove instance
    void Detach(Employee *employee)
    { employees.erase(remove(employees.begin(), employees.end(), employee)); }

    // Apply bulk action
    void Accept(IVisitor *visitor)
    {
        vector<Employee*>::const_iterator pemployee = employees.begin();
        while(pemployee != employees.end())
        {
            (*pemployee)->Accept(visitor);
            pemployee++;
        }
        //for_each (employees.begin(), employees.end(),
        //        [visitor](Employee* e){ e->Accept(visitor); });
    }
};

// Test vistor pattern
int main()
{
    // Setup employee collection
    Employees *e = new Employees();
    e->Attach(new Clerk());
    e->Attach(new Director());
    e->Attach(new President());

    // Employees are 'visited(modified)'
    e->Accept(new IncomeVisitor());
    e->Accept(new VacationVisitor());

    // The end
    return 0;
}
