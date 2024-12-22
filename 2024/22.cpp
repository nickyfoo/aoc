#pragma GCC optimize ("O3")
#include <ranges>
#include <vector>
#include <string>
#include <sstream>
#include<unordered_map>
#include <set>
#include <map>
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

string dir = "^>v<";
vector<pair<int,int>> d4{{-1,0},{0,1},{1,0},{0,-1}};
const long long MOD = 16777216;

map<vector<int>, int> ans;

void f(ll x){

    vector<int> p{x%10};
    for(int i=0; i<2000; ++i){
        ll y = x*64;
        x  ^= y;
        x %= MOD;
        ll z = x/32;
        x ^= z;
        x %= MOD;
        ll a = x*2048;
        x ^= a;
        x %= MOD;
        p.push_back(x%10);
    }

    map<vector<int>, int> m;
    for(int i=4; i<p.size(); ++i){
        vector<int> inter;
        for(int j=i-3; j<=i; ++j){
            inter.push_back(p[j]-p[j-1]);
        }
        m.insert({inter,p[i]});
    }
    for(auto&[k,v]:m){
        ans[k]+=v;
    }
}

int main(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
    string line;
    while(getline(cin,line)){
        f(stoll(line));
    }
    ll x = 0;
    for(auto&[k,v]:ans) {
        x = max<ll>(x,v);
    }
    cout << x << endl;
}

