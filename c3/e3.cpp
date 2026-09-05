#include "PPP.h"

int main()
{
    vector<double> temps;
    double median;
    for (double temp; cin >> temp;)
        temps.push_back(temp);

    ranges::sort(temps);
    if (temps.size() % 2 == 1)
        median = temps[temps.size() / 2];
    else
        median = (temps[temps.size() / 2 - 1] + temps[temps.size() / 2]) / 2;
    cout << "Median temperature: " << median << '\n';
}