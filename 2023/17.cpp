#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <set>
#include <queue>
using namespace std;
using ll = long long;

vector<pair<int,int>> d4 {{-1,0},{1,0},{0,-1},{0,1}};

int d[150][150][4][11];
int f(vector<string> &grid){
    int m = grid.size(), n = grid[0].size();
    // {du,i,j,prevdir,dist}
    priority_queue<tuple<int,int,int,int,int>, vector<tuple<int,int,int,int,int>>, greater<>> pq;

    for(int i=0; i<150; i++){
        for(int j=0; j<150; j++){
            for(int k=0; k<4; k++){
                for(int l=0; l<11; l++){
                    d[i][j][k][l] = 1e9;
                }
            }
        }
    }

    for(int i=0; i<4; i++){
        pq.push({0,0,0,i,0});
        d[0][0][i][0] = 0;
    }
    while(pq.size()){
        auto [du,i,j,prevDir,len] = pq.top(); pq.pop();
        if(du != d[i][j][prevDir][len]) continue;
        for(int k=0; k<4; k++){
            int nextLen = 1;
            if(k==prevDir){
                nextLen = len + 1;
            } else {
                if(len<4) continue;
            }
            if(k!=prevDir && k/2 == prevDir/2) continue;
            if(nextLen > 10) continue;
            auto&[di,dj] = d4[k];
            if(0<=i+di && i+di<m && 0<=j+dj && j+dj<n){
                int w = grid[i+di][j+dj]-'0';
                if(du + w< d[i+di][j+dj][k][nextLen]) {
                    d[i+di][j+dj][k][nextLen] = du+w;
                    pq.push({du+w,i+di,j+dj,k,nextLen});
                }
            }
        }
    }
    int ans = 1e9;
    for(int i=0; i<4; i++){
        for(int j=4; j<=10; j++){
            ans = min(ans, d[m-1][n-1][i][j]);
        }
    }
    return ans;
}


int main()
{
//    freopen("test.txt", "r", stdin);
    freopen("input.txt", "r", stdin);
    string line;
    vector<string> grid;

    while (getline(cin,line)) {
        grid.push_back(line);
    }
    cout << f(grid);
    return 0;
}
