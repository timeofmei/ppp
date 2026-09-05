#include "PPP.h"

int main()
{
    double num1 = 0;
    double num2 = 0;
    char operation = 0;
    cout << "Enter two double values and a character to represent an "
            "opration.\n";
    while (cin >> num1 >> num2 >> operation) {
        switch (operation) {
        case '+':
            cout << "The sum of " << num1 << " and " << num2 << " is "
                 << num1 + num2 << ".\n";
            break;
        case '-':
            cout << "The subtract of " << num1 << " and " << num2 << " is "
                 << num1 - num2 << ".\n";
            break;
        case '*':
            cout << "The multiply of " << num1 << " and " << num2 << " is "
                 << num1 * num2 << ".\n";
            break;
        case '/':
            cout << "The divide of " << num1 << " and " << num2 << " is "
                 << num1 / num2 << ".\n";
            break;
        default:
            cout << "Unknown operation " << operation << ".\n";
            break;
        }
    }
}