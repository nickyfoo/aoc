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

// mapper[tile, dir] = {next dirs};
map<pair<char,int>, vector<int>> mapper;

void initMapper(){
    for(int i=0; i<4; i++){
        mapper[{'.',i}] = {i};
    }
    mapper[{'-',0}] = {2,3};
    mapper[{'-',1}] = {2,3};
    mapper[{'-',2}] = {2};
    mapper[{'-',3}] = {3};

    mapper[{'|',0}] = {0};
    mapper[{'|',1}] = {1};
    mapper[{'|',2}] = {0,1};
    mapper[{'|',3}] = {0,1};

    mapper[{'/',0}] = {3};
    mapper[{'/',1}] = {2};
    mapper[{'/',2}] = {1};
    mapper[{'/',3}] = {0};

    mapper[{'\\',0}] = {2};
    mapper[{'\\',1}] = {3};
    mapper[{'\\',2}] = {0};
    mapper[{'\\',3}] = {1};
}

int process(vector<string>&grid, int x, int y, int d){
    int m =grid.size(), n = grid[0].size();
    set<tuple<int,int,int>> s;
    queue<tuple<int,int,int>> q;
    q.push({x,y,d});
    s.insert({x,y,d});
    while(q.size()){
        auto [i,j,d] = q.front(); q.pop();
        for(auto&nextD:mapper[{grid[i][j],d}]) {
            auto&[di,dj] = d4[nextD];
            if(0<=i+di && i+di<m && 0<=j+dj && j+dj<n){
                if(!s.count({i+di,j+dj,nextD})) {
                    s.insert({i+di,j+dj,nextD});
                    q.push({i+di,j+dj,nextD});
                }
            }
        }
    }

    vector<vector<int>> vis(m, vector<int>(n,'.'));
    for(auto&[i,j,d]:s){
        vis[i][j]='#';
    }
    int ans = 0;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            ans += vis[i][j]=='#';
        }
    }
    return ans;
}

int main()
{
    freopen("input.txt", "r", stdin);
    string line;
    vector<string> grid;

    while (getline(cin,line))
    {
        grid.push_back(line);
    }
    initMapper();
    cout << process(grid,0,0,3) << '\n';
    int ans = 0;
    for(int j=0; j<grid[0].size(); j++){
        ans = max(ans, process(grid,0,j,1));
    }
    for(int i=0; i<grid.size(); i++){
        ans = max(ans, process(grid,i,0,3));
    }
    cout << ans << '\n';
    return 0;
}
