#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <limits>
#include <stdexcept>
#include <utility>

using namespace std;

struct Entry
{
    int row;
    int column;
    long long value;
};

int main()
{
    int choice, rows, columns;
    cout << "1 Dense to triplet form  2 Triplet to dense: ";
    if (!(cin >> choice))
    {
        return 1;
    }
    cout << "Rows and columns (1-100): ";
    if (!(cin >> rows >> columns) || rows < 1 || rows > 100 || columns < 1 || columns > 100)
    {
        return 1;
    }
    vector<vector<long long>> dense(rows, vector<long long>(columns, 0));
    vector<Entry> entries;
    if (choice == 1)
    {
        cout << "Enter dense elements row by row:\n";
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (!(cin >> dense[i][j]))
                {
                    return 1;
                }
                if (dense[i][j] != 0)
                {
                    entries.push_back({i, j, dense[i][j]});
                }
            }
        }
        cout << "Rows Columns Nonzeros\n" << rows << ' ' << columns << ' ' << entries.size() << "\nRow Column Value (zero-based)\n";
        for (const Entry &entry : entries)
        {
            cout << entry.row << ' ' << entry.column << ' ' << entry.value << '\n';
        }
    }
    else if (choice == 2)
    {
        int count;
        cout << "Number of nonzero entries: ";
        if (!(cin >> count) || count < 0 || count > rows * columns)
        {
            return 1;
        }
        vector<vector<bool>> used(rows, vector<bool>(columns, false));
        cout << "Enter zero-based row, column, nonzero value (no duplicates):\n";
        for (int i = 0; i < count; i++)
        {
            Entry entry;
            if (!(cin >> entry.row >> entry.column >> entry.value) ||
                entry.row < 0 ||
                entry.row >= rows ||
                entry.column < 0 ||
                entry.column >= columns ||
                entry.value == 0)
            {
                return 1;
            }
            if (used[entry.row][entry.column])
            {
                cout << "Duplicate position.\n";
                return 1;
            }
            used[entry.row][entry.column] = true;
            dense[entry.row][entry.column] = entry.value;
        }
        for (const auto &row : dense)
        {
            for (long long value : row)
            {
                cout << value << ' ';
            }
            cout << '\n';
        }
    }
    else
    {
        return 1;
    }
    return 0;
}
