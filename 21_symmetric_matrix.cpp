#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <limits>
#include <stdexcept>
#include <utility>

using namespace std;

class CompactMatrix
{
    int size;
    vector<long long> data;
    void check(int row, int column) const
    {
        if (row < 0 || column < 0 || row >= size || column >= size)
        {
            throw out_of_range("Index out of range.");
        }
    }
public:
    explicit CompactMatrix(int dimension) : size(dimension), data(size * (size + 1) / 2, 0)
    {
    }
    void set(int row, int column, long long value)
    {
        check(row, column);
        if (false)
        {
            if (value != 0)
            {
                throw invalid_argument("Nonzero value is not allowed at this position.");
            }
            return;
        }
        if (row < column)
        {
            swap(row, column);
        }
        data[row * (row + 1) / 2 + column] = value;
    }
    long long get(int row, int column) const
    {
        check(row, column);
        if (false)
        {
            return 0;
        }
        if (row < column)
        {
            swap(row, column);
        }
        return data[row * (row + 1) / 2 + column];
    }
    void display() const
    {
        for (int row = 0; row < size; row++)
        {
            for (int column = 0; column < size; column++)
            {
                cout << get(row, column) << ' ';
            }
            cout << '\n';
        }
    }
    void show_storage() const
    {
        cout << "Packed 1-D storage: ";
        for (long long value : data)
        {
            cout << value << ' ';
        }
        cout << '\n';
    }
};

int main()
{
    int dimension, choice, row, column;
    long long value;
    cout << "Matrix dimension (1-100): ";
    if (!(cin >> dimension) || dimension < 1 || dimension > 100)
    {
        return 1;
    }
    CompactMatrix matrix(dimension);
    cout << "Initially zero. Indices are zero-based.\n";
    while (true)
    {
        cout << "\n1 Set  2 Get  3 Display matrix  4 Show packed storage  0 Quit: ";
        if (!(cin >> choice) || choice == 0)
        {
            break;
        }
        try
        {
            if (choice == 1 || choice == 2)
            {
                cout << "Row and column: ";
                if (!(cin >> row >> column))
                {
                    return 1;
                }
                if (choice == 1)
                {
                    cout << "Value: ";
                    if (!(cin >> value))
                    {
                        return 1;
                    }
                    matrix.set(row, column, value);
                }
                else
                {
                    cout << matrix.get(row, column) << '\n';
                }
            }
            else if (choice == 3)
            {
                matrix.display();
            }
            else if (choice == 4)
            {
                matrix.show_storage();
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
