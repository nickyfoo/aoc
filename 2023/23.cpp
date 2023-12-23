#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <numeric>
using namespace std;
using ll = long long;

string dirs = ">v<^";
vector<pair<int,int>> d4 {{0,1},{1,0},{0,-1},{-1,0}};
vector<string> grid;
int m,n;

int ans = 0;

void dfs(int i, int j, int depth){
    if(i==m-1 && j==n-2){
        ans = max(ans, depth);
//        cout << depth << ' ' << ans << '\n';
        return;
    }
    if(grid[i][j]=='.'){
        for(auto&[di,dj]:d4){
            if(0<=i+di && i+di<m && 0<=j+dj && j+dj<n){
                if(grid[i+di][j+dj]!='#') {
                    grid[i][j] = '#';
                    dfs(i+di,j+dj, depth+1);
                    grid[i][j] = '.';
                }
            }
        }
    } else {
        int dir = dirs.find(grid[i][j]);
        auto&[di,dj] = d4[dir];
        if(grid[i+di][j+dj]!='.') return;
        grid[i][j] = '#';
        dfs(i+di, j+dj, depth+1);
        grid[i][j] = dirs[dir];
    }
    return;
}
vector<vector<int>> deg;
vector<pair<int,int>> junctions;

map<pair<int,int>, vector<tuple<int,int,int>>> al;

void getDist(int si, int sj){
    queue<pair<int,int>> q;
    vector<vector<int>> d(m, vector<int>(n,-1));
    d[si][sj] = 0;
    q.push({si,sj});
    while(q.size()){
        auto [i,j] = q.front();
        q.pop();

        for(auto&[di,dj]:d4){
            if(0<=i+di && i+di<m && 0<=j+dj && j+dj<n){
                if(grid[i+di][j+dj]!='#' && d[i+di][j+dj]==-1) {
                    d[i+di][j+dj] = d[i][j]+1;
                    if(deg[i+di][j+dj]>=3 || i+di==m-1 && j+dj==n-2 || i+di==0 && j+dj==1){
                        al[{si,sj}].push_back({i+di,j+dj,d[i+di][j+dj]});
                    } else {
                        q.push({i+di,j+dj});
                    }
                }
            }
        }
    }

//    cout << si << ' ' << sj << '\n';
//    for(auto&[x,y,dd]:al[{si,sj}]){
//        cout << x << ',' << y << ',' << dd << ' ';
//    }
//    cout << '\n';
//    vector<string> g = grid;
//    for(int i=0; i<m; i++){
//        for(int j=0; j<n; j++){
//            if(d[i][j]>=0) g[i][j] = ' ';
//        }
//        g[si][sj] = 'X';
//        cout << g[i] << '\n';
//    }
}

void dfs2(pair<int,int> p, set<pair<int,int>> &vis, int depth, vector<pair<int,int>>&path){
//    cout << p.first << ',' << p.second << "\n";
    if(p.first==m-1 && p.second==n-2) {
        ans = max(ans, depth);
//        cout << depth << ' ' << ans << '\n';
//        for(auto&[x,y]:path) cout << x << ',' << y << ' '; cout << '\n';
        return;
    }
//    cout << al[p].size() << '\n';
    vis.insert(p);
    path.push_back(p);
    for(auto&[x,y,d]:al[p]){
//        cout << x << ',' << y << ',' << d << '\n';
        if(!vis.count({x,y})){
            dfs2({x,y}, vis, depth+d, path);
        }
    }
    path.pop_back();
    vis.erase(p);
}

int main()
{
//    freopen("test.txt", "r", stdin);
    freopen("input.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    string line;
    while (getline(cin,line)) {
        grid.push_back(line);
    }
    m = grid.size();
    n = grid[0].size();
    dfs(0,1,0);

    cout << ans << '\n';

    // compress the graph into the junctions
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] != '#') grid[i][j] = '.';
        }
    }

    deg.assign(m, vector<int>(n,0));
    junctions.push_back({0,1});
    for(int i=0; i<m ;i++){
        for(int j=0; j<n; j++){
            if(grid[i][j]=='.'){
                for(auto&[di,dj]:d4){
                    if(0<=i+di && i+di<m && 0<=j+dj && j+dj<n){
                        deg[i][j] += grid[i+di][j+dj]=='.';
                    }
                }
            }
            if(deg[i][j]>=3) {
//                cout << i << ',' << j << '\n';
                junctions.push_back({i,j});
            }
        }
    }
    junctions.push_back({m-1,n-2});
    cout << m << 'X' << n << " into " << junctions.size() << '\n';
    for(int i=0; i<junctions.size(); i++){
        auto&[ii,jj] = junctions[i];
        getDist(ii,jj);
    }
//    for(auto&[p1,v]:al){
//        cout << p1.first << ',' << p1.second << ": ";
//        for(auto&[x,y,d]:v) cout << x << ',' << y << ',' << d << ' ';
//        cout << '\n';
//    }
    set<pair<int,int>> vis;
    vector<pair<int,int>> path;
    dfs2({0,1},vis,0,path);
    cout << ans << '\n';
}
