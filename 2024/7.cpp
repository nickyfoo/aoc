#pragma GCC optimize ("O3")
#include <ranges>
#include <vector>
#include <string>
#include <sstream>
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
        if(!s.empty()) ans.push_back(stoi(s));
    }
    return ans;
}

bool eval(vector<ll>&v, ll curr, int pos, ll tgt){
    if(pos==v.size()){
        return curr==tgt;
    }
    if(curr + v[pos] <= tgt && eval(v,curr+v[pos],pos+1,tgt)) return true;
    if(curr*v[pos] <= tgt && eval(v,curr*v[pos],pos+1, tgt)) return true;
    ll nxt = stoll(to_string(curr) + to_string(v[pos]));
    if(nxt<=tgt && eval(v, nxt, pos+1, tgt)) return true;
    return false;
}

bool can(ll t, vector<ll>&v){
    vector<ll> curr;
    return eval(v,v[0],1,t);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll ans = 0;
    string line;
    while(getline(cin, line)){
        stringstream ss(line);
        string t, src;
        getline(ss,t,':');
        getline(ss,src,':');
        ll tgt = stoll(t);
        vector<ll> v = split(src,' ');
        if(can(tgt,v)) {
            ans += tgt;
            cout << ans << ' ' << tgt << endl;
        }
    }
    cout << ans;
}
