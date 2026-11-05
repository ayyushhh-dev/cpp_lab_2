#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <limits>
#include <stdexcept>
#include <utility>

using namespace std;

class LinkedList
{
    struct Node
    {
        int value;
        Node *next;
        Node(int data) : value(data), next(nullptr)
        {
        }
    };
    Node *head = nullptr;
public:
    LinkedList() = default;
    LinkedList(const LinkedList &other)
    {
        for (Node *node = other.head; node; node = node->next)
        {
            insert(node->value);
        }
    }
    LinkedList(LinkedList &&other) noexcept : head(other.head)
    {
        other.head = nullptr;
    }
    LinkedList &operator=(LinkedList other)
    {
        swap(head, other.head);
        return *this;
    }
    ~LinkedList()
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
        Node **link = &head;
        while (*link)
        {
            link = &(*link)->next;
        }
        *link = new Node(value);
    }
    bool erase(int value)
    {
        Node **link = &head;
        while (*link && (*link)->value != value)
        {
            link = &(*link)->next;
        }
        if (!*link)
        {
            return false;
        }
        Node *old = *link;
        *link = old->next;
        delete old;
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
        Node *previous = nullptr, *current = head;
        while (current)
        {
            Node *next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }
        head = previous;
    }
    LinkedList concatenate(const LinkedList &other) const
    {
        LinkedList result(*this);
        for (Node *node = other.head; node; node = node->next)
        {
            result.insert(node->value);
        }
        return result;
    }
    LinkedList operator+(const LinkedList &other) const
    {
        return concatenate(other);
    }
    void display() const
    {
        if (!head)
        {
            cout << "Empty";
        }
        for (Node *node = head; node; node = node->next)
        {
            cout << node->value << ' ';
        }
        cout << '\n';
    }
};

int main()
{
    LinkedList first, second;
    int choice, value, selected;
    while (true)
    {
        cout << "\n1 Insert  2 Delete first match  3 Search  4 Reverse\n5 Concatenate function  6 Concatenate operator +  7 Display  0 Quit: ";
        if (!(cin >> choice) || choice == 0)
        {
            break;
        }
        if (choice == 5 || choice == 6)
        {
            LinkedList result = choice == 5 ? first.concatenate(second) : first + second;
            result.display();
            continue;
        }
        cout << "Select list (1 or 2): ";
        if (!(cin >> selected) || (selected != 1 && selected != 2))
        {
            return 1;
        }
        LinkedList &list = selected == 1 ? first : second;
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
        else if (choice == 7)
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
