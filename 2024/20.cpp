#pragma GCC optimize ("O3")
#include <ranges>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
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
vector<vector<int>> fromStart, fromEnd;

int sx,sy,ex,ey;


vector<vector<int>> f(int x, int y){
    vector<vector<int>> d(grid.size(), vector<int>(grid[0].size(), INT_MAX));
    queue<pair<int,int>> q;
    q.push({x,y});
    d[x][y] = 0;
    while(q.size()){
        auto [i,j] = q.front(); q.pop();
        for(auto&[di,dj]:d4){
            if(0<=i+di && i+di<grid.size() && 0<=j+dj && j+dj<grid[0].size()){
                if(grid[i+di][j+dj]!='#' && d[i+di][j+dj]==INT_MAX){
                    d[i+di][j+dj] = d[i][j]+1;
                    q.push({i+di,j+dj});
                }
            }
        }
    }
    return d;
}

vector<tuple<int,int,int>> rad;

int main(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
    string line;
    while(getline(cin,line)){
        grid.push_back(line);
    }

    for(int i=0; i<grid.size(); ++i){
        for(int j=0; j<grid[0].size(); ++j){
            if(grid[i][j]=='S'){
                sx = i; sy = j;
            }
            if(grid[i][j]=='E'){
                ex = i; ey = j;
            }
        }
    }

    // precompute the 20 radius lol
    for(int i=-20; i<=20; ++i){
        for(int j=-20; j<=20; ++j){
            if(abs(i)+abs(j) <= 20) rad.push_back({i,j,abs(i)+abs(j)});
        }
    }

    fromStart = f(sx,sy);
    fromEnd = f(ex,ey);

    int originalDistance = fromStart[ex][ey];
    cout << originalDistance << endl;

    map<int,int> m;
    ll ans =0 ;

    for(int i=0; i<grid.size(); ++i){
        for(int j=0; j<grid[0].size(); ++j){
            //ij is the start.
            if(fromStart[i][j]==INT_MAX)continue;
            for(auto&[di,dj,r]:rad){
                if(0<=i+di && i+di<grid.size() &&0<=j+dj &&j+dj<grid[0].size()){
                    if(fromEnd[i+di][j+dj]==INT_MAX)continue;
                    int newDist = fromStart[i][j] + fromEnd[i+di][j+dj] + r;
//                    if(newDist > originalDistance) cout << i << ' ' << j << ' ' << newDist << ' ' << originalDistance << endl;
                    m[originalDistance-newDist]++;
                    if(originalDistance - newDist >= 100) ans++;
                }
            }
        }
    }
    for(auto&[k,v]:m) {
        cout << k << " saved by " << v << endl;
    }
    cout << ans << endl;;


//    int orig = f();
//    int ans = 0;
//    for(int i=0; i<grid.size(); ++i){
//        for(int j=0; j<grid[0].size(); ++j){
//            if(grid[i][j]=='#'){
//                grid[i][j]='.';
//                int change = f();
//                if(orig-change >= 100) ans++;
//                grid[i][j] = '#';
//            }
//        }
//    }
    cout << ans << endl;


}
