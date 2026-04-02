#include <iostream>
#include <string>
#include <stack>
using namespace std;

int getPrecedence(char op) 
{
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2;
    return 0;
}

double applyOperation(double a, double b, char op) 
{
    switch (op)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if(b == 0) {
                cout << "Error: Division by zero!" << endl;
                return 0;
            }
            return a / b;
    }
    return 0;
}

double evaluateExpression(string expr)
{
    stack<double> values;
    stack<char> operators;

    for(int i = 0; i < expr.size(); i++)
    {
        if(expr[i] == ' ') continue;

        if(expr[i] >= '0' && expr[i] <= '9') 
        {
            double val = 0;
            while(i < expr.length() && expr[i] >= '0' && expr[i] <= '9')
            {
                val = val * 10 + (expr[i] - '0');
                i++;
            }
            values.push(val);
            i--; 
        }

        else if(expr[i] == '(')
        {
            operators.push(expr[i]);
        }
        
        else if(expr[i] == ')') 
        {
            while(!operators.empty() && operators.top() != '(')
            {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                values.push(applyOperation(a, b, op));
            }
            if(!operators.empty()) operators.pop();
        }

        else  
        {
            while(!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(expr[i]))
            {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                values.push(applyOperation(a, b, op));
            }
            operators.push(expr[i]); 
        }
    }

    while(!operators.empty())
    {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char op = operators.top(); operators.pop();
        values.push(applyOperation(a, b, op));
    }

    return values.top();
}

int main()
{
    string expression;
    cout << "Enter expression: " << endl;
    getline(cin, expression);

    cout << "Result: " << evaluateExpression(expression) << endl;
    
    return 0;
}
