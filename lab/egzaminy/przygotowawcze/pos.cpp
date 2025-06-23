#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    vector<pair<int, int>> mono;

    int currStart = 0;
    if (n > 1)
    {
        int currMode = arr[0] == arr[1] ? 0 : (arr[0] < arr[1] ? 1 : -1);
        for (int i = 1; i < n; i++)
        {
            int mode = arr[i - 1] == arr[i] ? 0 : (arr[i - 1] < arr[i] ? 1 : -1);
            if (mode != currMode)
            {
                mono.push_back({currStart, i - 1});
                currStart = i - 1;
                currMode = mode;
            }
        }

        mono.push_back({currStart, n - 1});
    }

    int ans = 0;
    for (auto &interval : mono)
    {
        int oddCount, evenCount;

        if ((arr[interval.first] % 2) == (arr[interval.first + 1] % 2))
        {
            if (arr[interval.first] % 2 == 0)
            {
                oddCount = 0;
                evenCount = 2;
                ans += 1;
            }
            else
            {
                oddCount = 1;
                evenCount = 1;
                ans += 1;
            }
        }
        else
        {
            oddCount = 1;
            evenCount = 1;
        }

        for (int i = interval.first + 2; i <= interval.second; i++)
        {
            if (arr[i] % 2 == 0)
            {
                ans += evenCount;
                evenCount++;
            }
            else
            {
                ans += oddCount;
                swap(oddCount, evenCount);
                oddCount++;
            }
        }
    }

    cout << ans << endl;
}