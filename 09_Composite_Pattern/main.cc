/*
 * Composite design pattern demo
 *
 * [Description]:
 * Create tree based struct, separate change and break down complicated object to many simple ones
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Abstract class of all components
class AbstractComponent_Graphics
{
protected:
    string desc;
public:
    AbstractComponent_Graphics(string s) { desc = s; }
    // component interface
    virtual void Draw() = 0;
};

// For convenience of for_each
void drawChildren(AbstractComponent_Graphics *g) { g->Draw(); }

// The main component which will assamble other components together
// It doesn't have to inherit the abstract component class, but if you can, do it
class Picture : AbstractComponent_Graphics
{
private:
    // The list of compoents
    vector<AbstractComponent_Graphics*> picList;
public:
    Picture(string desc) : AbstractComponent_Graphics(desc) { }
    // Implement interface
    void Draw()
    {
        cout << "== Begin draw picture: " << desc << " =="<< endl;
        for_each (picList.begin(), picList.end(), drawChildren);
        cout << "=======================" << endl;
    }
    // Add component to the final product
    void Add(AbstractComponent_Graphics *g) 
    { picList.push_back(g); }
    // Remove component, be careful about how STL remove an item from list
    void Remove(AbstractComponent_Graphics *g)
    { picList.erase(remove(picList.begin(), picList.end(), g)); }
};

// A concrete component
class Line : public AbstractComponent_Graphics
{
public:
    Line(string desc) : AbstractComponent_Graphics(desc) { }
    // Implement interface
    void Draw()
    { cout << "Draw a line [" + desc << "]" << endl; }
};

// Another concrete component
class Circle: public AbstractComponent_Graphics
{
public:
    Circle(string desc) : AbstractComponent_Graphics(desc) { }
    // Implement interface
    void Draw()
    { cout << "Draw a circle [" + desc << "]" << endl; }
};

// Another concrete component
class Rectangle: public AbstractComponent_Graphics
{
public:
    Rectangle(string desc) : AbstractComponent_Graphics(desc) { }
    // Implement interface
    void Draw()
    { cout << "Draw a rectangle [" + desc << "]" << endl; }
};

// Test Composite pattern
int main()
{
    Picture *root = new Picture("map");

    root->Add(new Line("at the bottom"));
    root->Add(new Rectangle("above the line"));
    Line *l = new Line("this line will be remove");
    root->Add(l);
    root->Add(new Circle("in the rectangle"));
    root->Add(new Line("on the left side of rectangle"));
    root->Remove(l);
    root->Draw();

    // The end
    return 0;
}
