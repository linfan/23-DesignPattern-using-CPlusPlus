/*
 * Decorator design pattern demo
 *
 * [Usage]:
 * The product contain a main part and some option parts, the same option parts can have more than one instances,
 * and the order of assambling those components is not important.
 * We can use multi-inherit to solve this problem, 
 * but with more component defined, more combination will need, finally the number of class will explode.
 *
 * [Note]:
 * Bridge descript a single-to-single match
 * Decorator is a mult-to-single match, and Decorator class itself is sub-class of Target class
 *
 */

#include <iostream>
using namespace std;

// The abstract target, it's the final product which may be decorate with other components
class AbstractTarget_Tank
{
public:
    // vritual interfaces
    virtual void Shot() = 0;
    virtual void Move() = 0;
};

// A concrete target
class T50 : public AbstractTarget_Tank
{
public:
    // Implement interface
    virtual void Shot()
    { cout << "T50 tank shot 10 time per minute." << endl; }
    virtual void Move()
    { cout << "T50 tank move 10 meters per minute." << endl; }
};

// Another concrete target
class T75 : public AbstractTarget_Tank
{
public:
    // Implement interface
    virtual void Shot()
    { cout << "T75 tank shot 15 time per minute." << endl; }
    virtual void Move()
    { cout << "T75 tank move 12.5 meters per minute." << endl; }
};

// The decorator must inherit from the final product
class AbstractDecorator : public AbstractTarget_Tank
{
    // The target to decorate with
    AbstractTarget_Tank *tank;
protected:
    // Cannot be instantiated
    AbstractDecorator(AbstractTarget_Tank* t) : tank(t) {} 
public:
    // Decorator has same interface as the target product
    virtual void Shot() { tank->Shot(); }
    virtual void Move() { tank->Move(); }
};

// A concrete decorator
class InfraredSensor : public AbstractDecorator
{
public:
    // Get target as construction parameter
    InfraredSensor(AbstractTarget_Tank* t) : AbstractDecorator(t) {}
    // The interface that get decorated
    virtual void Shot()
    {
        // Decoration behavior
        cout << "Using infrared sensor .." << endl;
        // Call parent's implement
        AbstractDecorator::Shot(); 
    }
    // Other interface will inherit parent's
};

// Another concrete decorator
class GPS : public AbstractDecorator
{
public:
    // Get target as construction parameter
    GPS(AbstractTarget_Tank *t) : AbstractDecorator(t) {}
    // The interface that get decorated
    virtual void Move()
    {
        // Decoration behavior
        cout << "Using GPS navigating .." << endl;
        // Call parent's implement
        AbstractDecorator::Move();
    }
    // Other interface will inherit parent's
};
    
// Test decorator pattern
int main()
{
    // The final tank pointer
    AbstractTarget_Tank *tank;

    // Decorator is sub-class of the target, we can always use the abstract taget class
    // Create a T50 tank with a infrared sensor
    AbstractTarget_Tank *t50 = new T50();
    AbstractTarget_Tank *infrared = new InfraredSensor(t50);
    tank = infrared; // pointer to the laster wrapper
    cout << "==== T50 tank coming ====" << endl;
    tank->Move();
    tank->Shot();

    // Create a T75 tank with two GPS
    AbstractTarget_Tank *t75 = new T75();
    AbstractTarget_Tank *gps_1 = new GPS(t75);
    AbstractTarget_Tank *gps_2 = new GPS(gps_1);
    tank = gps_2; // pointer to the laster wrapper
    cout << "==== T75 tank coming ====" << endl;
    tank->Move();
    tank->Shot();
    
    // The end
    return 0;
}
