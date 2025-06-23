#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

int apply(vector<char> &c, int a, int b, char action)
{
    for (int i = a - 1; i < b; i++)
    {
        c[i] = action;
    }

    int sum = 0;
    for (int i = 0; i < c.size(); i++)
    {
        if (c[i] == 'B')
        {
            ++sum;
        }
    }

    return sum;
}

int main()
{

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<char> c(n, 'C');

    for (int event = 0; event < m; event++)
    {
        int a, b;
        cin >> a >> b;

        char action;
        cin >> action;

        cout << apply(c, a, b, action) << endl;
    }

    return 0;
}