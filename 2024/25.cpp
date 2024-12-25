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

bool matches(const vector<int>&l, const vector<int>&k){
    for(int i=0; i<5; ++i){
        if(l[i]+k[i]>5) return false;
    }
    return true;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    set<vector<int>> locks,keys;
    string line;

    vector<string> grid;
    while(getline(cin,line)){
        if(line.empty()) {
            if(grid[0] == string(5,'#')){
                vector<int> v(5,0);
                for(int i=1; i<7; ++i){
                    for(int j=0; j<5; ++j){
                        if(grid[i][j]=='#') v[j]++;
                    }
                }
                locks.insert(v);
            } else {
                vector<int> v(5,0);
                for(int i=0; i<6; ++i){
                    for(int j=0; j<5; ++j){
                        if(grid[i][j]=='#') v[j]++;
                    }
                }
                keys.insert(v);
            }
            grid.clear();
        } else {
            grid.push_back(line);
        }
    }

    for(auto&l:locks){
        for(auto&x:l) cout << x << ','; cout << endl;
    }

    for(auto&l:keys ){
        for(auto&x:l) cout << x << ','; cout << endl;
    }

    ll ans = 0;
    for(auto&l:locks){
        for(auto&k:keys){
            ans += matches(l,k);
        }
    }
    cout << ans << endl;
}
