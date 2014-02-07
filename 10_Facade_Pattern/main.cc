/*
 * Facade design pattern demo
 *
 * [Usage]:
 * A large system contains many sub systems, the interface of each sub-system change frequently
 *
 * [Description]:
 * Create a facade class to provide unified interface to user, hide the complex change in each sub-system
 * This pattern offen use for lower layer provide interface to higher layer
 *
 */

#include <iostream>
using namespace std;

// The user class
class Customer
{ 
    string name;
public:
    Customer(string s) : name(s) {}
    string GetName() { return name; }
}; 

// Bank sub-system
class Bank
{
public:
    // A mutable interface
    bool HasSufficientSavings(Customer *c, int amount)
    { cout << "Check bank for " << c->GetName() << " have more than " << amount << endl; return true; }
};

// Credit sub-system
class Credit
{
public:
    // A mutable interface
    bool HasGoodCredit(Customer *c)
    { cout << "Check credit for " << c->GetName() << endl; return true; }
};

// Loan sub-system
class Loan
{
public:
    // A mutable interface
    bool HasNoBadLoans(Customer *c)
    { cout << "Check loans for " << c->GetName() << endl; return true; }
};

// The facade class, hide sub-systems behind it
class Mortgage
{
private: 
    // Sub systems
    Bank *bank;
    Loan *loan;
    Credit *credit;
public:
    // Simply the three interfaces to only one
    bool IsEligible(Customer *cust, int amount)
    {
        cout << cust->GetName() << " applies for " << amount << " loan" << endl;
        bool eligible = true; 
        // Use interface provided by sub systems
        if (!bank->HasSufficientSavings(cust, amount))
        { eligible = false; }
        else if (!loan->HasNoBadLoans(cust))
        { eligible = false; }
        else if (!credit->HasGoodCredit(cust))
        { eligible = false; }

        return eligible;
    }
};

// Test Facade pattern
int main()
{
    // Facade provide the simply interface
    Mortgage *mortgage = new Mortgage();

    // Use the simply interface
    Customer *customer = new Customer(string("Ann McKinsey"));
    bool eligable = mortgage->IsEligible(customer, 125000);
    cout << customer->GetName() << " has been " << (eligable ? "Approved" : "Rejected") << endl; 

    // The end
    return 0;
}
