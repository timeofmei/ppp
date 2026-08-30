#include "PPP.h"

int main()
{
    cout << "Please enter an int value: ";
    int n = 0;
    cin >> n;
    cout << "n == " << n
         << "\nn+1 == " << n + 1
         << "\nthree times n == " << 3 * n
         << "\ntwice n == " << n + n
         << "\nsquared == " << n * n
         << "\nhalf of n == " << n / 2
         << "\nsquare root of n == " << sqrt(n)
         << "\nremainder 2 of n == " << n % 2
         << '\n';
}