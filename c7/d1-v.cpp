#include "PPP.h"

void swap_v(int a, int b)
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
    swap_v(x, y);
    cout << x << ' ' << y << '\n';
    swap_v(7, 9);
    const int cx = 7;
    const int cy = 9;
    swap_v(cx, cy);
    cout << cx << ' ' << cy << '\n';
    swap_v(7.7, 9.9);
    double dx = 7.7;
    double dy = 9.9;
    swap_v(dx, dy);
    cout << dx << ' ' << dy << '\n';
    swap_v(7.7, 9.9);
}