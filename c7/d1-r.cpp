#include "PPP.h"

void swap_r(int& a, int& b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

int main()
{
    int x = 7;
    int y = 9;
    swap_r(x, y);
    cout << x << ' ' << y << '\n';
    // swap_r(7, 9);
    const int cx = 7;
    const int cy = 9;
    // swap_r(cx, cy);
    // swap_r(7.7, 9.9);
    double dx = 7.7;
    double dy = 9.9;
    // swap_r(dx, dy);
    // swap_r(7.7, 9.9);
}