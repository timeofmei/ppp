#include "PPP.h"

int main()
{
    int min = 1;
    int max = 100;
    int guess = 0;
    char answer = 0;
    cout << "Think of a number between " << min << " and " << max << ".\n";
    while (min < max) {
        guess = (min + max) / 2;
        cout << "Is the number you are thinking of <= " << guess << "? (y/n) ";
        cin >> answer;
        switch (answer) {
        case 'y':
            max = guess;
            break;
        case 'n':
            min = guess + 1;
            break;
        default:
            cout << "Please enter y or n\n";
            break;
        }
    }
    cout << "The number you are thinking of is " << min << ".\n";
}