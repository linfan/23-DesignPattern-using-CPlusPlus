/*
 * State design pattern demo
 *
 * [Description]:
 * An object have different behaivor under different state,
 * An object should alway under one of the pre-defined states.
 * Operation under a state may change the object to another state.
 *
 */

#include <iostream>
#include <string>
using namespace std;

class State;
class RedState;
class SilverState;
class GoldState;

// Context
class Account
{
    private:
        State* state;
        string owner;

    public:
        // Constructor
        Account(string owner);

        // Properties
        double GetBalance();
        State* GetState() { return state; }
        void SetState(State* value) { state = value; }

        void Deposit(double amount);
        void Withdraw(double amount);
        void PayInterest();
};

// State
class State
{
    protected:
        Account* account;
        State* preState;
        double balance;

        double interest;
        double lowerLimit;
        double upperLimit;

    public:
        State(State* state)
        {
            preState = state; 
        }
        ~State()
        { 
            // Clean state stack
            State* pState = this->preState;
            State* pStateTmp;
            while(pState)
            {
                pStateTmp = pState->preState;
                delete pState;
                pState = pStateTmp;
            }
        }

        // Properties
        State* GetPrestate() { return preState; }

        Account* GetAccount() { return account; }
        void SetAccount(Account* value) { account = value; }

        double GetBalance() { return balance; }
        void SetBalance(double value) { balance = value; }

        // Behaviors
        virtual void Deposit(double amount) = 0;
        virtual void Withdraw(double amount) = 0;
        virtual void PayInterest() = 0;
        virtual const char* GetName() = 0;
};

// Concrete state: Account is overdrawn
class RedState : public State
{
    private:
        double serviceFee;

        void Initialize()
        {
            // Should come from a datasource
            interest = 0.0;
            lowerLimit = -100.0;
            upperLimit = 0.0;
            serviceFee = 15.00;
        }

        void StateChangeCheck();

    public:
        // Constructor
        RedState(State* state) : State(state)
        {
            this->balance = state->GetBalance();
            this->account = state->GetAccount();
            Initialize();
        }

        void Deposit(double amount)
        {
            balance += amount;
            StateChangeCheck();
        }

        void Withdraw(double amount)
        {
            amount = amount - serviceFee;
            cout << "No funds available for withdrawal!" << endl;
        }

        void PayInterest()
        {
            // No interest is paid
        }

        const char* GetName()
        {
            return "RedState";
        }
};

// Concrete state: Silver is non-interest bearing state
class SilverState : public State
{
    // Overloaded constructors

    private:

        void Initialize()
        {
            // Should come from a datasource
            interest = 0.0;
            lowerLimit = 0.0;
            upperLimit = 1000.0;
        }

        void StateChangeCheck();

    public:
        SilverState(State* state) : State(state)
        {  
            this->balance = state->GetBalance();
            this->account = state->GetAccount();
            Initialize();
        }

        SilverState(double balance, Account* account) : State(NULL)
        {
            this->balance = balance;
            this->account = account;
            Initialize();
        }

        void Deposit(double amount)
        {
            balance += amount;
            StateChangeCheck();
        }

        void Withdraw(double amount)
        {
            balance -= amount;
            StateChangeCheck();
        }

        void PayInterest()
        {
            balance += interest * balance;
            StateChangeCheck();
        }

        const char* GetName()
        {
            return "SilverState";
        }
};

// Concrete state: Interest bearing state
class GoldState : public State
{
    private:
        void Initialize()
        {
            // Should come from a database
            interest = 0.05;
            lowerLimit = 1000.0;
            upperLimit = 10000000.0;
        }

        void StateChangeCheck();

    public:
        // Overloaded constructors
        GoldState(State* state) : State(state)
        {  
            this->balance = state->GetBalance();
            this->account = state->GetAccount();
            Initialize();
        }

        GoldState(double balance, Account* account) : State(NULL)
        {
            this->balance = balance;
            this->account = account;
            Initialize();
        }

        void Deposit(double amount)
        {
            balance += amount;
            StateChangeCheck();
        }

        void Withdraw(double amount)
        {
            balance -= amount;
            StateChangeCheck();
        }

        void PayInterest()
        {
            balance += interest * balance;
            StateChangeCheck();
        }

        const char* GetName()
        {
            return "GoldState";
        }
};

// Context
Account::Account(string owner)
{
    // New accounts are 'Silver' by default
    this->owner = owner;
    state = new SilverState(0.0, this);
}

double Account::GetBalance() { return state->GetBalance(); }

void Account::Deposit(double amount)
{
    state->Deposit(amount);
    cout << "Deposited --- " << amount << endl;
    cout << " Balance = " << this->GetBalance() << endl;
    cout << " Status = " << this->state->GetName() << endl;
    cout << endl;
}

void Account::Withdraw(double amount)
{
    state->Withdraw(amount);
    cout << "Withdrew --- " << amount << endl;
    cout << " Balance = " << this->GetBalance() << endl;
    cout << " Status = " << this->state->GetName() << endl;
    cout << endl;
}

void Account::PayInterest()
{
    state->PayInterest();
    cout << "Interest Paid --- " << endl;
    cout << " Balance = " << this->GetBalance() << endl;
    cout << " Status = " << this->state->GetName() << endl;
    cout << endl;
}



void RedState::StateChangeCheck()
{
    if (balance > upperLimit)
    {
        account->SetState(new SilverState(this));
    }
}

void SilverState::StateChangeCheck()
{
    if (balance < lowerLimit)
    {
        account->SetState(new RedState(this));
    }
    else if (balance > upperLimit)
    {
        account->SetState(new GoldState(this));
    }
}

void GoldState::StateChangeCheck()
{
    if (balance < 0.0)
    {
        account->SetState(new RedState(this));
    }
    else if (balance < lowerLimit)
    {
        account->SetState(new SilverState(this));
    }
}

// Test state pattern
int main()
{
    // Open a new account
    Account* account = new Account("Jim Johnson");

    // Apply financial transactions
    account->Deposit(500.0);
    account->Deposit(300.0);
    account->Deposit(550.0);
    account->PayInterest();
    account->Withdraw(2000.00);
    account->Withdraw(1100.00);

    // The end
    return 0;
}

