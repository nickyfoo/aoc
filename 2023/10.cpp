#include <bits/stdc++.h>

using namespace std;
using ll = long long;

vector<ll> parse(string&line){
    stringstream ss(line);
    vector<ll> ans;
    ll x;
    while(ss>>x){
        ans.push_back(x);
    }
    return ans;
}
vector<pair<int,int>> d4{{-1,0},{1,0},{0,-1},{0,1}};
vector<pair<int,int>> d8{{-1,-1},{-1,0},{-1,1},{1,-1},{1,0},{1,1},{0,-1},{0,1}};
unordered_map<char,int> out,in;


ll process(vector<string>&grid){
    int m = grid.size();
    int n = grid[0].size();
    pair<int,int> s;
    vector<vector<int>> d(m, vector<int>(n,-1));
    queue<pair<int,int>> q;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j]=='S'){
                s = {i,j};
                d[i][j]=0;
                q.push({i,j});
            }
        }
    }

    // bfs from S to find main loop
    while(q.size()){
        auto [i,j] = q.front(); q.pop();
        for(int k=0; k<4; k++){
            auto&[di,dj] = d4[k];
            if(0<=i+di && i+di<m && 0<=j+dj && j+dj<n && d[i+di][j+dj]==-1){
                if(out[grid[i][j]]&(1<<k)
                   && ((in[grid[i+di][j+dj]]) & (1<<k))
                   && out[grid[i][j]] & in[grid[i+di][j+dj]]) {
                    d[i+di][j+dj] = d[i][j]+1;
                    q.push({i+di,j+dj});
                }
            }
        }
    }

    // clear out main loop
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(d[i][j]>-1){
                grid[i][j] = 'X';
            } else {
                grid[i][j] = '.';
            }
        }
    }

    for(int i=0; i<m; i++){
        cout << grid[i] << '\n';
    }

    // find the furthest in main loop for part 1
    int ans = -1;
    for(int i=0; i<m; i++){
        ans = max(ans, *max_element(d[i].begin(), d[i].end()));
    }
    return ans;
}

// pad a row for expansion
string getRow(vector<string>&grid, int i){
    int m = grid.size();
    int n = grid[0].size();
    string inter = "";
    inter += grid[i][0];
    for(int j=1; j<n; j++){
        if(out[grid[i][j-1]]&8 && in[grid[i][j]]&8 ) inter += '-';
        else inter += '.';
        inter += grid[i][j];
    }
    return inter;
}

// pad the grid for expansion
vector<string> blowup(vector<string>&grid){
    int m = grid.size();
    int n = grid[0].size();
    vector<string> ans;
    ans.push_back(getRow(grid,0));
    for(int i=1; i<m; i++){
        string row = getRow(grid,i);
        string inter = "";
        for(int j=0; j<row.size(); j++){
            if(out[ans.back()[j]]&2 && in[row[j]]&2) inter += '|';
            else inter += '.';
        }
        ans.push_back(inter);
        ans.push_back(getRow(grid,i));
    }
    return ans;
}

ll process2(vector<string>&grid){
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> vis(m, vector<int>(n,0));

    // bfs on exterior points
    queue<pair<int,int>> q;
    for(int i=0; i<m; i++){
        if(grid[i][0]=='.'){
            q.push({i,0});
            vis[i][0] = 1;
        }
        if(grid[i][n-1]=='.'){
            q.push({i,n-1});
            vis[i][n-1] = 1;
        }
    }
    for(int j=0; j<n; j++){
        if(!vis[0][j] && grid[0][j]=='.'){
            q.push({0,j});
            vis[0][j] = 1;
        }
        if(!vis[m-1][j] && grid[m-1][j]=='.'){
            q.push({m-1,j});
            vis[m-1][j] = 1;
        }
    }

    while(q.size()){
        auto [i,j] = q.front(); q.pop();
        int deg = 0;
        for(auto&[di,dj]:d8){
            if(0<=i+di && i+di<m && 0<=j+dj && j+dj<n){
                if(grid[i+di][j+dj]=='.') {
                    vis[i][j]++;
                    if(!vis[i+di][j+dj]){
                        vis[i+di][j+dj] = 1;
                        q.push({i+di,j+dj});
                    }
                }
            }
        }
    }

    // clear out exterior points
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(vis[i][j]) grid[i][j] = ' ';
        }
    }
    for(int i=0; i<m; i++){
        cout << grid[i] << '\n';
    }

    // initial spaces are now groups of 3x3 '.'
    int ans = 0;
    for(int i=2; i<m; i+=2){
        for(int j=2; j<n; j+=2){
            int deg = 1;
            if(grid[i][j]=='.'){
                for(auto&[di,dj]:d8){
                    if(grid[i+di][j+dj]=='.'){
                        deg++;
                    }
                }
            }
            if(deg==9) {
                ans++;
                grid[i][j] = '*';
            }
        }
    }
    for(int i=0; i<m; i++){
        cout << grid[i] << '\n';
    }
    return ans;

}

int main(){
    out['|'] = 1 | 2;
    in['|'] = 1 | 2;

    out['-'] = 4 | 8;
    in['-'] = 4 | 8;

    out['L'] = 1 | 8;
    in['L'] = 2 | 4;

    out['J'] = 1 | 4;
    in['J'] = 2 | 8;

    out['7'] = 2 | 4;
    in['7'] = 1 | 8;

    out['F'] = 2 | 8;
    in['F'] = 1 | 4;

    out['S'] = 1 | 2 | 4 | 8;
    in['S'] = 1 | 2 | 4 | 8;

    vector<string> grid;
    string line;
    while(getline(cin,line)) {
        grid.push_back(line);
    }
    // for second part, blow up the grid so that there are non-zero spaces.
    grid = blowup(grid);
    // find the main loop
    cout << process(grid);
    // bfs to clear out exterior points
    cout << process2(grid);

}
