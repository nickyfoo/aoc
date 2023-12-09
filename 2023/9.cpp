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

ll process(vector<ll> v){
    vector<vector<ll>> diffs;
    diffs.push_back(v);
    do {
        vector<ll> inter;
        for(int i=1; i<diffs.back().size(); i++){
            inter.push_back(diffs.back()[i]-diffs.back()[i-1]);
        }
        diffs.push_back(inter);
        auto [mn,mx] = minmax_element(inter.begin(), inter.end());
        if(*mn==0 && *mx==0){
            break;
        }
    }while(true);
    for(int i=diffs.size()-2; i>=0; i--){
//        diffs[i].back() += diffs[i+1].back();
        diffs[i][0] -= diffs[i+1][0];
    }
//    return diffs[0].back();
    return diffs[0][0];
}

int main(){
    string line;
    long long ans = 0;
    while(getline(cin,line)){
        ans += process(parse(line));
    }
    cout << ans;
}
