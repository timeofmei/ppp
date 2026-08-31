#include "PPP.h"

int main()
{
    cout << "Enter two integer values: ";
    int val1 = 0;
    int val2 = 0;
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