#include "PPP.h"

int main()
{
    const vector<string> spell_outs_and_digits = {"zero", "one", "two",   "three", "four",
                                       "five", "six", "seven", "eight", "nine", "0", "1", "2", "3", "4",
                                   "5", "6", "7", "8", "9"};
    const vector<string> digits = {};
    string val1 = "";
    string val2 = "";
    int num1 = 0;
    int num2 = 0;
    char operation = 0;
    cout << "Enter two digits or spelled out values and a character to represent an "
            "opration.\n";
    while (cin >> val1 >> val2 >> operation) {
        for (size_t i = 0; i < spell_outs_and_digits.size(); ++i) {
            if (spell_outs_and_digits[i] == val1)
                    num1 = i % 10;
            if (spell_outs_and_digits[i] == val2)
                    num2 = i % 10;
        }
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