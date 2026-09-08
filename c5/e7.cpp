#include "PPP.h"

void print_digits(vector<int> digits)
{
    if (digits.empty())
        return;
    int result = 0;
    for (int digit : digits) {
        result *= 10;
        result += digit;
    }
    cout << result << " is ";
    size_t pos = 0;
    if (digits.size() - pos == 4) {
        cout << digits[pos] << " thousand";
        if (digits[pos] != 1) {
            cout << 's';
        }
        cout << " and ";
        ++pos;
    }
    if (digits.size() - pos == 3) {
        cout << digits[pos] << " hundred";
        if (digits[pos] != 1) {
            cout << 's';
        }
        cout << " and ";
        ++pos;
    }
    if (digits.size() - pos == 2) {
        cout << digits[pos] << " ten";
        if (digits[pos] != 1) {
            cout << 's';
        }
        cout << " and ";
        ++pos;
    }
    if (digits.size() - pos == 1) {
        cout << digits[pos] << " one";
        if (digits[pos] != 1) {
            cout << 's';
        }
        cout << '\n';
    }
}

int main()
{
    vector<int> digits = {};
    char buffer = 0;
    while (cin >> buffer) {
        switch (buffer) {
        case '=':
            print_digits(digits);
            digits.clear();
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if (digits.size() < 4)
                digits.push_back(buffer - '0');
            break;
        default:
            error("Bad token");
        }
    }
}