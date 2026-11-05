#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <limits>
#include <stdexcept>
#include <utility>

using namespace std;

void fibonacci_recursive(int remaining, unsigned long long first, unsigned long long second)
{
    if (remaining == 0)
    {
        return;
    }
    cout << first << ' ';
    if (remaining > 1)
    {
        fibonacci_recursive(remaining - 1, second, first + second);
    }
}

int main()
{
    int terms;
    cout << "Terms (0-94, starting with F0 = 0): ";
    if (!(cin >> terms) || terms < 0 || terms > 94)
    {
        return 1;
    }
    cout << "Recursive: ";
    fibonacci_recursive(terms, 0, 1);
    cout << "\nIterative: ";
    unsigned long long first = 0, second = 1;
    for (int i = 0; i < terms; i++)
    {
        cout << first << ' ';
        if (i + 1 < terms)
        {
            unsigned long long next = first + second;
            first = second;
            second = next;
        }
    }
    cout << '\n';
    return 0;
}
