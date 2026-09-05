#include "PPP.h"

int main()
{
    string mode = "";
    int max_times = 0;
    vector<string> strings = {};
    string temp = "";
    while (cin >> temp) {
        strings.push_back(temp);
    }
    ranges::sort(strings);
    for (size_t i = 0; i < strings.size();) {
        int times = 1;
        while (i + times < strings.size() && strings[i + times] == strings[i])
            ++times;
        if (times > max_times) {
            max_times = times;
            mode = strings[i];
        }
        i += times;
    }
    cout << "min: " << strings[0] << '\n';
    cout << "max: " << strings[strings.size() - 1] << '\n';
    cout << "mode: " << mode << '\n';
}