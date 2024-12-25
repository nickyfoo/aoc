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

string dirs = ">v<^";
vector<pair<int,int>> d4{{0,1},{1,0},{0,-1},{-1,0}};

vector<string> numericPaths[12][12];
string numericString = "789456123X0A";

vector<string> dirPaths[6][6];
string dirString = "X^A<v>";

int gridDist(int x, int y){
    int xi = x/3, xj = x%3;
    int yi = y/3, yj = y%3;
    return abs(xi-yi) + abs(xj-yj);
}

void genNumericPaths(int x, int s, int t, string&curr){
    if(x==t){
        curr += 'A';
        numericPaths[s][t].push_back(curr);
        curr.pop_back();
        return;
    }
    int i = x/3, j=x%3;
    for(int d=0; d<4; ++d){
        const auto&[di,dj]=d4[d];
        if(0<=i+di && i+di<4 && 0<=j+dj && j+dj<3){
            int y = (i+di)*3 + j+dj;
            if(y==9) continue;
            if(gridDist(x,t) <= gridDist(y,t)) continue;
            curr += dirs[d];
            genNumericPaths(y,s,t,curr);
            curr.pop_back();
        }
    }
    return;
}


void genDirPaths(int x, int s, int t, string&curr){
    if(x==t){
        curr += 'A';
        dirPaths[s][t].push_back(curr);
        curr.pop_back();
        return;
    }
    int i = x/3, j=x%3;
    for(int d=0; d<4; ++d){
        const auto&[di,dj]=d4[d];
        if(0<=i+di && i+di<2 && 0<=j+dj && j+dj<3){
            int y = (i+di)*3 + j+dj;
            if(y==0) continue;
            if(gridDist(x,t) <= gridDist(y,t)) continue;
            curr += dirs[d];
            genDirPaths(y,s,t,curr);
            curr.pop_back();
        }
    }
    return;
}

// build it backwards, storing the cost to go from a to b.
int main(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
    for(int i=0; i<12; ++i){
        for(int j=0; j<12; ++j){
            if(i==9 || j==9) continue;
            string curr;
            genNumericPaths(i,i,j,curr);
            cout << i << " to " << j << ": ";
            for(auto&x:numericPaths[i][j]) cout << x << ','; cout << endl;
        }
    }


    for(int i=0; i<6; ++i){
        for(int j=0; j<6; ++j){
            if(i==0 || j==0) continue;
            string curr;
            genDirPaths(i,i,j,curr);
            cout << i << " to " << j << ": ";
            for(auto&x:dirPaths[i][j]) cout << x << ','; cout << endl;
        }
    }

    vector<vector<vector<ll>>> dirCosts;
    vector<vector<ll>> v(6, vector<ll>(6, 1e18));
    for(int i=0; i<6; ++i){
        for(int j=0; j<6; ++j){
            if(dirPaths[i][j].size()) v[i][j] = dirPaths[i][j][0].size();
        }
    }
    dirCosts.push_back(v);

//    int numLayers = 2;
    int numLayers = 25;
    for(int i=0; i<numLayers-1; ++i){
        vector<vector<ll>> dirCost(6, vector<ll>(6, 1e18));
        for(int i=0; i<6; ++i){
            for(int j=0; j<6; ++j){
                for(auto&path:dirPaths[i][j]){
                    ll inter = 0;
                    int curr = 2;
                    for(auto c:path){
                        int pos = dirString.find(c);
                        inter += dirCosts.back()[curr][pos];
                        curr = pos;
                    }
                    dirCost[i][j] = min(dirCost[i][j], inter);
                }
            }
        }
        dirCosts.push_back(dirCost);
    }

    vector<vector<ll>> numericCost(12, vector<ll>(12, 1e18));
    for(int i=0; i<12; ++i){
        for(int j=0; j<12; ++j){
            for(auto&path:numericPaths[i][j]){
                ll inter = 0;
                int curr = 2;
                for(auto c:path){
                    int pos = dirString.find(c);
                    inter += dirCosts.back()[curr][pos];
                    curr = pos;
                }
                numericCost[i][j] = min(numericCost[i][j], inter);
            }
        }
    }

    string line;
    ll ans = 0;
    while(getline(cin,line)){
        ll inter = 0;
        int curr = 11;
        for(auto c:line){
            int pos = numericString.find(c);
            inter += numericCost[curr][pos];
            curr = pos;
        }
        line.pop_back();
        cout << inter << ' ' << stoll(line) << endl;
        ans += inter*stoll(line);
    }
    cout << ans << endl;
}
