#include "PPP.h"

int main()
{
    string operation = "";
    double operand1 = 0.0;
    double operand2 = 0.0;
    double result = 0.0;
    while (cin >> operation >> operand1 >> operand2) {
        if (operation == "+" || operation == "plus")
            result = operand1 + operand2;
        if (operation == "-" || operation == "minus")
            result = operand1 - operand2;
        if (operation == "*" || operation == "mul")
            result = operand1 * operand2;
        if (operation == "/" || operation == "div")
            result = operand1 / operand2;
        cout << result << '\n';
    }

}