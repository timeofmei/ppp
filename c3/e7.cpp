#include "PPP.h"

int main()
{
    const vector<string> spell_outs = {"zero", "one", "two",   "three", "four",
                                       "five", "six", "seven", "eight", "nine"};
    char mode = 0;
    int digit_input = 0;
    string spelled_out_input = "";
    cout << "Enter a character (d for digit, s for spelled-out) and the "
            "value:\n";
    while (cin >> mode) {
        switch (mode) {
        case 'd':
            cin >> digit_input;
            if (digit_input >= 0 && digit_input <= 9)
                cout << spell_outs[digit_input] << '\n';
            break;
        case 's':
            cin >> spelled_out_input;
            for (size_t i = 0; i < spell_outs.size(); ++i) {
                if (spell_outs[i] == spelled_out_input)
                    cout << i << '\n';
            }
            break;
            cin >> spelled_out_input;
            cout << "Unknown mode: " << mode << '\n';
            break;
        }
    }
}