#include "PPP.h"

int main()
{
    double num = 0;
    double length = 0;
    double sum = 0;
    int num_entered = 0;
    vector<double> values = {};
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
        sum += length;
        ++num_entered;
        values.push_back(length);
    }
    cout << "smallest: " << smallest << "m\n";
    cout << "largest: " << largest << "m\n";
    cout << "number of values: " << num_entered << '\n';
    cout << "sum of values: " << sum << "m\n";
    ranges::sort(values);
    for (double value : values) {
        cout << value << "m\n";
    }
}