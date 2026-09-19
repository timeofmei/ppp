#include "PPP.h"

void print(string label, vector<string> &vec)
{
    cout << label << ": ";
    for (string s : vec)
        cout << s << ' ';
    cout << '\n';
}

void swap(string &a, string &b)
{
    string temp = a;
    a = b;
    b = temp;
}

vector<string> reverse_string(const vector<string> &vec)
{
    vector<string> result;
    for (int i = vec.size(); i > 0; --i)
        result.push_back(vec[i-1]);
    return result;
}

void reverse_string_inplace(vector<string> &vec)
{
    for (int i = 0; i < vec.size() / 2; ++i)
        swap(vec[i], vec[vec.size()-1-i]);
}

int main()
{
    vector<string> vec1 {"a", "bc", "def", "ghij", "klmno"};
    print("vec1", vec1);
    vector<string> vec2 = reverse_string(vec1);
    print("vec2", vec2);
    print("vec1", vec1);
    reverse_string_inplace(vec1);
    print("vec1", vec1);
}