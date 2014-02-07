/*
 * Iterator design pattern demo
 *
 * [Description]:
 * Provide a way for outer to visit its content in an specific order without exposing the internal structure
 *
 * [Example]:
 * A container like a TV, you can use a control (iterator) to watch different channels
 *
 */

#include <iostream>
using namespace std;

// iterator interface
template <class T>
class IIterator
{
public:
    // Get current item
    virtual T CurrentItem() = 0;
    // Whether have next item
    virtual bool MoveNext() = 0;
    // Move cursor to first item
    virtual void First() = 0;
    // Move cursor to next item
    virtual void Next() = 0;
};

// container interface
template <class T>
class IList
{
public:
    // Provide a iterator
    virtual IIterator<T>* GetIterator() = 0;
};

// declaration
template <class T>
class ConcreteIterator;

// A concrete container
#define LENGTH 10
template <class T>
class ConcreteList : public IList<T>
{
    T list[LENGTH];
public:
    ConcreteList<T>(T t) // C++11 only
        : list { t, t+4, t-3, t-4, t+5, t-1, t+5, t+8, t-2, t+3 }
    { }

    // Implement the interface
    IIterator<T>* GetIterator()
    { return new ConcreteIterator<T>(this); }

    // Other common method of a container
    int Length()
    { return LENGTH; }
    int GetElement(int index)
    { return list[index]; }
};

// A concrete iterator
template <class T>
class ConcreteIterator : public IIterator<T>
{
private:
    // Have a container member
    ConcreteList<T> *list;
    // Current position
    int index;
public:
    ConcreteIterator<T>(ConcreteList<T> *l) : list(l), index(0)
    { }
    // Implement the interfaces
    bool MoveNext()
    { return (index < list->Length()); }
    T CurrentItem()
    { return list->GetElement(index) ; }
    void First()
    { index = 0; }
    void Next()
    { if (index < list->Length()) { index++; } }
};

// Test iterator pattern
int main()
{
    IIterator<int> *iterator;
    IList<int> *list = new ConcreteList<int>(7);
    iterator = list->GetIterator();
    // Move through the container
    while (iterator->MoveNext())
    {
        cout << (int)iterator->CurrentItem() << endl;
        iterator->Next();
    }

    // The end
    return 0;
}

