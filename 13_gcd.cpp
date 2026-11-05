#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <limits>
#include <stdexcept>
#include <utility>

using namespace std;

unsigned long long magnitude(long long value)
{
    return value < 0 ? 0ULL - static_cast<unsigned long long>(value) : static_cast<unsigned long long>(value);
}

unsigned long long gcd_recursive(unsigned long long first, unsigned long long second)
{
    if (second == 0)
    {
        return first;
    }
    return gcd_recursive(second, first % second);
}

int main()
{
    long long first_input, second_input;
    cout << "Enter two integers: ";
    if (!(cin >> first_input >> second_input))
    {
        return 1;
    }
    unsigned long long first = magnitude(first_input), second = magnitude(second_input);
    if (first == 0 && second == 0)
    {
        cout << "GCD(0, 0) is undefined.\n";
        return 1;
    }
    cout << "Recursive GCD = " << gcd_recursive(first, second) << '\n';
    while (second != 0)
    {
        unsigned long long remainder = first % second;
        first = second;
        second = remainder;
    }
    cout << "Iterative GCD = " << first << '\n';
    return 0;
}
