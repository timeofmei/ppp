#include "PPP.h"

int main()
{
    cout << "Enter three integer values: ";
    int val1 = 0;
    int val2 = 0;
    int val3 = 0;
    cin >> val1 >> val2 >> val3;
    int small = val1;
    int middle = val2;
    int large = val3;
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