#include "PPP.h"

int main()
{
    double a = 0;
    double b = 0;
    double c = 0;
    double x1 = 0;
    double x2 = 0;
    cout << "Enter a, b, and c: ";
    cin >> a >> b >> c;
    if (a == 0) {
        if (b == 0)
            exit(1);
        x1 = -c / b;
        x2 = x1;
    } else {
        double delta = b * b - 4 * a * c;
        if (delta >= 0) {
            x1 = (b + sqrt(delta)) / (-2 * a);
            x2 = (b - sqrt(delta)) / (-2 * a);
        } else {
            exit(-1);
        }
    }
    cout << "x1: " << x1 << "\nx2: " << x2 << '\n';
}