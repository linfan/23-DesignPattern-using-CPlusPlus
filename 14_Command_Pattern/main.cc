/*
 * Command design pattern demo
 *
 * [Descritpion]:
 * Separete the request proposer and command implementation
 * Pack the request as a command object, so that the request can be put in queue,
 * if needed, you can undo the command by calling the undo func of the command implementation.
 * The command is not depend on object that it apply to, it can be apply to any support objects.
 *
 */

#include <iostream>
#include <vector>
using namespace std;

// Target object
class Document
{
    char* name;
public:
    Document(char* s) : name(s) { }
    char* GetDocName() { return name; }
};

// Abstract command
class DocumentCommand
{
protected:
    // Have a target object pointer
    Document *document;
public:
    DocumentCommand(Document *doc) : document(doc) { }
    // Command interfaces
    virtual void Execute() = 0;
    virtual void Undo() = 0;
};

// A concrete command
class DisplayCommand : public DocumentCommand
{
public:
    DisplayCommand(Document *doc) : DocumentCommand(doc) { }
    // Here is how this commmand handle the target object
    void Execute() { cout << "Display: " << document->GetDocName() << endl; } 
    void Undo() { cout << "Hide doc: " << document->GetDocName() << endl; }
};

// Another concrete command
class DeleteCommand : public DocumentCommand
{ 
public:
    DeleteCommand(Document *doc) : DocumentCommand(doc) { }
    // Here is how this commmand handle the target object
    void Execute() { cout << "Delete: " << document->GetDocName() << endl; } 
    void Undo() { cout << "Restore doc: " << document->GetDocName() << endl; }
};

// Maintaining all commands
class DocumentInvoker
{
    // To recode the command order
    vector<DocumentCommand*> undoQueue;
    vector<DocumentCommand*> redoQueue;
public:
    void Execute(DocumentCommand *cmd)
    {
        undoQueue.push_back(cmd);
        cmd->Execute();
    }
    void Undo()
    {
        if (undoQueue.size() > 0)
        {
            DocumentCommand *cmd = *(undoQueue.end() -1);
            cmd->Undo(); 
            redoQueue.push_back(cmd);
            undoQueue.pop_back();
        }
    }
    void Redo()
    { 
        if (redoQueue.size() > 0)
        {
            DocumentCommand *cmd = *(redoQueue.end() -1);
            cmd->Execute(); 
            undoQueue.push_back(cmd);
            redoQueue.pop_back();
        }
    }
};

// Test command pattern
int main()
{
    // Target objects
    Document *doc = new Document("Mint.iso");
    Document *doc_2 = new Document("Ubuntu.iso");

    // Commands
    DisplayCommand *dispCmd = new DisplayCommand(doc);
    DeleteCommand *delCmd = new DeleteCommand(doc);
    DisplayCommand *dispCmd_2 = new DisplayCommand(doc_2);

    // Invoker
    DocumentInvoker *invoker = new DocumentInvoker();

    // Play with commands
    invoker->Execute(dispCmd);
    invoker->Execute(delCmd);
    invoker->Undo();
    invoker->Execute(dispCmd_2);
    invoker->Undo();
    invoker->Redo();
    invoker->Undo();
    invoker->Undo();
    invoker->Undo();
    invoker->Undo();

    // The end
    return 0;
}

