/*
 * Bridge design pattern demo
 *
 * [Usage]:
 * the final product content two or more parts, each part will change separately
 *
 * [Description]:
 * Define each part as an abstract component class,
 * One of those is the "main component", which hold all other components
 *
 */

#include <iostream>
#include <string>
using namespace std;

// A part of components, abstrace class (interface)
class Color
{
public:
    // interface members or methods
    virtual string GetColor() = 0;
};

// A concrete Color
class Red : public Color
{
public:
    // Implement the interface
    string GetColor() { return "red"; }
};

// Another concrete Color
class Blue : public Color
{
public:
    // Implement the interface
    string GetColor() { return "blue"; }
};

// The main component
class Brush
{
protected:
    // Contain all other components
    Color *c;
public:
    void SetColor(Color *c) { this->c = c; }
    // Make it cannot be instantiated
    virtual void Paint() = 0;
};

// A concrete Brush
class BigBrush : public Brush
{
public:
    // Implement the interface
    virtual void Paint()
    { cout << "Using BIG brush and color \"" << c->GetColor() << "\" painting." << endl; }
};

// Another concrete Brush
class SmallBrush : public Brush
{
public:
    // Implement the interface
    virtual void Paint()
    { cout << "Using SMALL brush and color \"" << c->GetColor() << "\" painting." << endl; }
};

// Test bridge pattern
int main()
{
    // The main component pointer
    Brush *b; 

    // Use big brush with blue color
    b = new BigBrush();
    b->SetColor(new Blue());
    b->Paint();

    // Use small brush with red color
    Brush *brush_2 = new SmallBrush();
    b->SetColor(new Red());
    b->Paint();
    
    // The end
    return 0;
}
