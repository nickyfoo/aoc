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

unordered_map<string,set<string>> al;
unordered_map<string,int> deg;
set<string> vis;

// returns cc,has t
pair<int,int> dfs(string s){
    cout << s << endl;
    vis.insert(s);
    int ans = 1;
    int hasT = s[0]=='t';
    for(auto&v:al[s]){
        if(!vis.count(v)) {
            auto [sz,hast] = dfs(v);
            ans += sz;
            hasT |= hast;
        }
    }
    return {ans,hasT};

}

vector<string> best;

void trav(vector<string>&coms, int pos, vector<string>&chosen){
//    cout << pos << endl;
    if(pos==coms.size()) return;
    bool valid = true;
    for(auto&x:chosen){
        if(!al[coms[pos]].contains(x)) {
            valid = false;
            break;
        }
    }
    if(valid){
        chosen.push_back(coms[pos]);
        if(chosen.size() > best.size()) best = chosen;
        trav(coms,pos+1,chosen);
        chosen.pop_back();
    }
    trav(coms, pos+1, chosen);
}

int N = 70;

vector<string> grid;
bool f(){

    queue<pair<int,int>> q;
    vector<vector<int>> d(N+1, vector<int>(N+1,INT_MAX));
    q.push({0,0});
    d[0][0]=0;
    while(q.size()){
        auto [i,j] = q.front(); q.pop();
//        cout << i << ' ' << j << endl;
        for(auto&[di,dj]:d4){
            if(0<=i+di &&i+di<=N&& 0<=j+dj && j+dj<=N){
                if(grid[i+di][j+dj]!='#' && d[i+di][j+dj]==INT_MAX){
                    d[i+di][j+dj] = d[i][j]+1;
                    q.push({i+di,j+dj});
                }
            }
        }
    }
    return d[N][N] != INT_MAX;
}

int main(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
    string line;

    grid.assign(N+1,string(N+1,'.'));;
//    int lim = 1024;
    while(getline(cin,line)){
        vector<ll> v = split(line,',');
        grid[v[0]][v[1]]= '#';
        if(!f()) {
            cout << "~~~~~~~~~~~~~~~" << line << endl;
            break;
        }
    }

    // to ignore the rest of input after termination LOL
    while(true){
        cin.get();
    }

}
