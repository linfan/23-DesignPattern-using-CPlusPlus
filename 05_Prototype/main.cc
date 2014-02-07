/*
 * ProtoType design pattern demo
 *
 * [Usage]:
 * The situation just like factory method pattern, 
 * the production interface is stable, but its implementation is flexible.
 *
 * [Description]:
 * Each product class contain it's own method to create itself.
 *
 * [Note]:
 * ProtoType is a special factory class, the factory itself is also the product
 *
 */

#include <iostream>
#include <time.h>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

// The abstract product, and it is its own factory
class ProtoType_Cell
{
    // Not a must, only give a identification code to each copy
    static int id; 
public:
    // clone() is a method let the product to create itself
    virtual ProtoType_Cell* Clone() = 0;
    // The interface functions
    virtual string GetInfo() = 0;
    // Other member functions
    static int GetUid() { return id++; }
};
// Initialize static members
int ProtoType_Cell::id = 0;

// A concrete product
class BodyCell : public ProtoType_Cell
{
    // It's own members
    int x, y, id;
public:
    // It's own construction
    BodyCell(int x, int y) : x(x), y(y) { id = ProtoType_Cell::GetUid(); }
    // Implement clone() method, do a deep copy of itself
    virtual ProtoType_Cell* Clone()
    {
        srand(time(NULL)); // Let's have something random
        ProtoType_Cell *cell = new BodyCell(rand() % 100, rand() % 100 );
        return cell;
    }
    // Implement the interface
    virtual string GetInfo()
    {
        ostringstream pos_string;
        pos_string << "BodyCell id " << id << " at ( " << x << ", " << y << " ).";
        return pos_string.str();
    }
};

// Another concrete product
class BrainCell : public ProtoType_Cell
{
    // it's own members
    int id, IQ;
public:
    // It's own construction
    BrainCell(int iq) : IQ(iq) { id = ProtoType_Cell::GetUid(); }
    // Implement clone() method, do a deep copy of itself
    virtual ProtoType_Cell* Clone()
    {
        srand(time(NULL)); // Again something random
        ProtoType_Cell *cell = new BrainCell(rand() % 50 + 80 );
        return cell;
    }
    // Implement the interface
    virtual string GetInfo()
    {
        ostringstream iq_string;
        iq_string << "BrainCell id " << id << " with IQ: " << IQ << " .";
        return iq_string.str();
    }
};

// Test prototype pattern
int main()
{
    // Two body cells
    ProtoType_Cell* bodyCell_1 = new BodyCell(50, 50);
    ProtoType_Cell* bodyCell_2 = bodyCell_1->Clone();

    // Two brain cells
    ProtoType_Cell* brainCell_1 = new BrainCell(100);
    ProtoType_Cell* brainCell_2 = brainCell_1->Clone();
    
    // Show information
    vector<ProtoType_Cell*> cells;
    cells.push_back(bodyCell_1);
    cells.push_back(bodyCell_2);
    cells.push_back(brainCell_1);
    cells.push_back(brainCell_2);

    // for each
    vector<ProtoType_Cell*>::const_iterator p = cells.begin();
    while (p != cells.end())
    {
        cout << (*p)->GetInfo() << endl;
        p++;
    }
    // foreach, lambda function, c++ only
    //for_each(cells.begin(), cells.end(),
    //        [](ProtoType_Cell *cell){ cout << cell->GetInfo() << endl; });
    
    // The end
    return 0;
}
