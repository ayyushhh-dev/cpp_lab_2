#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <limits>
#include <stdexcept>
#include <utility>

using namespace std;

class LinkedDeque
{
    struct Node
    {
        int value;
        Node *previous = nullptr, *next = nullptr;
        explicit Node(int data) : value(data)
        {
        }
    };
    Node *head = nullptr, *tail = nullptr;
public:
    LinkedDeque() = default;
    LinkedDeque(const LinkedDeque &) = delete;
    LinkedDeque &operator=(const LinkedDeque &) = delete;
    ~LinkedDeque()
    {
        while (head)
        {
            pop_front();
        }
    }
    void push_front(int value)
    {
        Node *node = new Node(value);
        node->next = head;
        if (head)
        {
            head->previous = node;
        }
        else
        {
            tail = node;
        }
        head = node;
    }
    void push_back(int value)
    {
        Node *node = new Node(value);
        node->previous = tail;
        if (tail)
        {
            tail->next = node;
        }
        else
        {
            head = node;
        }
        tail = node;
    }
    int front() const
    {
        if (!head)
        {
            throw underflow_error("Deque is empty.");
        }
        return head->value;
    }
    int back() const
    {
        if (!tail)
        {
            throw underflow_error("Deque is empty.");
        }
        return tail->value;
    }
    int pop_front()
    {
        int value = front();
        Node *old = head;
        head = head->next;
        if (head)
        {
            head->previous = nullptr;
        }
        else
        {
            tail = nullptr;
        }
        delete old;
        return value;
    }
    int pop_back()
    {
        int value = back();
        Node *old = tail;
        tail = tail->previous;
        if (tail)
        {
            tail->next = nullptr;
        }
        else
        {
            head = nullptr;
        }
        delete old;
        return value;
    }
    void display() const
    {
        for (Node *node = head; node; node = node->next)
        {
            cout << node->value << ' ';
        }
        cout << '\n';
    }
};

int main()
{
    LinkedDeque values;
    int choice, value;
    while (true)
    {
        cout << "\n1 Push front  2 Push back  3 Pop front  4 Pop back\n5 Peek front  6 Peek back  7 Display  0 Quit: ";
        if (!(cin >> choice) || choice == 0)
        {
            break;
        }
        try
        {
            if (choice == 1 || choice == 2)
            {
                cout << "Value: ";
                if (!(cin >> value))
                {
                    return 1;
                }
                if (choice == 1)
                {
                    values.push_front(value);
                }
                else
                {
                    values.push_back(value);
                }
            }
            else if (choice == 3)
            {
                cout << values.pop_front() << '\n';
            }
            else if (choice == 4)
            {
                cout << values.pop_back() << '\n';
            }
            else if (choice == 5)
            {
                cout << values.front() << '\n';
            }
            else if (choice == 6)
            {
                cout << values.back() << '\n';
            }
            else if (choice == 7)
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
