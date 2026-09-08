#include "PPP.h"

int factorial(int x)
{
    if (x < 0)
        error("factorial should >= 0");
    int result = 1;
    while (x > 0) {
        result *= x;
        --x;
    }
    return result;
}

int permutation(int a, int b) { return factorial(a) / factorial(a - b); }

int combination(int a, int b) { return permutation(a, b) / factorial(b); }

int main()
{
    try {
        int a;
        int b;
        char choice;
        cout << "Enter a and b: ";
        if (!(cin >> a >> b))
            error("a and b must be integers");
        cout << "Calculate permutation(p) or combination(c)? ";
        if (!(cin >> choice))
            error("choice must be p or c");
        switch (choice) {
        case 'p':
            cout << "P(a, b) = " << permutation(a, b) << '\n';
            break;
        case 'c':
            cout << "C(a, b) = " << combination(a, b) << '\n';
            break;
        default:
            error("not p or c");
            break;
        }
    } catch (exception &e) {
        cerr << e.what() << '\n';
    }
}