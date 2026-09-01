#include "PPP.h"

int main()
{
    constexpr double dollar_per_yen = 0.0063;
    constexpr double dollar_per_kroner = 0.11;
    constexpr double dollar_per_pounds = 1.35;
    constexpr double dollar_per_swiss_francs = 1.24;
    double money = 0;
    char currency = ' ';
    cout << "Please enter an amount of money followed by a currency (y, k, p or s):\n";
    cin >> money >> currency;
    switch (currency) {
        case 'y':
            cout << money << " yen == " << money * dollar_per_yen << " dollar\n";
            break;
        case 'k':
            cout << money << " kroner == " << money * dollar_per_kroner << " dollar\n";
            break;
        case 'p':
            cout << money << " pounds == " << money * dollar_per_pounds << " dollar\n";
            break;
        case 's':
            cout << money << " Swiss francs == " << money * dollar_per_swiss_francs << " dollar\n";
            break;
        default:
            cout << "Sorry, I don't know a currency called " << currency << '\n';
            break;
    }
}