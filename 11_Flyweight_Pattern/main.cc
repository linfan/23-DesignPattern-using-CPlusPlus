/*
 * Flyweight design pattern demo
 *
 * [Usage]:
 * System contain large number of instances of a class, 
 * many of those instances are the same, but they occupied lots of memory
 * others are not identical, but most of attribute value are the same
 *
 * [Description]:
 * Use a Flyweight Factory to manage the creation of instances.
 * When creating a new object if there are no instance exist with identical attribute,
 * Flyweight Factory will create a new one and record it into a hash table.
 * Otherwise, the one in the hash table will be reused.
 * 
 * [Extension]:
 * For those instance which is not identical but have many same value attribute.
 * Use a static object inside the class to share those attribute with all instances.
 * But this is not a content of flyweight design pattern require.
 *
 */

#include <iostream>
#include <map>
using namespace std;

// The abstract flyweight objects, interfaces
class Charactor
{
public:
    // Interfaces
    virtual void Display() = 0;
    // Shared attribute
    virtual char GetSymbol() = 0;
    virtual int GetWidth() = 0;
    virtual int GetHeight() = 0;
    virtual int GetAscent() = 0;
    virtual int GetDescent() = 0;
    // Stand alone attribute
    virtual int GetPointSize() = 0;
    virtual void SetPointSize(int size) = 0;
};

// The static part of concrete flyweight object CharactorA
class CharactorA_Shared
{
friend class CharactorA;
private:
    char _symbol;
    int _width, _height, _ascent, _descent;
    CharactorA_Shared()
    { _symbol = 'A'; _height = 100; _width = 120; _ascent = 70; _descent = 0; }
};
// A concrete flyweight class
class CharactorA : public Charactor
{
private:
    // Stand alone attributes
    int _pointSize;
    // Shared attributes container
    static CharactorA_Shared shared;
public:
    CharactorA(int size) : _pointSize(size) { }
    // Implement the interfaces
    virtual char GetSymbol() { return shared._symbol; }
    virtual int GetWidth() { return shared._width; }
    virtual int GetHeight() { return shared._height; }
    virtual int GetAscent() { return shared._ascent; }
    virtual int GetDescent() { return shared._descent; }
    virtual int GetPointSize() { return _pointSize; }
    virtual void SetPointSize(int size) { _pointSize = size; }
    virtual void Display()
    { cout << GetSymbol() << " pointsize: " << GetPointSize() << endl; }
};
// Initialize static members
CharactorA_Shared CharactorA::shared;

// The static part of concrete flyweight object CharactorB
class CharactorB_Shared
{
friend class CharactorB;
private:
    char _symbol;
    int _width, _height, _ascent, _descent;
    CharactorB_Shared()
    { _symbol = 'B'; _height = 100; _width = 120; _ascent = 70; _descent = 0; }
};
// Another concrete flyweight class
class CharactorB : public Charactor
{
private:
    // Stand alone attributes
    int _pointSize;
    // Shared attributes container
    static CharactorB_Shared shared;
public:
    // Implement the interfaces
    CharactorB(int size) : _pointSize(size) { }
    virtual char GetSymbol() { return shared._symbol; }
    virtual int GetWidth() { return shared._width; }
    virtual int GetHeight() { return shared._height; }
    virtual int GetAscent() { return shared._ascent; }
    virtual int GetDescent() { return shared._descent; }
    virtual int GetPointSize() { return _pointSize; }
    virtual void SetPointSize(int size) { _pointSize = size; }
    virtual void Display()
    { cout << GetSymbol() << " pointsize: " << GetPointSize() << endl; }
};
// Initialize static members
CharactorB_Shared CharactorB::shared;

// The flyweight factory
class CharactorFactory
{
private:
    // The hash table to record exist flyweight objects
    map<pair<char,int>, Charactor*> charactors;
    // Singleton class
    CharactorFactory() { }
    static CharactorFactory *instance;
public:
    static CharactorFactory* Instance()
    {
        if (instance == NULL)
        { instance = new CharactorFactory(); }
        return instance;
    }
    // Create or reuse a flyweight object
    Charactor* GetCharactor(char key, int size)
    {
        if (!charactors[pair<char,int>(key, size)])
        {
            switch (key)
            {
                case 'A': 
                    charactors[pair<char,int>(key, size)] = new CharactorA(size);
                    break;
                case 'B': 
                    charactors[pair<char,int>(key, size)] = new CharactorB(size);
                    break;
                default: throw key;
            }
        }
        return charactors[pair<char,int>(key, size)];
    }
};
// Initialize static members
CharactorFactory *CharactorFactory::instance = 0;

// Test Flyweight pattern
int main()
{
    // Frist charactor "A"
    Charactor *ca_1 = CharactorFactory::Instance()->GetCharactor('A', 10);
    ca_1->Display();

    // Second charactor "A", same as first one
    Charactor *ca_2 = CharactorFactory::Instance()->GetCharactor('A', 10);
    ca_2->Display();
    cout << "Ca_1 and Ca_2 " << (ca_1 == ca_2 ? "is" : "is NOT" ) << " the same" << endl;

    // Third charactor "A", different from first one
    Charactor *ca_3 = CharactorFactory::Instance()->GetCharactor('A', 12);
    ca_3->Display();
    cout << "Ca_1 and Ca_3 " << (ca_1 == ca_3 ? "is" : "is NOT" ) << " the same" << endl;

    // The end
    return 0;
}
