// Creator: Marcin Szopa

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/// @brief Struct with hash function for vector<int>
struct vector_hash
{
    size_t operator()(const vector<int> &arr) const
    {
        size_t hashValue = 0;
        for (const int &num : arr)
        {
            hashValue ^= hash<int>()(num) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
        }
        return hashValue;
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // 0 - team Left, 1 - team Right
    // playerTeams[playerIndex][matchIndex] = team
    vector<vector<int>> playersTeams(n, vector<int>(m));

    for (int i = 0; i < m; i++)
    {
        for (int k = 0; k < 2; k++)
        {
            for (int j = 0; j < n / 2; j++)
            {
                int playerNo;
                cin >> playerNo;

                const int playerIndex = playerNo - 1;
                playersTeams[playerIndex][i] = k;
            }
        }
    }

    // Find if any playersTeam is unique. If not, atleast two players never played against eachother.
    unordered_map<vector<int>, size_t, vector_hash> labels;
    labels.reserve(n);

    size_t maxGroup = 0;
    for (auto label : playersTeams)
    {
        labels[label]++;
        maxGroup = max(maxGroup, labels[label]);
    }

    cout << maxGroup << endl;
}