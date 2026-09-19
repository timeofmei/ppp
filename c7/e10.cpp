#include "PPP.h"

int maxv(const vector<int> &vec)
{
    if (vec.empty())
        error("vec empty");
    int result = vec[0];
    for (int num : vec)
        if (num > result)
            result = num;
    return result;
}

int main()
{
    vector<int> vec{};
    cout << "max: " << maxv(vec) << '\n';
}