#include <iostream>
#include <vector>

using namespace std;

void insert(vector<size_t> &table, size_t j, size_t x, size_t k)
{
    table.insert(table.begin() + j, k, x);
}

int main()
{
    int m;
    cin >> m;

    size_t n = 0;
    size_t w = 0;

    vector<size_t> table;

    for (int i = 0; i < m; i++)
    {
        char op;
        cin >> op;

        size_t jp, x, k;
        cin >> jp;
        if (op == 'i')
        {
            cin >> x >> k;
            n += 1;
        }

        size_t j = (jp + w) % n;

        if (op == 'i')
        {
            insert(table, j, x, k);
            n = table.size();
        }
        else
        {
            w = table[j];
            cout << w << "\n";
        }
    }
    return 0;
}
