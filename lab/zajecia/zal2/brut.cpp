#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> arr(n, 1);

    for (int i = 0; i < m; i++)
    {
        char c;
        int l, r;
        cin >> c >> l >> r;

        if (c == 'N')
        {
            int k;
            cin >> k;
            for (int j = l - 1; j < r; j++)
            {
                arr[j] += k;
            }
        }
        else
        {
            int max = 1;
            int curr = 1;
            for (int j = l; j < r; j++)
            {
                if (arr[j] < arr[j - 1])
                {
                    max = std::max(max, curr);
                    curr = 1;
                }
                else
                {
                    curr++;
                }
            }
            max = std::max(max, curr);

            cout << max << endl;
        }
    }

    return 0;
}