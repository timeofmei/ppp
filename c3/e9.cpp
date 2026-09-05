#include "PPP.h"

int main()
{
    int square = 1;
    int current = 1;
    int previous = 0;
    while (previous < 1000000000) {
        cout << "square: " << square << "\tcurrent: " << current
             << "\tprevious: " << previous << '\n';
        previous += current;
        ++square;
        current = 2 * current;
    }
}