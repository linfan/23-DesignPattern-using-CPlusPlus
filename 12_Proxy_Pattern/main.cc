/*
 * Proxy design pattern demo
 *
 * [Usage]:
 * There are changes happen on the other side of an interface, or user want to add extra process to exist interface
 * e.g. add a encrytion/decrytion layer behind the interface, add operation record transparently.
 *
 * [Description]:
 * The proxy class and server class inherit from same interface (abstract class)
 * The user can use totally same way to handle proxy and the original server
 *
 */

#include <iostream>
using namespace std;

// Public interface
class IMath
{
public:
    // Interfaces
    virtual double Add(double x,double y) = 0;
    virtual double Sub(double x,double y) = 0;
    virtual double Mul(double x,double y) = 0;
    virtual double Dev(double x,double y) = 0;
};

// The original server class
class Math : public IMath
{
public:
    // Implement the interface
    double Add(double x,double y) { return x + y; }
    double Sub(double x,double y) { return x - y; }
    double Mul(double x,double y) { return x * y; }
    double Dev(double x,double y) { return x / y; }
};

// The proxy class
class MathProxy : public IMath
{
private:
    // Contain the original class
    Math math;
public:
    // Implement the interface
    double Add(double x,double y)
    { return math.Add(x,y) + 100; }
    double Sub(double x,double y)
    { return math.Sub(x,y) + 100; }
    double Mul(double x,double y)
    { return math.Mul(x,y) + 100; }
    double Dev(double x,double y)
    { return math.Dev(x,y) + 100; }
};

// Test Proxy pattern
int main()
{
    // Use original server to do operation
    IMath *math = new Math();
    cout << math->Add(2,3) << endl;
    cout << math->Sub(6,4) << endl;
    cout << math->Mul(2,3) << endl;
    cout << math->Dev(2,3) << endl;

    // Use proxy to do the same job
    IMath *pmath = new MathProxy();
    cout << pmath->Add(2,3) << endl;
    cout << pmath->Sub(6,4) << endl;
    cout << pmath->Mul(2,3) << endl;
    cout << pmath->Dev(2,3) << endl;

    // The end
    return 0;
}
