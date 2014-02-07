/*
 * Singleton design pattern demo
 */

#include <iostream>
using namespace std;

// Singleton Class
class Singleton
{
private:
    // The static instance object, priveat
    static Singleton* instance;
    // Constructor must be private
    Singleton() : val(0) { }
    // Other members
    int val;
public:
    // Instance function must be static
    static Singleton* Instance()
    {
        if (instance == 0)
        { instance = new Singleton(); }
        return instance;
    }
    // Other member functions
    int getVal() { return val; }
    void setVal(int v) { val = v; }
};
// Initialize static member
Singleton* Singleton::instance = 0;

// Test singleton pattern
int main()
{
    // Get instance first time
    Singleton::Instance()->setVal(12);
    cout << "Set value 12 to singletion instance." << endl;
    
    // Get instance second time
    Singleton* s = Singleton::Instance();
    cout << "Read value from singletion instance, Val = " << s->getVal() << endl;;

    // The end
    return 0;
}
