#include "PPP.h"

int main()
{
    vector<string> names = {};
    vector<int> values = {};
    string name;
    int value;
    while (cin >> name >> value) {
        if (name == "NoName" && value == 0)
            break;
        for (string current : names) {
            if (name == current) {
                cout << "Error: name " << name << " is entered twice.\n";
                exit(1);
            }
        }
        names.push_back(name);
        values.push_back(value);
    }
    for (size_t i = 0; i < names.size(); ++i) {
        cout << "(" << names[i] << ", " << values[i] << ")\n";
    }
}