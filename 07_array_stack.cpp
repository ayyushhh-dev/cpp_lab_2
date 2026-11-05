#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <limits>
#include <stdexcept>
#include <utility>

using namespace std;

class Stack
{
    static constexpr int capacity = 100;
    int data[capacity];
    int count = 0;
public:
    void push(int value)
    {
        if (count == capacity)
        {
            throw overflow_error("Stack is full (capacity 100).");
        }
        data[count++] = value;
    }
    int peek() const
    {
        if (!count)
        {
            throw underflow_error("Stack is empty.");
        }
        return data[count - 1];
    }
    int pop()
    {
        int value = peek();
        count--;
        return value;
    }
    void display() const
    {
        cout << "Top -> ";
        for (int i = count - 1; i >= 0; i--)
        {
            cout << data[i] << ' ';
        }
        cout << '\n';
    }
};

int main()
{
    Stack values;
    int choice, value;
    while (true)
    {
        cout << "\n1 Push  2 Pop  3 Peek  4 Display  0 Quit: ";
        if (!(cin >> choice) || choice == 0)
        {
            break;
        }
        try
        {
            if (choice == 1)
            {
                cout << "Value: ";
                if (!(cin >> value))
                {
                    return 1;
                }
                values.push(value);
            }
            else if (choice == 2)
            {
                cout << "Popped: " << values.pop() << '\n';
            }
            else if (choice == 3)
            {
                cout << "Top: " << values.peek() << '\n';
            }
            else if (choice == 4)
            {
                values.display();
            }
            else
            {
                cout << "Invalid choice.\n";
            }
        }
        catch (const exception &error)
        {
            cout << error.what() << '\n';
        }
    }
    return 0;
}
