#include "PPP.h"

class Name_pairs {
public:
    vector<string> name;
    vector<double> age;
    void read_names();
    void read_ages();
    void sort();
};

void Name_pairs::read_names()
{
    string s;
    while (cin >> s && s != "end") {
        name.push_back(s);
    }
}

void Name_pairs::read_ages()
{
    double d;
    for (string s : name) {
        cout << "Enter the age of " << s << ": ";
        cin >> d;
        age.push_back(d);
    }
}

ostream& operator<<(ostream& os, Name_pairs name_pairs)
{
    for (int i = 0; i < name_pairs.name.size(); ++i) {
        os << '(' << name_pairs.name[i] << ", " << name_pairs.age[i] << ")\n"; 
    }
    return os;
}

void Name_pairs::sort()
{
    vector<string> original_name = name;
    vector<double> original_age = age;
    ranges::sort(name);
    for (int i = 0; i < name.size(); ++i) {
        for (int j = 0; j < original_name.size(); ++j) {
            if (name[i] == original_name[j]) {
                age[i] = original_age[j];
                break;
            }
        }
    }
}

bool operator==(Name_pairs name_pairs1, Name_pairs name_pairs2)
{
    return name_pairs1.name == name_pairs2.name && name_pairs1.age == name_pairs2.age;
}

bool operator!=(Name_pairs name_pairs1, Name_pairs name_pairs2)
{
    return !(name_pairs1 == name_pairs2);
}

int main()
{
    Name_pairs name_pairs;
    cout << "Names:\n";
    name_pairs.read_names();
    cout << "Ages:\n";
    name_pairs.read_ages();
    cout << "Before sort:\n";
    cout << name_pairs;
    cout << "After sort:\n";
    name_pairs.sort();
    cout << name_pairs;
}