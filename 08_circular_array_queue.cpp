#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <limits>
#include <stdexcept>
#include <utility>

using namespace std;

class CircularQueue
{
    static constexpr int capacity = 100;
    int data[capacity];
    int front = 0, count = 0;
public:
    void enqueue(int value)
    {
        if (count == capacity)
        {
            throw overflow_error("Queue is full (capacity 100).");
        }
        data[(front + count) % capacity] = value;
        count++;
    }
    int peek() const
    {
        if (!count)
        {
            throw underflow_error("Queue is empty.");
        }
        return data[front];
    }
    int dequeue()
    {
        int value = peek();
        front = (front + 1) % capacity;
        count--;
        return value;
    }
    void display() const
    {
        cout << "Front -> ";
        for (int i = 0; i < count; i++)
        {
            cout << data[(front + i) % capacity] << ' ';
        }
        cout << '\n';
    }
};

int main()
{
    CircularQueue values;
    int choice, value;
    while (true)
    {
        cout << "\n1 Enqueue  2 Dequeue  3 Front  4 Display  0 Quit: ";
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
                values.enqueue(value);
            }
            else if (choice == 2)
            {
                cout << "Removed: " << values.dequeue() << '\n';
            }
            else if (choice == 3)
            {
                cout << "Front: " << values.peek() << '\n';
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
