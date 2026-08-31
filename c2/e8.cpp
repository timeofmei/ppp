#include "PPP.h"

int main()
{
    cout << "Type an integer: ";
    int number = 0;
    cin >> number;
    if (number % 2 == 0)
        cout << "The value " << number << " is an even number\n";
    else
        cout << "The value " << number << " is an odd number\n";
}