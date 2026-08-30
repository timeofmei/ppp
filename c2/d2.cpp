#include "PPP.h"

int main()
{
    cout << "Enter the name of the person you want to write to \n";
    string first_name;
    cin >> first_name;
    cout << "Dear " << first_name << ",\n"
         << "    How are you? I am fine. I miss you.\n";
}