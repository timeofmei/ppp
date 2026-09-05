#include "PPP.h"

int main()
{
    int mode = 0;
    int max_times = 0;
    vector<int> numbers = {};
    int number = 0;
    while (cin >> number) {
        numbers.push_back(number);
    }
    ranges::sort(numbers);
    for (size_t i = 0; i < numbers.size();) {
        int times = 1;
        while (i + times < numbers.size() && numbers[i + times] == numbers[i])
            ++times;
        if (times > max_times) {
            max_times = times;
            mode = numbers[i];
        }
        i += times;
    }
    cout << "mode: " << mode << '\n';
}