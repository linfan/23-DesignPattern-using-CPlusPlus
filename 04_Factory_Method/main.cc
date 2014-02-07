/*
 * Factory method design pattern demo
 *
 * [Usage]:
 * The implementation of an object always change, but it's outlet interface is stable.
 * The Factory method will delay the detail creation to a product's sub class.
 *
 * [Description]:
 * All those product have the same parent class (interface) and a factory to create them.
 * All those factories also inherit from same abstract factory class.
 *
 */

#include <iostream>
using namespace std;

// Abstract product
class AbstractProduct
{
public:
    // Virtual function of the product (interface)
    virtual void PlayMe() = 0;
};

// A concrete product
class ConcreteProduct_Car : public AbstractProduct
{
public:
    // Implement the interface
    virtual void PlayMe()
    { cout << "I'm a toy car, Dooo." << endl; }
};

// Another concrete product
class ConcreteProduct_Doll : public AbstractProduct
{
public:
    // Implement the interface
    virtual void PlayMe()
    { cout << "I'm a little doll, Ahhh." << endl; }
};

// Abstract factory
class AbstractFactory
{
public:
    // virtual function to create product
    virtual AbstractProduct* CreateToy() = 0;
};

// A concrete factory
class ConcreteFactory_CarFactory : public AbstractFactory
{
public:
    // Only create product as car 
    virtual AbstractProduct* CreateToy()
    { return new ConcreteProduct_Car(); }
};

// Another concrete factory
class ConcreteFactory_DollFactory : public AbstractFactory
{
public:
    // Only create product as doll
    virtual AbstractProduct* CreateToy()
    { return new ConcreteProduct_Doll(); }
};

// Test factory method pattern
int main()
{
    // Use a factory pointer to create product
    AbstractFactory *f;
    // Here is its product, the user only need to know interface which product provide
    // and no need to know about the class name of the concrete product
    AbstractProduct *p;

    // Now to create a toy car
    f = new ConcreteFactory_CarFactory();
    p = f->CreateToy();
    p->PlayMe();
    delete f;
    delete p;

    // Then to create a toy doll
    f = new ConcreteFactory_DollFactory();
    p = f->CreateToy();
    p->PlayMe();
    delete f;
    delete p;

    // The end
    return 0;
}
