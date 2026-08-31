#include "PPP.h"

int main()
{
    int pennies = 0;
    int nickles = 0;
    int dimes = 0;
    int quarters = 0;
    int half_dollars = 0;
    int coins = 0;
    int sum = 0;
    cout << "How many pennies do you have? ";
    cin >> pennies;
    cout << "How many nickles do you have? ";
    cin >> nickles;
    cout << "How many dimes do you have? ";
    cin >> dimes;
    cout << "How many quarters do you have? ";
    cin >> quarters;
    cout << "How many half_dollars do you have? ";
    cin >> half_dollars;
    cout << "How many coins do you have? ";
    cin >> coins;
    sum = 1 * pennies + 5 * nickles + 10 * dimes + 25 * quarters + 50 * half_dollars + 100 * coins;
    cout << "You have " << pennies << " penn";
    if (pennies == 1)
        cout << "y.\n";
    else
        cout << "ies.\n";
    cout << "You have " << nickles << " nickle";
    if (nickles == 1)
        cout << ".\n";
    else
        cout << "s.\n";
    cout << "You have " << dimes << " dime";
    if (dimes == 1)
        cout << ".\n";
    else
        cout << "s.\n";
    cout << "You have " << quarters << " quarter";
    if (quarters == 1)
        cout << ".\n";
    else
        cout << "s.\n";
    cout << "You have " << half_dollars << " half dollar";
    if (half_dollars == 1)
        cout << ".\n";
    else
        cout << "s.\n";
    cout << "The value of all your coins is " << sum / 100 << " dollar";
    if (sum / 100 == 1)
        cout << "";
    else
        cout << "s";
    cout << " and " << sum % 100 << " cent";
    if (sum % 100 == 1)
        cout << ".\n";
    else
        cout << "s.\n";
}