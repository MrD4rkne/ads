#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct IncreasingComparator
{
    bool operator()(int a, int b)
    {
        return a < b;
    }
};

struct DecreasingComparator
{
    bool operator()(int a, int b)
    {
        return a > b;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++)
    {
        char c;
        cin >> c;
        arr[i] = c - '0';
    }

    for (int i = 0; i < m; i++)
    {
        char c;
        cin >> c;

        switch (c)
        {
        case '?':
        {
            int i;
            cin >> i;
            cout << arr[i] << endl;
            break;
        }
        case '>':
        case '<':
        {
            int a, b;
            cin >> a >> b;
            if (c == '<')
                sort(arr.begin() + a, arr.begin() + b + 1, IncreasingComparator());
            else
                sort(arr.begin() + a, arr.begin() + b + 1, DecreasingComparator());
            break;
        }
        }
    }
}