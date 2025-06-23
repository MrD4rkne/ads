#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const static inline char WALL = '#';
const static inline char EMPTY = '.';
const static inline char START = 'S';
const static inline char END = 'M';
const static inline char TELEPORT = '*';

using point_t = pair<int,int>;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n,m;
    cin>>n >> m;

    point_t start, end;

    vector<point_t> teleports;

    char board[n][m];
    for(int i =0; i<n; i++){
        for(int j=0;j<m;j++){
            cin>>board[i][j];

            switch(board[i][j]){
                case START:
                    start = {i,j};
                    break;
                case END:
                    end = {i,j};
                    break;
                case TELEPORT:
                    teleports.push_back({i,j});
                    break;
            }
        }
    }

    queue<std::pair<point_t, int>> q;
    q.push({start,0});
    
    const int dx[] = {0,0,1,-1};
    const int dy[] = {1,-1,0,0};

    vector<vector<bool>> visited(n, vector<bool>(m,false));
    visited[start.first][start.second] = false;

    bool wereTeleports = false;

    int min = INT_MAX;

    while(!q.empty()){
        auto& [current,steps] = q.front();
        q.pop();

        if(current == end){
            min = steps;
            break;
        }

        for(int i=0;i<4;i++){
            int x = current.first + dx[i];
            int y = current.second + dy[i];

            if(x<0 || x>=n || y<0 || y>=m || board[x][y] == WALL){
                continue;
            }

            if(visited[x][y]){
                continue;
            }

            q.push({{x,y},steps+1});
            visited[x][y] = true;
        }

        if(!wereTeleports  && board[current.first][current.second] == TELEPORT){
            wereTeleports = true;
            for(auto& teleport : teleports){
                if(teleport == current){
                    continue;
                }

                q.push({teleport,steps+1});
                visited[teleport.first][teleport.second] = true;
            }
        }
    }

    if(min == INT_MAX)
    {
        min = -1;
    }

    cout<<min<<endl;
}