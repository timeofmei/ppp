#include "PPP.h"

int main()
{
    int num1 = 0;
    int num2 = 0;
    int smaller = 0;
    int larger = 0;
    while (cin >> num1 >> num2) {
        if (num1 < num2) {
            smaller = num1;
            larger = num2;
        } else {
            smaller = num2;
            larger = num1;
        }
        cout << "the smaller value is: " << smaller
             << "\nthe larger value is: " << larger << '\n';
    }
}