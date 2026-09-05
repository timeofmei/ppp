#include "PPP.h"

int main()
{
    int square = 1;
    double current = 1;
    double previous = 0;
    while (square <= 64) {
        cout << "square: " << square << "\tcurrent: " << current
             << "\tprevious: " << previous << '\n';
        previous += current;
        ++square;
        current = 2 * current;
    }
}