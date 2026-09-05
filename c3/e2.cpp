#include "PPP.h"

int main()
{
    string str = "";
    while (cin >> str) {
        for (char c : str) {
            cout << c << ' ' << int(c) << '\n';
        }
    }
}