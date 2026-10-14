#include "PPP.h"

class Name_pairs {
public:
    void read_names();
    void read_ages();
    void print();
    void sort();

private:
    vector<string> name;
    vector<double> age;
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

void Name_pairs::print()
{
    for (int i = 0; i < name.size(); ++i) {
        cout << '(' << name[i] << ", " << age[i] << ")\n";
    }
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

int main()
{
    Name_pairs name_pairs;
    cout << "Names:\n";
    name_pairs.read_names();
    cout << "Ages:\n";
    name_pairs.read_ages();
    cout << "Before sort:\n";
    name_pairs.print();
    cout << "After sort:\n";
    name_pairs.sort();
    name_pairs.print();
}