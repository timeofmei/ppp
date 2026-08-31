#include "PPP.h"

int main()
{
    cout << "Type a number of miles: ";
    double miles = 0;
    cin >> miles;
    cout << miles << " miles == " << miles * 1.609 << " kilometers.\n";
}