#include "PPP.h"

int main()
{
    double num = 0;
    double smallest = numeric_limits<double>::max();
    double largest = numeric_limits<double>::lowest();
    while (cin >> num) {
        if (num <= smallest) {
            cout << num << " the smallest so far\n";
            smallest = num;
        }
        if (num >= largest) {
            cout << num << " the largest so far\n";
            largest = num;
        }
    }
}