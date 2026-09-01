#include "PPP.h"

int main()
{
    vector<string> disliked {"Broccoli", "Shigoto", "Tabacco"};
    for (string temp; cin >> temp;) {
        string output = temp;
        for (string disliked_temp : disliked) {
            if (temp == disliked_temp)
                output = "BLEEP";
        }
        cout << output << '\n';
    }
}
