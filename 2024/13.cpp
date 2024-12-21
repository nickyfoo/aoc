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
const ll MOD = 1e9+7;


vector<ll> split(const string&line, char delim){
    stringstream ss(line);
    string s;
    vector<ll> ans;
    while(getline(ss,s,delim)){
        if(!s.empty()) ans.push_back(stoll(s));
    }
    return ans;
}

pair<ll,ll> ParseButton(){
    string line;
    getline(cin,line);
    stringstream ss(line);
    string s;
    vector<string> toks;
    while(ss >> s){
        toks.push_back(s);
    }
    return {stoll(toks[2].substr(2)), stoll(toks[3].substr(2))};
}


pair<ll,ll> ParsePrize(){
    string line;
    getline(cin,line);
    stringstream ss(line);
    string s;
    vector<string> toks;
    while(ss >> s){
        toks.push_back(s);
    }
    return {stoll(toks[1].substr(2)), stoll(toks[2].substr(2))};
}

/**
( ax bx )(a) = (x)
( ay by )(b) = (y)
*/
ll solve(ll ax, ll ay, ll bx, ll by, ll x, ll y){
    ll det = ax*by - ay*bx;
    cout << det << endl;
    if(det==0) return 0;
    ll a = by * x - bx * y;
    ll b = -ay * x + ax * y;
    if(a%det) return 0;
    if(b%det) return 0;
    return a/det*3 + b/det;

//    ll ans = INT_MAX;
//    for(int a=0; a<=100; ++a){
//        for(int b=0; b<=100; ++b){
//            if(a*ax + b*bx == x && a*ay + b*by == y){
//                ans = min<ll>(ans, 3*a+b);
//            }
//        }
//    }
//    return ans == INT_MAX ? 0 : ans;
}

int main(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
    ll ans = 0;
    string line;

    while(true){
        auto [ax,ay] = ParseButton();
        auto [bx,by] = ParseButton();
        auto [x,y] = ParsePrize();
        ll v = solve(ax,ay,bx,by,x+10000000000000,y+10000000000000);
        ans += v;
        cout << v << endl;
        if(!getline(cin,line)) break;
    }
    cout << ans << endl;
}
