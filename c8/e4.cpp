#include "PPP.h"

struct Name_pair {
    string name = "";
    double age = 0.0;
    Name_pair(string s, double d)
        :name{s}, age{d}
    {}
    Name_pair(string s)
        :name{s}
    {}
};

class Name_pairs {
public:
    vector<Name_pair> values;
    void read_names();
    void read_ages();
    void sort();
};

void Name_pairs::read_names()
{
    string s;
    while (cin >> s && s != "end") {
        values.push_back(Name_pair{s});
    }
}

void Name_pairs::read_ages()
{
    for (Name_pair& name_pair : values) {
        cout << "Enter the age of " << name_pair.name << ": ";
        cin >> name_pair.age;
    }
}

ostream& operator<<(ostream& os, Name_pairs name_pairs)
{
    for (int i = 0; i < name_pairs.values.size(); ++i) {
        os << '(' << name_pairs.values[i].name << ", " << name_pairs.values[i].age << ")\n"; 
    }
    return os;
}

bool operator==(Name_pair name_pair1, Name_pair name_pair2)
{
    return name_pair1.name == name_pair2.name && name_pair1.age == name_pair2.age;
}

bool operator==(Name_pairs name_pairs1, Name_pairs name_pairs2)
{
    return name_pairs1.values == name_pairs2.values;
}

bool operator!=(Name_pairs np1, Name_pairs np2)
{
    return !(np1 == np2);
}

void Name_pairs::sort()
{
    ranges::sort(values, {}, &Name_pair::name);
}

int main()
{
    Name_pairs np;
    cout << "Names:\n";
    np.read_names();
    cout << "Ages:\n";
    np.read_ages();
    cout << "Before sort:\n";
    cout << np;
    cout << "After sort:\n";
    np.sort();
    cout << np;
}