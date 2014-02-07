#include <vector>
#include <iostream>
using namespace std;

// "Context"
class Context
{
private:
    string input;
    int output;

public:
    Context( const string& input ) : input(input), output(0) { }
    friend class Expression;
    friend ostream& operator << (ostream& os, Context& context)
    {
        return os << context.output;
    }
};

// "AbstractExpression"
class Expression
{
public :
    // Template Method
    void Interpret( Context& context )
    {
        string& input = context.input;
        int& output = context.output;

        if (0 == input.length()) return;
        if (input.find(Nine()) == 0)
        {
            output += 9 * Multiplier();
            input = input.substr(2, input.length() - 2);
        }
        else if (input.find(Four()) == 0)
        {
            output += 4 * Multiplier();
            input = input.substr(2, input.length() - 2);
        }
        else if (input.find(Five()) == 0)
        {
            output += 5 * Multiplier();
            input = input.substr(1, input.length() - 1);
        }
        while (input.find(One()) == 0)
        {
            output += Multiplier();
            input = input.substr(1, input.length() - 1);
        }
    }

    virtual const char* One() = 0;
    virtual const char* Four() = 0;
    virtual const char* Five() = 0;
    virtual const char* Nine() = 0;
    virtual int Multiplier() = 0;
};

// Thousand checks for the Roman Numeral M
// "TerminalExpression"
class ThousandExpression : public Expression
{
    // Methods
    const char* One() { return "M"; }
    const char* Four(){ return " "; }
    const char* Five(){ return " "; }
    const char* Nine(){ return " "; }
    int Multiplier() { return 1000; }
};

// Hundred checks C, CD, D or CM
// "TerminalExpression"
class HundredExpression : public Expression
{
    // Methods
    const char* One() { return "C"; }
    const char* Four(){ return "CD"; }
    const char* Five(){ return "D"; }
    const char* Nine(){ return "CM"; }
    int Multiplier() { return 100; }
};

// Ten checks for X, XL, L and XC
// "TerminalExpression"
class TenExpression : public Expression
{
    // Methods
    const char* One() { return "X"; }
    const char* Four(){ return "XL"; }
    const char* Five(){ return "L"; }
    const char* Nine(){ return "XC"; }
    int Multiplier() { return 10; }
};

// One checks for I, II, III, IV, V, VI, VII, VIII, IX
// "TerminalExpression"
class OneExpression : public Expression
{
    // Methods
    const char* One() { return "I"; }
    const char* Four(){ return "IV"; }
    const char* Five(){ return "V"; }
    const char* Nine(){ return "IX"; }
    int Multiplier() { return 1; }
};

int main()
{
    string roman("MCMXXVIII");
    Context context(roman);

    // Build the ''''parse tree''''
    Expression* exp[] = {
        new ThousandExpression(), new HundredExpression(),
        new TenExpression(), new OneExpression()};
    vector<Expression*> v_exp(exp, exp + sizeof(exp) / sizeof(Expression*));
    vector<Expression*>::iterator it = v_exp.begin();
    for (; it != v_exp.end(); it++)
    {
        (*it)->Interpret(context);
        delete (*it);
    }

    cout << roman.c_str() << "=" << context << endl;
}

