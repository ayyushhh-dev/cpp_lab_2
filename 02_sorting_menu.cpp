#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <limits>
#include <stdexcept>
#include <utility>

using namespace std;

void insertion_sort(vector<int> &values)
{
    for (int i = 1; i < static_cast<int>(values.size()); i++)
    {
        int key = values[i], j = i - 1;
        while (j >= 0 && values[j] > key)
        {
            values[j + 1] = values[j];
            j--;
        }
        values[j + 1] = key;
    }
}

void bubble_sort(vector<int> &values)
{
    for (size_t pass = 0; pass < values.size(); pass++)
    {
        bool changed = false;
        for (size_t j = 0; j + 1 < values.size() - pass; j++)
        {
            if (values[j] > values[j + 1])
            {
                swap(values[j], values[j + 1]);
                changed = true;
            }
        }
        if (!changed)
        {
            break;
        }
    }
}

void selection_sort(vector<int> &values)
{
    for (size_t i = 0; i < values.size(); i++)
    {
        size_t smallest = i;
        for (size_t j = i + 1; j < values.size(); j++)
        {
            if (values[j] < values[smallest])
            {
                smallest = j;
            }
        }
        swap(values[i], values[smallest]);
    }
}

int main()
{
    int n, choice;
    cout << "Size (1-10000): ";
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
    cout << "1 Insertion  2 Bubble  3 Selection: ";
    if (!(cin >> choice))
    {
        return 1;
    }
    if (choice == 1)
    {
        insertion_sort(values);
    }
    else if (choice == 2)
    {
        bubble_sort(values);
    }
    else if (choice == 3)
    {
        selection_sort(values);
    }
    else
    {
        return 1;
    }
    for (int value : values)
    {
        cout << value << ' ';
    }
    cout << '\n';
    return 0;
}
