#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <climits>


using namespace std;

int main(){
    int n;
    cin>>n;

    vector<std::vector<int>> v(n, vector<int>(3));
    for(int i=0; i<n; i++){
        for(int j=0; j<3; j++){
            cin>>v[i][j];
        }
    }

    vector<pair<int,int>> x(n);
    for(int i=0; i<n; i++){
        x[i] = make_pair(v[i][0], v[i][2]);
    }

    sort(x.begin(), x.end(), [](pair<int,int> a, pair<int,int> b){
        return a.first < b.first;
    });

    vector<pair<int,int>> y(n);
    for(int i=0; i<n; i++){
        y[i] = make_pair(v[i][1],v[i][2]);
    }

    sort (y.begin(), y.end(), [](pair<int,int> a, pair<int,int> b){
        return a.first < b.first;
    });

    unordered_map<int, int> m;
    int current = x[0].first;

    int i = 0, j=0;
    int max =0;
    int pierwszy = 0;
    int akt = 0;
    while(i < n || j < n){
        current=INT_MAX;
        if(i<n){
            current = x[i].first;
        }

        if(j<n){
            current = std::min(current, y[j].first);
        }

        while(j<n && y[j].first == current){
            m[y[j].second]--;
            if(m[y[j].second] == 0){
                akt--;
            }
            j++;
        }

        while(i<n && x[i].first == current){
            m[x[i].second]++;
            if(m[x[i].second] == 1){
                akt++;
            }
            if(akt >max){
                pierwszy=x[i].first;
                max = akt;
            }
            i++;
        }


    }

    std::cout<<pierwszy << " " << max << std::endl;

}