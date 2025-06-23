#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int find(const vector<pair<int64_t,int64_t>> &intervals, int i, int start){
    int j = i+1;
    while(j < intervals.size() && intervals[j].second < start){
        j++;
    }

    if(j == intervals.size() || intervals[j].first > start){
        return -1;
    }

    return j;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int64_t n,m;
    cin>>n>>m;

    vector<int64_t> tab(m);
    for(int i=0;i<m;i++){
        cin>>tab[i];
    }

    vector<pair<int64_t,int64_t>> intervals;
    if(m>0){
        intervals.push_back({0,tab[0]-1});
    }
    else{
        intervals.push_back({0,n});
    }
    
    for(int i = 1; i<m; i++){
        if (tab[i]-1>=tab[i-1]+1)
        intervals.push_back({tab[i-1]+1,tab[i]-1});
    }

    if(m > 0 && tab[m-1]<n)
        intervals.push_back({tab[m-1]+1,n});

    vector<map<int,int64_t>> bestPath(intervals.size());
    bestPath[0].insert({0,0});

    vector<pair<int64_t,int>> jumps = {{5,10},{10,100}};

    for(int i = 0; i<intervals.size()-1; i++){
        auto [start,end] = intervals[i];

        for(auto [to,cost] : bestPath[i]){        
            for(int upTo=std::min(end-to + 1,(int64_t)20); upTo>=0; upTo--){
                int jumpFrom = end-upTo;
                if(jumpFrom < to){
                    continue;
                }

                for(auto [by, jumpCost] : jumps){
                    int index = find(intervals,i,jumpFrom+by);
                    if(index == -1)
                        continue;

                    int64_t costUntilJump = cost + jumpFrom-to;
                    int jumpTo = jumpFrom + by;
                    auto it = bestPath[index].find(jumpTo);
                    if(it == bestPath[index].end()){
                        bestPath[index].insert({jumpTo, costUntilJump + jumpCost});
                    }
                    else{
                        it->second = std::min(it->second,costUntilJump + jumpCost);
                    }
                }
            }
        }
    }


    if(intervals[intervals.size()-1].second == n && bestPath[bestPath.size()-1].size() > 0){
        int64_t k = INT64_MAX;
        for(auto [to,cost] : bestPath[bestPath.size()-1]){
            k = std::min(k,cost + n-to);
        }

        cout<<k<<endl;
    }
    else{
        cout<<-1<<endl;
    }
}