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


vector<int> split(const string&line){
    stringstream ss(line);
    string s;
    vector<int> ans;
    while(getline(ss,s,' ')){
        if(!s.empty()) ans.push_back(stoi(s));
    }
    return ans;
}

bool isSafe(const vector<int>&v){
    bool hasIncrease=false, hasDecrease=false;
    for(int i=1; i<v.size(); ++i){
        if(v[i] > v[i-1]) hasIncrease = true;
        else if(v[i] < v[i-1]) hasDecrease = true;
        else return false;
    }
    if(hasIncrease && hasDecrease) return false;
    set<int> s;
    for(int i=1; i<v.size(); ++i){
        s.insert(v[i]-v[i-1]);
    }
    for(auto&x:s){
        if(abs(x)<1 || abs(x)>3) return false;
    }
    return true;
}

bool isSafe2(vector<int> v){
    if(isSafe(v)) return true;

    for(int i=0; i<v.size(); ++i){
        vector<int> v2 = v;
        v2.erase(v2.begin()+i);
        if(isSafe(v2)) return true;
    }
    return false;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int ans = 0;
    string line;
    while(getline(cin, line)){
        ans += isSafe2(split(line));
    }
    cout << ans;
}
