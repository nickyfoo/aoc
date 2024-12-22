#pragma GCC optimize ("O3")
#include <ranges>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <algorithm>


using namespace std;
using ll = long long;

vector<ll> split(const string&line, char delim){
    stringstream ss(line);
    string s;
    vector<ll> ans;
    while(getline(ss,s,delim)){
        if(!s.empty()) ans.push_back(stoll(s));
    }
    return ans;
}

vector<pair<int,int>> d4{{0,1},{1,0},{0,-1},{-1,0}};


vector<string> grid;

int main(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
    string line;
    while(getline(cin,line)){
        grid.push_back(line);
    }

    int m = grid.size(), n = grid[0].size();

    vector<vector<vector<int>>> d(4, vector<vector<int>>(m, vector<int>(n,INT_MAX)));
    vector<vector<vector<vector<tuple<int,int,int>>>>> prev(4, vector<vector<vector<tuple<int,int,int>>>>(m, vector<vector<tuple<int,int,int>>>(n)));

    priority_queue<tuple<int,int,int,int>, vector<tuple<int,int,int,int>>, greater<>> pq;
    d[0][m-2][1] = 0;
    pq.push({0,0,m-2,1});
    while(pq.size()){
        auto [du, dd, i, j] = pq.top(); pq.pop();
        if(d[dd][i][j] != du) continue;
        const auto&[di,dj] = d4[dd];
        if(grid[i+di][j+dj]!='#'){
            if(d[dd][i+di][j+dj] > du + 1){
                d[dd][i+di][j+dj] = du + 1;
                prev[dd][i+di][j+dj] = {{dd,i,j}};
                pq.push({du+1, dd, i+di, j+dj});
            } else if(d[dd][i+di][j+dj] == du + 1){
                prev[dd][i+di][j+dj].push_back({dd,i,j});
            }
        }
        if(d[(dd+1)%4][i][j] > du+1000) {
            d[(dd+1)%4][i][j] = du+1000;
            prev[(dd+1)%4][i][j] = {{dd,i,j}};
            pq.push({du+1000, (dd+1)%4, i, j});
        } else if(d[(dd+1)%4][i][j] == du+1000){
            prev[(dd+1)%4][i][j].push_back({dd,i,j});
        }

        if(d[(dd+3)%4][i][j] > du+1000) {
            d[(dd+3)%4][i][j] = du+1000;
            prev[(dd+3)%4][i][j] = {{dd,i,j}};
            pq.push({du+1000, (dd+3)%4, i, j});
        } else if(d[(dd+3)%4][i][j] == du+1000) {
            prev[(dd+3)%4][i][j].push_back({dd,i,j});
        }
    }

    for(int i=0; i<4; ++i){
        cout << d[i][1][n-2] << '\n';
    }

    vector<vector<vector<int>>> vis(4, vector<vector<int>>(m, vector<int>(n,0)));
    queue<tuple<int,int,int>> q;
    q.push({3,1,n-2});
    vis[3][1][n-2] = 1;
    set<pair<int,int>> good{{1,n-2}};
    while(q.size()){
        auto [dd,i,j] = q.front(); q.pop();
        for(auto&[nd,ni,nj]:prev[dd][i][j]){
            if(!vis[nd][ni][nj]){
                q.push({nd,ni,nj});
                vis[nd][ni][nj] = 1;
                good.insert({ni,nj});
            }
        }
    }
    cout << good.size() << endl;
}

