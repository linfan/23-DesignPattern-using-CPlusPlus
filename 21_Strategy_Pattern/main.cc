/*
 * Strategy design pattern demo
 *
 * [Usage]:
 * A object need frequently change its arithmetic,
 * In order to maintain those arithmetic, avoiding too many functions inside a class, 
 * a good way is put each of them into a separate object.
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Abstract stategy
class SortStrategy
{
public:
    // Strategy interface
    virtual void Sort(vector<string> &list) = 0;
};

// A concrete strategy
class ShellSort : public SortStrategy
{
public:
    // Implement strategy solution
    virtual void Sort(vector<string> &list)
    {
        sort(list.begin(), list.end()); //no-implement
        cout << "ShellSorted List" << endl;
    }
};

// Another concrete strategy
class MergeSort : public SortStrategy
{
public:
    // Implement strategy solution
    virtual void Sort(vector<string> &list)
    {
        sort(list.begin(), list.end()); //no-implement
        cout << "MergeSort List" << endl;
    }
};

// Another concrete strategy
class QuickSort : public SortStrategy
{
public: 
    // Implement strategy solution
    virtual void Sort(vector<string> &list)
    {
        sort(list.begin(), list.end()); //no-implement
        cout << "QuickSorted List" << endl;
    }
};

//Context
class SortdList
{
private:
    // A strategy object
    SortStrategy *sortstrategy;
    // Other members
    vector<string> list;
public:
    // Set strategy method
    void SetSortStrategy(SortStrategy *sortstrategy)
    { this->sortstrategy = sortstrategy; }

    void Add(string name)
    { list.push_back(name); }

    // Do arithmetic
    void Sort()
    {
        // Call function provide by strategy class
        sortstrategy->Sort(list);
        // Show results
        vector<string>::const_iterator pname = list.begin();
        while(pname != list.end())
        {
            cout << "" << (*pname);
            pname++;
        }
        //for_each (list.begin(), list.end(), // lambda function, c++11 only
        //        [](string name){ cout << " " << name; });
        cout << endl;
    }
};

// Test strategy pattern
int main()
{
    //Two contexts following different strategies 
    SortdList *studentRecords = new SortdList();

    // Put string on any order
    studentRecords->Add("Satu");
    studentRecords->Add("Jim");
    studentRecords->Add("Palo");
    studentRecords->Add("Terry");
    studentRecords->Add("Annaro");

    // Use different arithmetic to sort
    studentRecords->SetSortStrategy(new QuickSort());
    studentRecords->Sort();

    studentRecords->SetSortStrategy(new ShellSort());
    studentRecords->Sort();

    studentRecords->SetSortStrategy(new MergeSort());
    studentRecords->Sort();

    // The end
    return 0;
}
