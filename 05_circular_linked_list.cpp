#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <limits>
#include <stdexcept>
#include <utility>

using namespace std;

class CircularList
{
    struct Node
    {
        int value;
        Node *next;
        Node(int data) : value(data), next(nullptr)
        {
        }
    };
    Node *tail = nullptr;
public:
    CircularList() = default;
    CircularList(const CircularList &) = delete;
    CircularList &operator=(const CircularList &) = delete;
    ~CircularList()
    {
        if (tail)
        {
            Node *node = tail->next;
            tail->next = nullptr;
            while (node)
            {
                Node *next = node->next;
                delete node;
                node = next;
            }
        }
    }
    void insert(int value)
    {
        Node *node = new Node(value);
        if (!tail)
        {
            node->next = node;
        }
        else
        {
            node->next = tail->next;
            tail->next = node;
        }
        tail = node;
    }
    bool erase(int value)
    {
        if (!tail)
        {
            return false;
        }
        Node *previous = tail, *node = tail->next;
        do
        {
            if (node->value == value)
            {
                if (node == previous)
                {
                    tail = nullptr;
                }
                else
                {
                    previous->next = node->next;
                    if (node == tail)
                    {
                        tail = previous;
                    }
                }
                delete node;
                return true;
            }
            previous = node;
            node = node->next;
        }
        while (node != tail->next);
        return false;
    }
    bool search(int value) const
    {
        if (!tail)
        {
            return false;
        }
        Node *node = tail->next;
        do
        {
            if (node->value == value)
            {
                return true;
            }
            node = node->next;
        }
        while (node != tail->next);
        return false;
    }
    void reverse()
    {
        if (!tail || tail->next == tail)
        {
            return;
        }
        Node *head = tail->next, *previous = tail, *current = head;
        do
        {
            Node *next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }
        while (current != head);
        tail = head;
    }
    void display() const
    {
        if (!tail)
        {
            cout << "Empty\n";
            return;
        }
        Node *node = tail->next;
        do
        {
            cout << node->value << ' ';
            node = node->next;
        }
        while (node != tail->next);
        cout << "(back to head)\n";
    }
};

int main()
{
    CircularList list;
    int choice, value;
    while (true)
    {
        cout << "\n1 Insert at end  2 Delete first match  3 Search  4 Reverse  5 Display  0 Quit: ";
        if (!(cin >> choice) || choice == 0)
        {
            break;
        }
        if (choice >= 1 && choice <= 3)
        {
            cout << "Value: ";
            if (!(cin >> value))
            {
                return 1;
            }
            if (choice == 1)
            {
                list.insert(value);
            }
            else if (choice == 2)
            {
                cout << (list.erase(value) ? "Deleted\n" : "Not found\n");
            }
            else
            {
                cout << (list.search(value) ? "Found\n" : "Not found\n");
            }
        }
        else if (choice == 4)
        {
            list.reverse();
        }
        else if (choice == 5)
        {
            list.display();
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}
