/*
 * Observer design pattern demo
 *
 * [Usage]:
 * When objects have an multi-to-one relationship, 
 * when the one object changed, all objects depend on it need to update
 *
 * [Description]:
 * All observer objects register themselves to the target object,
 * The target object will sent out notify all registed objects the events.
 * 
 * [Example]:
 * User register this phone number to bank account,
 * each time the amount of money change, user will receive a SMS as notification.
 *
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Declaration
class Emailer;
class Mobile;

// The target object
class BankAccount
{
private:
    // List of registered observers
    vector<Emailer*> emailers;
    vector<Mobile*>  phoneNumbers;
    // Other members
    double _money;

public:
    // Register method
    void AddEmailer(Emailer *value)
    { emailers.push_back(value); }
    void AddPhoneNumber(Mobile *value)
    { phoneNumbers.push_back(value); }

    // Other member methods
    void SetMoney(double value)
    { _money = value; }
    double GetMoney()
    { return _money; }

    // Notify trigger
    // To avoid "incomplete type" error, put define to outside
    void WithDraw();
};

// Observer
class Emailer
{
private:
    string _emailer;
public:
    Emailer(string emailer)
    { _emailer = emailer; }
    void SendEmail(BankAccount *ba)
    { cout << "Notified : Emailer is " << _emailer << ", You withdraw " << ba->GetMoney() << endl; }
};

// Another observer
class Mobile
{
private:
    long _phoneNumber;
public:
    Mobile(long phoneNumber)
    { _phoneNumber = phoneNumber; }
    void SendNotification(BankAccount *ba)
    { cout << "Notified : Phone number is " << _phoneNumber << ", You withdraw " << ba->GetMoney() << endl; }
};

// Notify all registered observers
void BankAccount::WithDraw()
{
    for(vector<Emailer*>::iterator i = emailers.begin(); i != emailers.end(); i++)
    { (*i)->SendEmail(this); }
    for(vector<Mobile*>::iterator i = phoneNumbers.begin(); i != phoneNumbers.end(); i++)
    { (*i)->SendNotification(this); }
}

// Test observer pattern
int main()
{
    // Target object
    BankAccount *ba = new BankAccount();
    // Register observers
    ba->AddEmailer(new Emailer("niubi@163.com"));
    ba->AddEmailer(new Emailer("shenma@163.com"));
    ba->AddPhoneNumber(new Mobile(15001234567));
    ba->AddPhoneNumber(new Mobile(13984531209));
    ba->AddPhoneNumber(new Mobile(16807894461));
    ba->SetMoney(2000);       
    // Send notify
    ba->WithDraw();

    // The end
    return 0;
}
