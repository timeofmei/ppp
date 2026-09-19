#include "PPP.h"

int main()
{
    int i = 1001;
    double d = 7.7;
    char c = 'x';

    int int_d = d;
    int int_c = c;
    double double_i = i;
    double double_c = c;
    char char_i = i;
    char char_d = d;

    // int narrow_int_d = narrow<int>(d);
    int narrow_int_c = narrow<int>(c);
    double narrow_double_i = narrow<double>(i);
    double narrow_double_c = narrow<double>(c);
    // char narrow_char_i = narrow<char>(i);
    // char narrow_char_d = narrow<char>(d);

    cout << "i = " << i << '\n';
    cout << "d = " << d << '\n';
    cout << "c = " << c << '\n';
    cout << "int_d = " << int_d << '\n';
    cout << "int_c = " << int_c << '\n';
    cout << "double_i = " << double_i << '\n';
    cout << "double_c = " << double_c << '\n';
    cout << "char_i = " << char_i << '\n';
    cout << "char_d = " << char_d << '\n';
    // cout << "narrow_int_d = " << narrow_int_d << '\n';
    cout << "narrow_int_c = " << narrow_int_c << '\n';
    cout << "narrow_double_i = " << narrow_double_i << '\n';
    cout << "narrow_double_c = " << narrow_double_c << '\n';
    // cout << "narrow_char_i = " << narrow_char_i << '\n';
    // cout << "narrow_char_d = " << narrow_char_d << '\n';
}
