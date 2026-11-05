#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <limits>
#include <stdexcept>
#include <utility>

using namespace std;

class Polynomial
{
    struct Term
    {
        long long coefficient;
        int exponent;
        Term *next;
        Term(long long c, int e, Term *n) : coefficient(c), exponent(e), next(n)
        {
        }
    };
    Term *head = nullptr;
public:
    Polynomial() = default;
    Polynomial(const Polynomial &) = delete;
    Polynomial &operator=(const Polynomial &) = delete;
    Polynomial(Polynomial &&other) noexcept : head(other.head)
    {
        other.head = nullptr;
    }
    ~Polynomial()
    {
        while (head)
        {
            Term *old = head;
            head = head->next;
            delete old;
        }
    }
    void insert(long long coefficient, int exponent)
    {
        if (!coefficient)
        {
            return;
        }
        Term **link = &head;
        while (*link && (*link)->exponent > exponent)
        {
            link = &(*link)->next;
        }
        if (*link && (*link)->exponent == exponent)
        {
            (*link)->coefficient += coefficient;
            if ((*link)->coefficient == 0)
            {
                Term *old = *link;
                *link = old->next;
                delete old;
            }
        }
        else
        {
            *link = new Term(coefficient, exponent, *link);
        }
    }
    Polynomial add(const Polynomial &other) const
    {
        Polynomial sum;
        for (Term *term = head; term; term = term->next)
        {
            sum.insert(term->coefficient, term->exponent);
        }
        for (Term *term = other.head; term; term = term->next)
        {
            sum.insert(term->coefficient, term->exponent);
        }
        return sum;
    }
    void display() const
    {
        if (!head)
        {
            cout << '0';
        }
        bool first = true;
        for (Term *term = head; term; term = term->next)
        {
            if (!first)
            {
                cout << " + ";
            }
            cout << '(' << term->coefficient << ")x^" << term->exponent;
            first = false;
        }
        cout << '\n';
    }
};

bool read_polynomial(Polynomial &polynomial)
{
    int terms;
    cout << "Number of terms (0-1000): ";
    if (!(cin >> terms) || terms < 0 || terms > 1000)
    {
        return false;
    }
    cout << "Enter coefficient and nonnegative exponent for each term:\n";
    for (int i = 0; i < terms; i++)
    {
        long long coefficient;
        int exponent;
        if (!(cin >> coefficient >> exponent) ||
            coefficient < -1000000000LL ||
            coefficient > 1000000000LL ||
            exponent < 0)
        {
            return false;
        }
        polynomial.insert(coefficient, exponent);
    }
    return true;
}

int main()
{
    Polynomial first, second;
    cout << "First polynomial:\n";
    if (!read_polynomial(first))
    {
        return 1;
    }
    cout << "Second polynomial:\n";
    if (!read_polynomial(second))
    {
        return 1;
    }
    Polynomial sum = first.add(second);
    cout << "First: ";
    first.display();
    cout << "Second: ";
    second.display();
    cout << "Sum: ";
    sum.display();
    return 0;
}
