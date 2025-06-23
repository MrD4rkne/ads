#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdint>

using namespace std;

int main()
{
    int n;
    cin >> n;

    uint64_t a[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    int lis[n];
    lis[0] = 1;
    for (int i = 1; i < n; i++)
    {
        if (a[i] > a[i - 1])
        {
            lis[i] = lis[i - 1] + 1;
        }
        else
        {
            lis[i] = 1;
        }
    }

    uint64_t ans = 0;

    for (int i = 1; i < n; i++)
    {
        if (lis[i] < lis[i - 1])
        {
            ans += a[i - 1];
        }
    }

    if (lis[n - 1] > 1)
    {
        ans += a[n - 1];
    }

    for (int i = 1; i < n; i++)
    {
        if (lis[i] == 2)
        {
            ans -= a[i - 1];
        }
    }

    std::cout << ans << std::endl;

    return 0;
}