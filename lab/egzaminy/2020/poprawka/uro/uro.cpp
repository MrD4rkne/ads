#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const uint64_t UPPER_BOUND = 10000;
const uint64_t MOD = 1000000000;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<uint64_t> arr(n);
    for (size_t i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    vector<uint64_t> endingAt(UPPER_BOUND + 1, 0);
    int64_t sum = 0;
    for (size_t i = 0; i < n; i++)
    {
        int64_t newSubs = (sum + MOD + 1 - endingAt[arr[i]]) % MOD;
        sum = (sum + newSubs) % MOD;
        endingAt[arr[i]] = (endingAt[arr[i]] + newSubs) % MOD;
    }

    cout << sum << endl;
    return 0;
}