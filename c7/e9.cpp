#include "PPP.h"

double weighted_price(const vector<double>& price, const vector<double>& weight)
{
    double result = 0;
    if(price.size() != weight.size())
        error("price size != weight size");
    for (int i = 0; i < price.size(); ++i)
        result += price[i] * weight[i];
    return result;
}

int main()
{
    vector<double> price = {10, 20, 30, 40, 50};
    vector<double> weight = {0.3, 0.5, 0.1, 0.02, 0.08};
    cout << "weighted price: " << weighted_price(price, weight) << '\n';
}