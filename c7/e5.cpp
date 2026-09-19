#include "PPP.h"

void print(string label, vector<int> &vec)
{
    cout << label << ": ";
    for (int i : vec)
        cout << i << ' ';
    cout << '\n';
}

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

vector<int> reverse_int(const vector<int> &vec)
{
    vector<int> result;
    for (int i = vec.size(); i > 0; --i)
        result.push_back(vec[i-1]);
    return result;
}

void reverse_int_inplace(vector<int> &vec)
{
    for (int i = 0; i < vec.size() / 2; ++i)
        swap(vec[i], vec[vec.size()-1-i]);
}

int main()
{
    vector<int> vec1 {1, 2, 3, 4, 5};
    print("vec1", vec1);
    vector<int> vec2 = reverse_int(vec1);
    print("vec2", vec2);
    print("vec1", vec1);
    reverse_int_inplace(vec1);
    print("vec1", vec1);
}