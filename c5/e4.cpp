#include "PPP.h"

class Name_value {
  public:
    string name;
    int value;
    Name_value(string name, int value) : name{name}, value{value} {}
};

int main()
{
    vector<Name_value> vec = {};
    string name;
    int value;
    while (cin >> name >> value) {
        Name_value temp {name, value};
        if (name == "NoName" && value == 0)
            break;
        for (Name_value current : vec) {
            if (name == current.name) {
                cout << "Error: name " << name << " is entered twice.\n";
                exit(1);
            }
        }
        vec.push_back(temp);
    }

    cout << "Enter a value:\n";
    while (cin >> value) {
        bool found = false;
        for (size_t i = 0; i < vec.size(); ++i) {
            if (value == vec[i].value) {
                found = true;
                cout << vec[i].name << '\n';
            }
        }
        if (!found)
            cout << "score not found\n";
    }
}