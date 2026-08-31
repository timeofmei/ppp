#include "PPP.h"

int main()
{
    cout << "Enter three string values: ";
    string val1 = "";
    string val2 = "";
    string val3 = "";
    cin >> val1 >> val2 >> val3;
    string small = val1;
    string middle = val2;
    string large = val3;
    if (val1 < val2) {
        if (val1 < val3) {
            small = val1;
            if (val2 < val3) {
                middle = val2;
                large = val3;
            } else {
                middle = val3;
                large = val2;
            }
        } else {
            small = val3;
            middle = val1;
            large = val2;
        }
    } else {
        if (val1 > val3) {
            large = val1;
            if (val2 > val3) {
                middle = val2;
                small = val3;
            } else {
                middle = val3;
                small = val2;
            }
        } else {
            large = val3;
            middle = val1;
            small = val2;
        }
    }
    cout << small << ", " << middle << ", " << large << '\n';
}