#include <iostream>

using namespace std;

int main()
{
    string pattern;
    getline(cin, pattern);

    const int n = pattern.size();

    int maxShift = n - 1;
    int currNonUniversalColorIndex = 0;
    for (int i = 1; i < n && currNonUniversalColorIndex < n; i++)
    {
        if (pattern[currNonUniversalColorIndex] == '*')
        {
            currNonUniversalColorIndex++;
            i--;
            continue;
        }

        if (currNonUniversalColorIndex >= i)
        {
            i = currNonUniversalColorIndex;
            continue;
        }

        if (pattern[i] == '*' || pattern[i] == pattern[currNonUniversalColorIndex])
        {
            continue;
        }

        int currShift = i - currNonUniversalColorIndex - 1;
        maxShift = min(maxShift, currShift);
        currNonUniversalColorIndex++;
        i--;
    }

    int minMatrixLength = n - maxShift;
    cout << minMatrixLength << endl;

    return 0;
}