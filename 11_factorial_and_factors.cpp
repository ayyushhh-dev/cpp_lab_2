#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <limits>
#include <stdexcept>
#include <utility>

using namespace std;

unsigned long long factorial_recursive(unsigned number)
{
    if (number < 2)
    {
        return 1;
    }
    return number * factorial_recursive(number - 1);
}

void factors_recursive(int number, int divisor)
{
    if (divisor > number / divisor)
    {
        return;
    }
    if (number % divisor == 0)
    {
        cout << divisor << ' ';
    }
    factors_recursive(number, divisor + 1);
    if (number % divisor == 0 && divisor != number / divisor)
    {
        cout << number / divisor << ' ';
    }
}

int main()
{
    int number;
    cout << "Enter n for factorial (0-20): ";
    if (!(cin >> number) || number < 0 || number > 20)
    {
        return 1;
    }
    unsigned long long product = 1;
    for (int i = 2; i <= number; i++)
    {
        product *= i;
    }
    cout << "Recursive factorial = " << factorial_recursive(number) << "\nIterative factorial = " << product << '\n';
    cout << "Enter positive number for factors (1-1000000): ";
    if (!(cin >> number) || number < 1 || number > 1000000)
    {
        return 1;
    }
    cout << "Recursive factors: ";
    factors_recursive(number, 1);
    cout << "\nIterative factors: ";
    for (int i = 1; i <= number; i++)
    {
        if (number % i == 0)
        {
            cout << i << ' ';
        }
    }
    cout << '\n';
    return 0;
}
