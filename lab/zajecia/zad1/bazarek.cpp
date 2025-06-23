#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long answer(const int p[], const long long sums[], const int oddIndexes[], const int evenIndexes[], const int oddIndexesReversed[], const int evenIndexesReversed[], int n, int k)
{
    if (k > n)
    {
        return -1;
    }

    int indexLastInSum = n - k;
    long long sum = sums[indexLastInSum];
    if (sum % 2 == 1)
    {
        return sum;
    }

    if (indexLastInSum == 0)
    {
        return -1;
    }

    long long anwser = -1;

    int oddIndex = oddIndexesReversed[indexLastInSum];
    if (oddIndex != -1)
    {
        int evenNumberIndex = evenIndexes[indexLastInSum - 1];
        if (evenNumberIndex != -1)
        {
            anwser = max(anwser, sum - p[oddIndex] + p[evenNumberIndex]);
        }
    }

    int evenIndex = evenIndexesReversed[indexLastInSum];
    if (evenIndex != -1)
    {
        int oddNumberIndex = oddIndexes[indexLastInSum - 1];
        if (oddNumberIndex != -1)
        {
            anwser = max(anwser, sum - p[evenIndex] + p[oddNumberIndex]);
        }
    }
    return anwser;
}

int main()
{
    int n;
    cin >> n;

    int p[n];
    for (int i = 0; i < n; i++)
    {
        cin >> p[i];
    }

    // Generate sums
    long long sums[n];
    sums[n - 1] = p[n - 1];
    for (int i = n - 1 - 1; i >= 0; i--)
    {
        sums[i] = sums[i + 1] + p[i];
    }

    // Generate index arrays
    int oddIndexes[n];
    oddIndexes[0] = (p[0] % 2 == 1 ? 0 : -1);
    int evenIndexes[n];
    evenIndexes[0] = (p[0] % 2 == 0 ? 0 : -1);

    for (int i = 1; i < n; i++)
    {
        if (p[i] % 2 == 0)
        {
            evenIndexes[i] = i;
            oddIndexes[i] = oddIndexes[i - 1];
        }
        else
        {
            oddIndexes[i] = i;
            evenIndexes[i] = evenIndexes[i - 1];
        }
    }

    // Generate index arrays reversed
    int oddIndexesReversed[n];
    oddIndexesReversed[n - 1] = (p[n - 1] % 2 == 1 ? n - 1 : -1);
    int evenIndexesReversed[n];
    evenIndexesReversed[n - 1] = (p[n - 1] % 2 == 0 ? n - 1 : -1);

    for (int i = n - 2; i >= 0; i--)
    {
        if (p[i] % 2 == 0)
        {
            evenIndexesReversed[i] = i;
            oddIndexesReversed[i] = oddIndexesReversed[i + 1];
        }
        else
        {
            oddIndexesReversed[i] = i;
            evenIndexesReversed[i] = evenIndexesReversed[i + 1];
        }
    }

    int m;

    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int k;
        cin >> k;
        cout << answer(p, sums, oddIndexes, evenIndexes, oddIndexesReversed, evenIndexesReversed, n, k) << endl;
    }
}