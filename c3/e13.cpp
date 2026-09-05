#include "PPP.h"

int main()
{
    vector<char> is_primes(101, 1);
    is_primes[1] = 0;
    for (size_t p = 2; p < is_primes.size();) {
        for (size_t n = 2; n * p < is_primes.size(); ++n)
            is_primes[n * p] = 0;
        do {
            ++p;
        } while (p < is_primes.size() && is_primes[p] == 0);
    }
    for (size_t p = 1; p < is_primes.size(); ++p)
        if (is_primes[p] == 1)
            cout << p << '\n';
}