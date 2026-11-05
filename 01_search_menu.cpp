#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <limits>
#include <stdexcept>
#include <utility>

using namespace std;

int main()
{
    int n, choice, target;
    cout << "Number of elements (1-10000): ";
    if (!(cin >> n) || n < 1 || n > 10000)
    {
        return 1;
    }
    vector<int> values(n);
    for (int &value : values)
    {
        if (!(cin >> value))
        {
            return 1;
        }
    }
    cout << "1 Linear search  2 Binary search\nChoice and target: ";
    if (!(cin >> choice >> target))
    {
        return 1;
    }
    int position = -1;
    if (choice == 1)
    {
        for (int i = 0; i < n; i++)
        {
            if (values[i] == target)
            {
                position = i;
                break;
            }
        }
    }
    else if (choice == 2)
    {
        if (!is_sorted(values.begin(), values.end()))
        {
            cout << "Binary search requires ascending input.\n";
            return 1;
        }
        int low = 0, high = n - 1;
        while (low <= high)
        {
            int middle = low + (high - low) / 2;
            if (values[middle] == target)
            {
                position = middle;
                break;
            }
            if (values[middle] < target)
            {
                low = middle + 1;
            }
            else
            {
                high = middle - 1;
            }
        }
    }
    else
    {
        cout << "Invalid choice.\n";
        return 1;
    }
    if (position == -1)
    {
        cout << "Not found.\n";
    }
    else
    {
        cout << "Found at zero-based index " << position << '\n';
    }
    return 0;
}
