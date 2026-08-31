#include "PPP.h"

int main()
{
    string input = "";
    while (cin >> input) {
        if (input == "zero")
            cout << 0;
        if (input == "one")
            cout << 1;
        if (input == "two")
            cout << 2;
        if (input == "three")
            cout << 3;
        if (input == "four")
            cout << 4;
        if (input != "zero" && input != "one" && input != "two" && input != "three" && input != "four")
            cout << "stupid number!";
        cout << '\n';
    }
}