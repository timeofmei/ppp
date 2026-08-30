#include "PPP.h"

int main()
{
    cout << "Enter the name of the person you want to write to and the name of another friend\n";
    string first_name;
    string friend_name;
    cin >> first_name >> friend_name;
    cout << "Dear " << first_name << ",\n"
         << "    How are you? I am fine. I miss you.\n"
         << "    Have you seen " << friend_name << " lately?\n";
}