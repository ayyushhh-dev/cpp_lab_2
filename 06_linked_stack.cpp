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
    struct Node
    {
        int value;
        Node *next;
        Node(int data, Node *link) : value(data), next(link)
        {
        }
    };
    Node *top = nullptr;
public:
    Stack() = default;
    Stack(const Stack &) = delete;
    Stack &operator=(const Stack &) = delete;
    ~Stack()
    {
        while (top)
        {
            Node *old = top;
            top = top->next;
            delete old;
        }
    }
    void push(int value)
    {
        top = new Node(value, top);
    }
    int peek() const
    {
        if (!top)
        {
            throw underflow_error("Stack is empty.");
        }
        return top->value;
    }
    int pop()
    {
        int value = peek();
        Node *old = top;
        top = top->next;
        delete old;
        return value;
    }
    void display() const
    {
        cout << "Top -> ";
        for (Node *node = top; node; node = node->next)
        {
            cout << node->value << ' ';
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
