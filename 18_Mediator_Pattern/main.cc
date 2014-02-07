/*
 * Mediator design pattern demo
 *
 * [Description]:
 * Use a mediator class to divide the complecate interact between two target objects
 * Change the multi-to-multi relation to multi-to-single relation
 *
 */

#include <iostream>
#include <string>
#include <map>
using namespace std;

// Declaration
class Chatroom;

// Abstract colleague
class Participant
{
private:
    // Content a mediator reference
    Chatroom *chatroom;
    // Other members
    string name;

public:
    // Constructor
    Participant(string name)
    { this->name = name; }

    // Properties
    string GetName()
    { return name; }
    Chatroom* GetChatroom()
    { return chatroom; }
    void SetChatroom(Chatroom *value)
    { chatroom = value; }

    // Interaction interface, use mediator to communicate between each other
    void Send(string to, string message);

    // Callback interface
    virtual void Receive(string from, string message)
    { cout << from << " to " <<  name << " : " << message << endl; }
};

// Concrete colleaguel
class Beatle : public Participant
{
public:
    // Constructor
    Beatle(string name) : Participant(name) { }
    virtual void Receive(string from, string message)
    {
        cout << "To a Beatle: ";
        Participant::Receive(from, message);
    }
};

// Another concrete colleague
class NonBeatle : public Participant
{
public:
    //Constructor
    NonBeatle(string name) : Participant(name) { }
    virtual void Receive(string from, string message)
    {
        cout << "To a non-Beatle: ";
        Participant::Receive(from, message);
    }
};

// Mediator interface
class AbstractChatroom
{
public:
    virtual void Register(Participant *participant) = 0;
    virtual void Send(string from, string to, string message) = 0;
};

// Concrete mediator
class Chatroom : public AbstractChatroom
{
private:
    // Use a map to record target objects
    map<string, Participant*> participants;
public:
    // Register, a little like the observer pattern
    virtual void Register(Participant *participant)
    {
        if (participants[participant->GetName()] == NULL)
        {
            participants[participant->GetName()] = participant;
        }
        participant->SetChatroom(this);
    }
    // Outer interface
    virtual void Send(string from, string to, string message)
    {
        Participant *pto = (Participant*)participants[to];
        if (pto != NULL) { pto->Receive(from, message); }
    }
};

// To avoid 'incomplete type' error, put the implementation
void Participant::Send(string to, string message)
{ chatroom->Send(name, to, message); }

// Test mediator pattern
int main()
{
    //create chatroom
    Chatroom *chatroom = new Chatroom();

    //Create participants and register them
    Participant *George = new NonBeatle("George");
    Participant *Paul = new NonBeatle("Paul");
    Participant *Ringo = new NonBeatle("Ringo");
    Participant *John = new Beatle("John");
    Participant *Yoko = new Beatle("Yoko");
    chatroom->Register(George);
    chatroom->Register(Paul);
    chatroom->Register(Ringo);
    chatroom->Register(John);
    chatroom->Register(Yoko);

    //chatting participants
    Yoko->Send("John", "Hi John");
    Paul->Send("Ringo", "All you need is love");
    Ringo->Send("George", "My sweet Lord");
    Paul->Send("John", "Can't buy me love");
    John->Send("Yoko", "My sweet love");

    // The end
    return 0;
}

