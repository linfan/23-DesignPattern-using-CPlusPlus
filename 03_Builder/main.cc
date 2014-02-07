/*
 * Builder design pattern demo
 *
 * [Usage]:
 * One large object contain many parts, each part may change separately
 *
 * [Description]:
 * The director class only contain the steps to create a large object,
 * The builder class know the detail of each steps, all builder inherit from same builder interface.
 * User use director and select a concrete builder to create final product.
 *
 * [Example]:
 * Builder mode, like a customer order dinner in a restaurant.
 * He only need to tell cashier the food species then get food from the chef.
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
using namespace std;

// The "large object", our final product
class Product_Food
{
    // Some contents in this product
    string foodName;
    string courses;
public:
    // Mendatory functions
    Product_Food(string name) : foodName(name) {}
    void AddCourse(string sth) { if (courses == "") courses = sth; else courses += (" & " + sth); }
    // Get what we build
    string GetTaste() { return "[" + foodName + "] => " + courses; }
};

// The abstract builder, who know the details how to build the product
class AbstractBulder_Chef
{
public:
    // Virtual functions, each build steps
    virtual void CookSoup(Product_Food *food) = 0;
    virtual void CookVegetable(Product_Food *food) = 0;
    virtual void CookMeat(Product_Food *food) = 0;
};

// A concrete builder, implement the steps
class ConcreteBuilder_ChineseChef : public AbstractBulder_Chef
{
public:
    // Implement the virtual functions
    virtual void CookSoup(Product_Food *food) { food->AddCourse("Chinese soup"); }
    virtual void CookVegetable(Product_Food *food) { food->AddCourse("Chinese vegetable"); }
    virtual void CookMeat(Product_Food *food) { food->AddCourse("Chinese meat"); }
};

// Another concrete builder, implement the steps
class ConcreteBuilder_AmericanChef : public AbstractBulder_Chef
{
    ostringstream food;
public:
    // Implement the virtual functions
    virtual void CookSoup(Product_Food *food) { food->AddCourse("American soup"); }
    virtual void CookVegetable(Product_Food *food) { food->AddCourse("American vegetable"); }
    virtual void CookMeat(Product_Food *food) { food->AddCourse("American meat"); }
};

// The director, who provide products, he only know the steps to create the large object
class Director_cashier
{
public:
    Director_cashier(AbstractBulder_Chef* chef, Product_Food *food)
    {
        // The build step is constant
        chef->CookSoup(food);
        chef->CookVegetable(food);
        chef->CookMeat(food);
    }
};

// Test builder pattern
int main()
{
    // Get customer information from outside
    ifstream customers;
    customers.open("./customers");
    vector<string> list;
    istream_iterator<string> infile(customers);
    istream_iterator<string> eoffile;
    // copy() Equal to "while (infile != eoffile) { list.push_back(*infile); infile++; }"
    copy(infile, eoffile, inserter(list, list.begin()));
    customers.close();

    // The pointer to our builder, director and product
    AbstractBulder_Chef *chef;
    Director_cashier *cashier;
    Product_Food *food;

    // Serve each customer
    for (vector<string>::iterator i = list.begin(); i != list.end(); i++)
    {
        // Select a builder
        if (*i == "Chinese")
            chef = new ConcreteBuilder_ChineseChef();
        else if (*i == "American")
            chef = new ConcreteBuilder_AmericanChef();
        else
            continue;
        food = new Product_Food(*i + " food");
        // The director use builder to create a product
        cashier = new Director_cashier(chef, food);
        cout << "Serve " << food->GetTaste() << " to " << *i << endl;
        delete food;
        delete chef;
        delete cashier;
    }

    // The end
    return 0;
}
