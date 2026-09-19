#include "PPP.h"

int main()
{
    vector<string> name;
    string temp_name;
    for (int i = 0; i < 5; ++i) {
        cin >> temp_name;
        name.push_back(temp_name);
    }
    vector<double> age;
    int temp_age;
    for (int i = 0; i < 5; ++i) {
        cout << "age of " << name[i] << ": ";
        cin >> temp_age;
        age.push_back(temp_age);
    }
    for (int i = 0; i < 5; ++i) {
        cout << "(" << name[i] << ", " << age[i] << ")\n";
    }
    vector<string> name_copy = name;
    sort(name.begin(), name.end());
    vector<double> age_copy = age;
    for (int i = 0; i < name.size(); ++i) {
        for (int j = 0; j < name.size(); ++j) {
            if (name[i] == name_copy[j]) {
                age[i] = age_copy[j];
                break;
            }
        }
    }
    cout << "sorted:\n";
        for (int i = 0; i < 5; ++i) {
        cout << "(" << name[i] << ", " << age[i] << ")\n";
    }
}
