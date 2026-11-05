#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <limits>
#include <stdexcept>
#include <utility>

using namespace std;

void display(stack<int> values)
{
    cout << "Top -> ";
    while (!values.empty())
    {
        cout << values.top() << ' ';
        values.pop();
    }
    cout << '\n';
}

int main()
{
    int count, value;
    stack<int> original;
    cout << "Number of elements (0-10000): ";
    if (!(cin >> count) || count < 0 || count > 10000)
    {
        return 1;
    }
    cout << "Enter bottom-to-top order:\n";
    for (int i = 0; i < count; i++)
    {
        if (!(cin >> value))
        {
            return 1;
        }
        original.push(value);
    }
    cout << "Before: ";
    display(original);
    queue<int> auxiliary;
    while (!original.empty())
    {
        auxiliary.push(original.top());
        original.pop();
    }
    while (!auxiliary.empty())
    {
        original.push(auxiliary.front());
        auxiliary.pop();
    }
    cout << "After: ";
    display(original);
    return 0;
}
