#include "PPP.h"

void print(string label, vector<int> &vec)
{
    cout << label << ": ";
    for (int i : vec)
        cout << i << ' ';
    cout << '\n';
}

int main()
{
    string label = "my numbers";
    vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    print(label, vec);
}
