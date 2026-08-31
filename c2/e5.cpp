#include "PPP.h"

int main()
{
    cout << "Enter two floating-point values: ";
    double val1 = 0;
    double val2 = 0;
    cin >> val1 >> val2;
    if (val1 < val2)
        cout << "smaller: " << val1 << '\n'
             << "larger: " << val2 << '\n';
    else
        cout << "smaller: " << val2 << '\n'
             << "larger: " << val1 << '\n';
    cout << "sum: " << val1 + val2 << '\n'
         << "difference: " << val1 - val2 << '\n'
         << "product: " << val1 * val2 << '\n'
         << "ratio: " << val1 / val2 << '\n';
}