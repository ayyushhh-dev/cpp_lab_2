#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <limits>
#include <stdexcept>
#include <utility>

using namespace std;

class DoublyLinkedList
{
    struct Node
    {
        int value;
        Node *previous;
        Node *next;
        Node(int data) : value(data), previous(nullptr), next(nullptr)
        {
        }
    };
    Node *head = nullptr, *tail = nullptr;
public:
    DoublyLinkedList() = default;
    DoublyLinkedList(const DoublyLinkedList &) = delete;
    DoublyLinkedList &operator=(const DoublyLinkedList &) = delete;
    ~DoublyLinkedList()
    {
        while (head)
        {
            Node *old = head;
            head = head->next;
            delete old;
        }
    }
    void insert(int value)
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
    bool erase(int value)
    {
        Node *node = head;
        while (node && node->value != value)
        {
            node = node->next;
        }
        if (!node)
        {
            return false;
        }
        if (node->previous)
        {
            node->previous->next = node->next;
        }
        else
        {
            head = node->next;
        }
        if (node->next)
        {
            node->next->previous = node->previous;
        }
        else
        {
            tail = node->previous;
        }
        delete node;
        return true;
    }
    bool search(int value) const
    {
        for (Node *node = head; node; node = node->next)
        {
            if (node->value == value)
            {
                return true;
            }
        }
        return false;
    }
    void reverse()
    {
        Node *node = head;
        while (node)
        {
            swap(node->next, node->previous);
            node = node->previous;
        }
        swap(head, tail);
    }
    void display() const
    {
        cout << "Forward: ";
        for (Node *node = head; node; node = node->next)
        {
            cout << node->value << ' ';
        }
        cout << "\nBackward: ";
        for (Node *node = tail; node; node = node->previous)
        {
            cout << node->value << ' ';
        }
        cout << '\n';
    }
};

int main()
{
    DoublyLinkedList list;
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
