#include "PPP.h"

int main()
{
    vector<double> distances = {};
    double temp = 0;
    double sum = 0;
    while (cin >> temp) {
        distances.push_back(temp);
        sum += temp;
    }
    ranges::sort(distances);
    if (distances.size() > 0) {
        cout << "smallest distance: " << distances[0] << '\n';
        cout << "greatest distance: " << distances[distances.size() - 1] << '\n';
        cout << "mean distance: " << sum / distances.size() << '\n';
    }
}