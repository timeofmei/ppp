#include "PPP.h"

int main()
{
    cout << "Enter the name of the person you want to write to and the name of another friend\n";
    string first_name;
    string friend_name;
    cin >> first_name >> friend_name;
    cout << "Enter the age of the recipient\n";
    int age;
    cin >> age;
    cout << "Dear " << first_name << ",\n"
         << "    How are you? I am fine. I miss you.\n"
         << "    Have you seen " << friend_name << " lately?"
         << " I hear you just had a birthday and you are " << age << " years old.";
    if (age <= 0 || age >= 110)
        error("you're kidding!\n");
    if (age < 12)
        cout << " Next year you will be " << age + 1 << ".\n";
    if (age == 17)
        cout << " Next year you will be able to vote.\n";
    if (age > 70)
        cout << " Are you retired?\n";
    cout << "Yours sincerely,\n\n\ntimeofmei\n";
}