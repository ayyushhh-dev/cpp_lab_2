#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <limits>
#include <stdexcept>
#include <utility>

using namespace std;

struct Node
{
    int value;
    Node *left = nullptr, *right = nullptr;
    explicit Node(int data) : value(data)
    {
    }
};

void clear_tree(Node *root)
{
    if (!root)
    {
        return;
    }
    clear_tree(root->left);
    clear_tree(root->right);
    delete root;
}

Node *insert_recursive(Node *root, int value)
{
    if (!root)
    {
        return new Node(value);
    }
    if (value < root->value)
    {
        root->left = insert_recursive(root->left, value);
    }
    else if (value > root->value)
    {
        root->right = insert_recursive(root->right, value);
    }
    return root;
}

void insert_iterative(Node *&root, int value)
{
    Node **link = &root;
    while (*link)
    {
        if (value == (*link)->value)
        {
            return;
        }
        link = value < (*link)->value ? &(*link)->left : &(*link)->right;
    }
    *link = new Node(value);
}

bool search(Node *root, int value)
{
    while (root)
    {
        if (root->value == value)
        {
            return true;
        }
        root = value < root->value ? root->left : root->right;
    }
    return false;
}

Node *delete_copying(Node *root, int value)
{
    if (!root)
    {
        return nullptr;
    }
    if (value < root->value)
    {
        root->left = delete_copying(root->left, value);
    }
    else if (value > root->value)
    {
        root->right = delete_copying(root->right, value);
    }
    else
    {
        if (!root->left || !root->right)
        {
            Node *replacement = root->left ? root->left : root->right;
            delete root;
            return replacement;
        }
        Node *predecessor = root->left;
        while (predecessor->right)
        {
            predecessor = predecessor->right;
        }
        root->value = predecessor->value;
        root->left = delete_copying(root->left, predecessor->value);
    }
    return root;
}

Node *delete_merging(Node *root, int value)
{
    if (!root)
    {
        return nullptr;
    }
    if (value < root->value)
    {
        root->left = delete_merging(root->left, value);
    }
    else if (value > root->value)
    {
        root->right = delete_merging(root->right, value);
    }
    else
    {
        Node *replacement = root->left ? root->left : root->right;
        if (root->left && root->right)
        {
            Node *rightmost = root->left;
            while (rightmost->right)
            {
                rightmost = rightmost->right;
            }
            rightmost->right = root->right;
        }
        delete root;
        return replacement;
    }
    return root;
}

void recursive_traversal(Node *root, int order)
{
    if (!root)
    {
        return;
    }
    if (order == 0)
    {
        cout << root->value << ' ';
    }
    recursive_traversal(root->left, order);
    if (order == 1)
    {
        cout << root->value << ' ';
    }
    recursive_traversal(root->right, order);
    if (order == 2)
    {
        cout << root->value << ' ';
    }
}

void iterative_preorder(Node *root)
{
    if (!root)
    {
        return;
    }
    stack<Node *> pending;
    pending.push(root);
    while (!pending.empty())
    {
        Node *node = pending.top();
        pending.pop();
        cout << node->value << ' ';
        if (node->right)
        {
            pending.push(node->right);
        }
        if (node->left)
        {
            pending.push(node->left);
        }
    }
}

void iterative_inorder(Node *root)
{
    stack<Node *> pending;
    while (root || !pending.empty())
    {
        while (root)
        {
            pending.push(root);
            root = root->left;
        }
        root = pending.top();
        pending.pop();
        cout << root->value << ' ';
        root = root->right;
    }
}

void iterative_postorder(Node *root)
{
    if (!root)
    {
        return;
    }
    stack<Node *> first, second;
    first.push(root);
    while (!first.empty())
    {
        Node *node = first.top();
        first.pop();
        second.push(node);
        if (node->left)
        {
            first.push(node->left);
        }
        if (node->right)
        {
            first.push(node->right);
        }
    }
    while (!second.empty())
    {
        cout << second.top()->value << ' ';
        second.pop();
    }
}

void level_order(Node *root)
{
    if (!root)
    {
        cout << "Empty\n";
        return;
    }
    queue<Node *> pending;
    pending.push(root);
    while (!pending.empty())
    {
        size_t count = pending.size();
        while (count--)
        {
            Node *node = pending.front();
            pending.pop();
            cout << node->value << ' ';
            if (node->left)
            {
                pending.push(node->left);
            }
            if (node->right)
            {
                pending.push(node->right);
            }
        }
        cout << '\n';
    }
}

pair<int, int> counts(Node *root)
{
    if (!root)
    {
        return {0, 0};
    }
    if (!root->left && !root->right)
    {
        return {1, 0};
    }
    auto left = counts(root->left);
    auto right = counts(root->right);
    return {left.first + right.first, 1 + left.second + right.second};
}

int height(Node *root)
{
    if (!root)
    {
        return 0;
    }
    return 1 + max(height(root->left), height(root->right));
}

Node *mirror_copy(Node *root)
{
    if (!root)
    {
        return nullptr;
    }
    Node *copy = new Node(root->value);
    copy->left = mirror_copy(root->right);
    copy->right = mirror_copy(root->left);
    return copy;
}

bool equal_trees(Node *first, Node *second)
{
    if (!first || !second)
    {
        return first == second;
    }
    return first->value == second->value &&
        equal_trees(first->left, second->left) &&
        equal_trees(first->right, second->right);
}

int main()
{
    Node *first = nullptr, *second = nullptr;
    int choice, selected, value;
    while (true)
    {
        cout << "\n1 Insert recursive  2 Insert iterative  3 Delete copying\n4 Delete merging  5 Search  6 Recursive traversals\n7 Iterative traversals  8 Level order  9 Counts  10 Height\n11 Display mirror copy  12 Compare both trees  0 Quit: ";
        if (!(cin >> choice) || choice == 0)
        {
            break;
        }
        if (choice == 12)
        {
            cout << (equal_trees(first, second) ? "Equal\n" : "Not equal\n");
            continue;
        }
        cout << "Select tree (1 or 2): ";
        if (!(cin >> selected) || (selected != 1 && selected != 2))
        {
            break;
        }
        Node *&root = selected == 1 ? first : second;
        if (choice >= 1 && choice <= 5)
        {
            cout << "Value (duplicate keys are ignored): ";
            if (!(cin >> value))
            {
                break;
            }
            if (choice == 1)
            {
                root = insert_recursive(root, value);
            }
            else if (choice == 2)
            {
                insert_iterative(root, value);
            }
            else if (choice == 3)
            {
                root = delete_copying(root, value);
            }
            else if (choice == 4)
            {
                root = delete_merging(root, value);
            }
            else
            {
                cout << (search(root, value) ? "Found\n" : "Not found\n");
            }
        }
        else if (choice == 6 || choice == 7)
        {
            cout << "Preorder: ";
            if (choice == 6)
            {
                recursive_traversal(root, 0);
            }
            else
            {
                iterative_preorder(root);
            }
            cout << "\nInorder: ";
            if (choice == 6)
            {
                recursive_traversal(root, 1);
            }
            else
            {
                iterative_inorder(root);
            }
            cout << "\nPostorder: ";
            if (choice == 6)
            {
                recursive_traversal(root, 2);
            }
            else
            {
                iterative_postorder(root);
            }
            cout << '\n';
        }
        else if (choice == 8)
        {
            level_order(root);
        }
        else if (choice == 9)
        {
            auto result = counts(root);
            cout << "Leaf nodes = " << result.first << ", non-leaf nodes = " << result.second << '\n';
        }
        else if (choice == 10)
        {
            cout << "Height in levels (empty = 0) = " << height(root) << '\n';
        }
        else if (choice == 11)
        {
            Node *mirror = mirror_copy(root);
            cout << "Mirror level order (original BST unchanged):\n";
            level_order(mirror);
            clear_tree(mirror);
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }
    clear_tree(first);
    clear_tree(second);
    return 0;
}
