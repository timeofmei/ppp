#include "PPP.h"

int main()
{
    constexpr double dollar_per_yen = 0.0063;
    constexpr double dollar_per_kroner = 0.11;
    constexpr double dollar_per_pounds = 1.35;
    double money = 0;
    char currency = ' ';
    cout << "Please enter an amount of money followed by a currency (y, k or p):\n";
    cin >> money >> currency;
    if (currency == 'y')
        cout << money << " yen == " << money * dollar_per_yen << " dollar\n";
    else if (currency == 'k')
        cout << money << " kroner == " << money * dollar_per_kroner << " dollar\n";
    else if (currency == 'p')
        cout << money << " pounds == " << money * dollar_per_pounds << " dollar\n";
    else
        cout << "Sorry, I don't know a currency called " << currency << '\n';
}