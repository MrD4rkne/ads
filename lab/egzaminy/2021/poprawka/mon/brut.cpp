#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int sign(int a, int b)
{
    if (a == b)
    {
        return 0;
    }
    return a < b ? 1 : -1;
}

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int ans = 0;

    for (int i = 0; i + 1 < n; i++)
    {
        int sum = arr[i] + arr[i + 1];
        if (sum % 2 == 0)
        {
            ans++;
        }

        for (int j = i + 2; j < n; j++)
        {
            if (sign(arr[i], arr[i + 1]) != sign(arr[j - 1], arr[j]))
            {
                break;
            }

            sum += arr[j];
            if (sum % 2 == 0)
            {
                ans++;
            }
        }
    }

    cout << ans << endl;
}