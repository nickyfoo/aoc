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

int main(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
    string line;

    unordered_set<string> c;

    while(getline(cin,line)){
        string s, t;
        s = line.substr(0,2);
        t = line.substr(3,2);
        cout << s << ' ' << t <<endl;
        al[s].insert(t);
        al[t].insert(s);
        deg[s]++;
        deg[t]++;

        c.insert(s);
        c.insert(t);
    }

    vector<string> computers(c.begin(),c.end());
    set<vector<string>> ss;
    for(auto&[u,vvv]:al){
        vector<string> vv(vvv.begin(), vvv.end());
        for(int i=0; i<vv.size(); ++i){
            for(int j=i+1; j<vv.size(); ++j){
                if(al[vv[i]].contains(vv[j])){
                    vector<string> v{u,vv[i],vv[j]};
                    ranges::sort(v);
                    ss.insert(v);
                }
            }
        }
    }

    cout << computers.size() << endl;
    int ans = 0;
    for(auto&x:ss){
//        cout << x[0] << ' ' << x[1] << ' ' << x[2] << endl;
        ans += ((x[0][0]=='t') || (x[1][0]=='t') || (x[2][0]=='t'));
    }

    vector<string> chosen;
    trav(computers,0,chosen);
    ranges::sort(best);
    for(auto&x:best) cout << x <<','; cout << endl;
//    cout << ans << endl;
}
