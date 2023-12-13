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

vector<ll> process(vector<string>&grid){
    int m=grid.size(), n=grid[0].size();
    vector<ll> lines;
    for(int i=0; i+1<m; i++){
        bool valid = true;
        for(int di=0; valid && i-di>=0 && i+1+di<m; di++){
            for(int j=0; valid && j<n; j++){
                if(grid[i-di][j] != grid[i+1+di][j]) valid = false;
            }
        }
        if(valid) lines.push_back(100*(i+1));
    }

    for(int j=0; j+1<n; j++){
        bool valid = true;
        for(int dj=0; valid && j-dj>=0 && j+1+dj<n; dj++){
            for(int i=0; valid && i<m; i++){
                if(grid[i][j-dj] != grid[i][j+1+dj]) valid = false;
            }
        }
        if(valid) lines.push_back(j+1);
    }
    return lines;
}

ll process2(vector<string>&grid){
    int m=grid.size(), n=grid[0].size();
    ll line = process(grid)[0];
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j]=='.') grid[i][j] = '#';
            else grid[i][j] = '.';
            vector<ll> line2 = process(grid);
            line2.erase(remove(line2.begin(), line2.end(), line), line2.end());
            if(line2.size()) return line2[0];
            if(grid[i][j]=='.') grid[i][j] = '#';
            else grid[i][j] = '.';
        }
    }
    return 0;
}

int main(){
    string line;
    long long ans = 0;
    vector<string> grid;
    while(getline(cin,line)){
        if(line.size()){
            grid.push_back(line);
        } else {
            ans += process2(grid);
            grid.clear();
        }
    }
    ans += process2(grid);
    cout << ans;
}
