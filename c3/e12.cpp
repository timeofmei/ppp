#include "PPP.h"

int main()
{
    vector<int> primes = {2};
    bool is_prime = true;
    for (int i = 3; i <= 100; ++i) {
        is_prime = true;
        for (int prime : primes) {
            if (i % prime == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime)
            primes.push_back(i);
    }
    for (int prime : primes)
        cout << prime << '\n';
}