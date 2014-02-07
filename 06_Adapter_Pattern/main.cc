/*
 * Apapter design pattern demo
 *
 * [Example]:
 * Wrap vector act as a stack
 *
 */

#include <iostream>
#include <vector>
using namespace std;

// Implement of a stack
template <class T>
class Adapter_Stack
{
    // Adapter content a target object
    vector<T> vec; 
public:
    // New interfaces, wrapper of old interface
    void Push(T item)
    { vec.push_back(item); }
    T Peek()
    { return *(vec.end() - 1); }
    T Pop()
    {
        if (vec.size() == 0)
            return NULL;
        T t = Peek();
        vec.pop_back(); // no return value
        return t;
    }
};

// Test adapter pattern
int main()
{
    // Test new interface
    Adapter_Stack<int> stack;
    stack.Push(0x10);
    cout << stack.Peek() << endl;
    cout << stack.Pop() << endl;
    cout << stack.Pop() << endl;

    // The end
    return 0;
}
