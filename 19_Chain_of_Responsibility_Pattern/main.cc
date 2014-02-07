/*
 * Chain of responsibility pdesign pattern demo
 *
 * [Usage]:
 * A request may have several handlers, but there is only one can really handle it
 * Put all handler on a chain, so the user only pass the request to the first handler,
 * and the user do not care actually which handler made the response.
 *
 */

#include <iostream>
using namespace std;

//Request details
class Purchase
{
private:
    int number;
    double amount;
    string purpose;

public:
    //Constructor
    Purchase(int number, double amount, string purpose)
    {
        this->number = number;
        this->amount = amount;
        this->purpose = purpose;
    }
    //Properties
    void SetAmount(double value) { amount = value; }
    double GetAmount() { return amount; }
    void SetPurpose(string value) { purpose = value; }
    string GetPurpose() { return purpose; }
    void SetNumber(int value) { number = value; }
    int GetNumber() { return number; }
};

// Handler interface
class Approver
{
protected:
    // The higher responder
    Approver *successor;
public:
    // Interface to setup the chain
    void SetSuccessor(Approver *successor)
    { this->successor = successor; }
    // Request interface
    virtual void ProcessRequest(Purchase *purchase) = 0;
};

// Concrete handler
class Director : public Approver
{
public:
    // Handle request
    void ProcessRequest(Purchase *purchase)
    {
        if (purchase->GetAmount() < 10000.0)
        {
            cout << "Director approved request " << purchase->GetNumber() << endl;
        }
        else if(successor != NULL)
        {
            // If cannot handle, pass to higher responser
            successor->ProcessRequest(purchase);
        }
    }
};

// Higher concrete handler
class VicePresident : public Approver
{
public:
    // Handle request
    void ProcessRequest(Purchase *purchase)
    {
        if (purchase->GetAmount() < 25000.0)
        {
            cout << "Vice president approved request " << purchase->GetNumber() << endl;
        }
        else if(successor != NULL)
        {
            // If cannot handle, pass to higher responser
            successor->ProcessRequest(purchase);
        }
    }
};

// The highest concrete handler
class President : public Approver
{
public:
    // Handle request
    void ProcessRequest(Purchase *purchase)
    {
        if (purchase->GetAmount() < 100000.0)
        {
            cout << "President approved request " << purchase->GetNumber() << endl;
        }
        else if(successor != NULL)
        {
            // If cannot handle, pass to higher responser
            successor->ProcessRequest(purchase);
        }
    }
};

// Test chain of responsibility pattern
int main()
{
    // Setup Chain of Responsibility
    Director *Larry = new Director();
    VicePresident *Sam = new VicePresident();
    President *Tammy = new President();
    Larry->SetSuccessor(Sam);
    Sam->SetSuccessor(Tammy);

    // Generate and process purchase requests
    Purchase *p = new Purchase(1034, 350.00, "Supplies");
    Larry->ProcessRequest(p);

    p = new Purchase(2035, 32590.10, "Project X");
    Larry->ProcessRequest(p);

    p = new Purchase(2036, 122100.00, "Project Y");
    Larry->ProcessRequest(p);

    // The end
    return 0;
}

