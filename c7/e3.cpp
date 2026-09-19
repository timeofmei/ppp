#include "PPP.h"

void print(string label, vector<int> &vec)
{
    cout << label << ": ";
    for (int i : vec)
        cout << i << ' ';
    cout << '\n';
}

void fibonacci(int x, int y, vector<int> &result, int n)
{
    result.push_back(x);
    result.push_back(y);
    for (int i = 2; i < n; ++i) {
        result.push_back(result[i-1] + result[i-2]);
    }
}

int main()
{
    string label = "fibonacci numbers";
    vector<int> vec;
    fibonacci(-1, -2, vec, 10);
    print(label, vec);
}
