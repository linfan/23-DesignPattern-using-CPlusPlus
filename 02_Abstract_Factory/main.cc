/*
 * Abstract Factory design pattern demo
 *
 * [Description]:
 * Like factory method pattern, but the factory will have more than one product,
 * and each concrete factory will create it's own concrete product combination.
 *
 */

#include <iostream>
using namespace std;

// Abstract product A
class AbstractProduct_A
{
public:
    // Functionality of product A, virtual function
    virtual void DoWork_A() = 0;
};

// Abstract product B
class AbstractProduct_B
{
public:
    // Functionality of product B, virtual function
    virtual void DoWork_B() = 0;
};

// Concrete product of A
class Product_A_sub_1 : public AbstractProduct_A
{
public:
    // Implement the virtual function
    virtual void DoWork_A()
    { cout << "Product A sub 1 instance is working.. 0_0" << endl; }
};

// Concrete product of A
class Product_A_sub_2 : public AbstractProduct_A
{
public:
    // Implement the virtual function
    virtual void DoWork_A()
    { cout << "Product A sub 2 instance is working.. ^_^" << endl; }
};

// Concrete product of B
class Product_B_sub_1 : public AbstractProduct_B
{
public:
    // Implement the virtual function
    virtual void DoWork_B()
    { cout << "Product B sub 1 instance is working.. G_G" << endl; }
};

// Concrete product of B
class Product_B_sub_2 : public AbstractProduct_B
{
public:
    // Implement the virtual function
    virtual void DoWork_B() { cout << "Product B sub 2 instance is working.. X_X" << endl;
    }
};

// Abstract factory
class AbstractFactory
{
public:
    // Virtual function to create two kind of product
    virtual AbstractProduct_A* CreateProductA() = 0;
    virtual AbstractProduct_B* CreateProductB() = 0;
};

// A concrete factory
class ConcreteFactory_sub_1 : public AbstractFactory
{
public:
    // a kind of product A
    virtual AbstractProduct_A* CreateProductA()
    { return new Product_A_sub_1(); }
    // a kind of product B
    virtual AbstractProduct_B* CreateProductB()
    { return new Product_B_sub_1(); }
};

// Another concrete factory
class ConcreteFactory_sub_2 : public AbstractFactory
{
public:
    // another kind of product A
    virtual AbstractProduct_A* CreateProductA()
    { return new Product_A_sub_2(); }
    // another kind of product B
    virtual AbstractProduct_B* CreateProductB()
    { return new Product_B_sub_2(); }
};

// Test abstract factory pattern
int main()
{
    // Create two kind of factory
    AbstractFactory *factory1 = new ConcreteFactory_sub_1();
    AbstractFactory *factory2 = new ConcreteFactory_sub_2();

    // Use abstract pointers to appoint factory and products
    AbstractFactory *f;
    AbstractProduct_A *pA;
    AbstractProduct_B *pB;
    
    // Point to first kind of factory, create some product
    f = factory1;
    pA = f->CreateProductA();
    pB = f->CreateProductB();
    pA->DoWork_A();
    pB->DoWork_B();

    // Point to second kind of factory, create some product
    f = factory2;
    pA = f->CreateProductA();
    pB = f->CreateProductB();
    pA->DoWork_A();
    pB->DoWork_B();

    // The end
    return 0;
}
