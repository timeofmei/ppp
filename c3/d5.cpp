#include "PPP.h"

int main()
{
    double num1 = 0;
    double num2 = 0;
    double smaller = 0;
    double larger = 0;
    while (cin >> num1 >> num2) {
        if (num1 == num2) {
            cout << "the numbers are equal\n";
        } else {
            if (num1 < num2) {
                smaller = num1;
                larger = num2;
            } else {
                smaller = num2;
                larger = num1;
            }
            cout << "the smaller value is: " << smaller
                 << "\nthe larger value is: " << larger << '\n';
            if (larger - smaller < 1.0 / 100)
                cout << "the numbers are almost equal\n";
        }
    }
}