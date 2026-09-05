#include "PPP.h"

int main()
{
    size_t n = 0;
    int i = 2;
    vector<int> primes = {2};
    bool is_prime = true;
    cout << "Enter n: ";
    cin >> n;
    while (primes.size() < n) {
        i++;
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