#include <iostream>

#include <vector>
#include <string>
#include <queue>
#include <climits>
#include <array>
#include <algorithm>
#include <tuple>

using namespace std;

#define WALL '#'
#define START 'S'
#define END 'M'

using point_t = std::pair<int, int>;

int main()
{
    int n, m;
    cin >> n >> m;

    const int rows = n;
    const int columns = m;

    point_t start;
    point_t end;

    const int NONE = n * n * 2;

    char board[rows][columns];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cin >> board[i][j];

            if (board[i][j] == START)
            {
                start = {i, j};
            }
            else if (board[i][j] == END)
            {
                end = {i, j};
            }
        }
    }

    const int dx[] = {0, 0, 1, -1};
    const int dy[] = {1, -1, 0, 0};

    vector<vector<vector<vector<vector<int>>>>> dist(rows, vector<vector<vector<vector<int>>>>(columns, vector<vector<vector<int>>>(2, vector<vector<int>>(2, vector<int>(2, NONE)))));

    queue<std::tuple<point_t, std::array<bool, 3>, int>> q;
    q.push({start, {false, false, false}, 0});

    int minDistance = NONE;

    while (!q.empty())
    {
        auto [current, collected, distance] = q.front();
        q.pop();

        if (current == end && std::all_of(collected.begin(), collected.end(), [](bool b)
                                          { return b; }))
        {
            minDistance = distance;
        }

        for (int i = 0; i < 4; i++)
        {
            int x = current.first + dx[i];
            int y = current.second + dy[i];

            if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] == WALL)
            {
                continue;
            }

            std::array<bool, 3> newCollected = collected;
            if (board[x][y] == '1')
            {
                newCollected[0] = true;
            }
            else if (board[x][y] == '2')
            {
                newCollected[1] = true;
            }
            else if (board[x][y] == '3')
            {
                newCollected[2] = true;
            }

            auto &currDistance = dist[x][y][newCollected[0]][newCollected[1]][newCollected[2]];

            if (currDistance > distance + 1)
            {
                currDistance = distance + 1;
                q.push({{x, y}, newCollected, distance + 1});
            }
        }
    }

    if (minDistance == NONE)
    {
        minDistance = -1;
    }

    cout << minDistance << endl;
    return 0;
}