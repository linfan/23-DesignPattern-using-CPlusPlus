/*
 * Memento design pattern demo
 *
 * [User]:
 * Record a object state at the outside the object without break its encapsulation.
 * Make any modification on target object can be revoked.
 *
 * [Description]:
 * The memento class itself is just a data collection.
 * A memento accessor class is needed to process the save/restore progress.
 * 
 * [Note]:
 * The memento should always use deep copy to store data.
 *
 */

#include <iostream>
using namespace std;

// The memnto, record necessary information
class Memento
{
private:
    // Data to store
    string name;
    string phone;
    double budget;

public:
    // Constructor
    Memento(string name, string phone, double budget)
    {
        this->name = name;
        this->phone = phone;
        this->budget = budget;
    }
    // Properties
    string GetName() { return name; }
    void SetName(string value) { name = value; }
    string GetPhone() { return phone; }
    void SetPhone(string value) { phone = value; }
    double GetBudget() { return budget; }
    void SetBudget(double value) { budget = value; }
};

// The memonto accessor
class ProspectMemory
{
private:
    // Have a memonto member, it can also be a list
    Memento *memento;

public:
    // Property
    Memento* GetMemento() { return memento; }
    void SetMemento(Memento *value) { memento = value; }
};

// Originator
class SalesProspect
{
private:
    // Some internal data
    string name;
    string phone;
    double budget;
public:
    // Properties
    string GetName() { return name; }
    void SetName(string value) 
    { name = value; cout << "Name: " << name << endl;}
    string GetPhone() { return phone; }
    void SetPhone(string value)
    { phone = value; cout << "Phone: " << phone << endl;}
    double GetBudget() { return budget; }
    void SetBudget(double value)
    { budget = value; cout << "Budge: " << budget << endl; }

    // Use memento accessor to store data
    Memento* SaveMemento()
    {
        cout << "=> Saving state --" << endl;
        return new Memento(name, phone, budget);
    }
    // Use momento accessor to resotre data
    void RestoreMemento(Memento *memento)
    {
        cout << "=> Restoring state --" << endl;
        SetName(memento->GetName());
        SetPhone(memento->GetPhone());
        SetBudget(memento->GetBudget());
    }
};

// Test memento pattern
int main()
{
    // Set initial state
    SalesProspect *s = new SalesProspect();
    s->SetName("xiaoming");
    s->SetPhone("(010)65236523");
    s->SetBudget(28000.0);

    // Store internal state
    ProspectMemory *m = new ProspectMemory();
    m->SetMemento(s->SaveMemento());

    // Continue changing originator
    s->SetName("deke");
    s->SetPhone("(029)85423657");
    s->SetBudget(80000.0);

    // Restore saved state 
    s->RestoreMemento(m->GetMemento());

    // The end
    return 0;
}
