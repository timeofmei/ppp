#include "PPP.h"

int main()
{
    double num = 0;
    double length = 0;
    string unit = "";
    double smallest = numeric_limits<double>::max();
    double largest = numeric_limits<double>::lowest();
    while (cin >> num >> unit) {
        if (unit == "cm") {
            length = num / 100;
        } else if (unit == "m") {
            length = num;
        } else if (unit == "in") {
            length = num * 2.54 / 100;
        } else if (unit == "ft") {
            length = num * 12 * 2.54 / 100;
        } else {
            cout << "illegal unit: " << unit << '\n';
            continue;
        }
        if (length <= smallest) {
            cout << num << unit << " the smallest so far\n";
            smallest = length;
        }
        if (length >= largest) {
            cout << num << unit << " the largest so far\n";
            largest = length;
        }
    }
}