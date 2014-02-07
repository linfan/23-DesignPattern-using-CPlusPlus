/*
 * Template design pattern demo
 *
 * [Description]:
 * The step order of an serial operation is stable,
 * but each step content is different for differrent situation.
 * The parent class offer the outlet interface,
 * delay the changes (step implementation) to sub-classes.
 *
 */

#include <iostream>
#include <string>
using namespace std;

// The operation outlet
class DataAccessObject
{
protected:
    string connectionString;
    string dataSet;

    // Default implementation, can be override in sub-classes
    virtual void Connect()
    { connectionString = "Server=.;User Id=sa;Password=;Database=Northwind"; }
    virtual void Disconnect()
    { connectionString = ""; }

    // The implementation of this two steps are delay to sub-classes
    virtual void Select() = 0;
    virtual void Display() = 0;

public:
    // The "Template Method" 
    void Run()
    {
        Connect();
        Select();
        Display();
        Disconnect();
    }
};

// Just a function, for convenient
string SqlResult(string sql, string connectionString)
{ return (string("Result of '") + sql + string("'")); }

// A sub-class of the templated operation
class Categories : public DataAccessObject
{
protected:
    // Implement the missing steps (protected interface)
    void Select()
    {
        string sql = "select CategoryName from Categories";
        dataSet = SqlResult(sql, connectionString);
    }
    void Display()
    {
        cout << "Categories ---- " << endl;
        cout << dataSet << endl;
    }
};

// Another sub-class of the templated operation
class Products : public DataAccessObject
{
protected:
    // Implement the missing steps (protected interface)
    void Select()
    {
        string sql = "select top 10 ProductName from Products";
        dataSet = SqlResult(sql, connectionString);
    }
    void Display()
    {
        cout << "Products ---- " << endl;
        cout << dataSet << endl;
    }
};

// Test Template pattern
int main()
{
    // The outlet interface object
    DataAccessObject *dao;

    // Instantiate to a sub-class
    dao = new Categories();
    dao->Run();
    delete dao;

    // Instantiate to another sub-class
    dao = new Products();
    dao->Run();
    delete dao;

    // The end
    return 0;
}
