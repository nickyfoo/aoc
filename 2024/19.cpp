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

unordered_set<string> towels;

vector<ll> m;
ll possible(string&s, int i){
    if(i==s.size()) return 1;
    ll &ans = m[i];
    if(ans!=-1) return ans;
    ans = 0;
    for(auto&towel:towels){
        if(s.substr(i,towel.size()) == towel){
            ans += possible(s,i+towel.size());
        }
    }
    return ans;
}

int main(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
    string line;
    getline(cin,line);
    stringstream ss(line);
    vector<string> v;
    string s;
    while(ss>>s){
        if(s.back()==',') s.pop_back();
        v.push_back(s);
        towels.insert(s);
    }



    getline(cin,line);

    long long ans = 0;
    while(getline(cin,line)){
        m.assign(line.size(),-1);
        ans += possible(line,0);
    }

    cout << ans << endl;


}
