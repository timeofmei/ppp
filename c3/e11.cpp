#include "PPP.h"

int main()
{
    const vector<string> type = {"rock", "paper", "scissors"};
    string player1 = "";
    string player2 = "";
    int p1 = 0;
    int p2 = 0;
    cout << "Enter rock, paper or scissors for player 1: ";
    cin >> player1;
    cout << "Enter rock, paper or scissors for player 2: ";
    cin >> player2;
    for (size_t i = 0; i < type.size(); ++i) {
        if (type[i] == player1)
            p1 = i;
        if (type[i] == player2)
            p2 = i;
    }
    if ((p2 + 1) % 3 == p1) {
        cout << "Player 1 wins.\n";
    } else if ((p1 + 1) % 3 == p2) {
        cout << "Player 2 wins.\n";
    } else {
        cout << "No one wins.\n";
    }
}