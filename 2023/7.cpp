#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int hand(string&s){
    int jCount = count_if(s.begin(), s.end(), [](auto c){return c=='J';});
    unordered_map<char,int> m;
    multiset<int> cts;
    for(auto c:s) if(c!='J') m[c]++;
    for(auto&[k,v]:m) cts.insert(v);
    int maxVal = cts.size() ? *cts.rbegin() : 0;
    if(cts.size()) cts.erase(--cts.end());
    cts.insert(maxVal + jCount);
    if(cts.count(5)) return 6;
    if(cts.count(4)) return 5;
    if(cts.count(3) && cts.count(2)) return 4;
    if(cts.count(3)) return 3;
    if(cts.count(2)==2) return 2;
    if(cts.count(2)==1) return 1;
    return 0;
}

//string str = "23456789TJQKA";
string str = "J23456789TQKA";

int main(){
    string line;
    vector<pair<string,ll>> v;
    string s; int x;
    while( cin >> s >> x){
        v.push_back({s,x});
    }
    sort(v.begin(), v.end(), [](auto&a, auto&b){
         int ha = hand(a.first);
         int hb = hand(b.first);
        if(ha==hb){
            for(int i=0; i<5; i++){
                int sa = str.find(a.first[i]);
                int sb = str.find(b.first[i]);
                if(sa<sb) return true;
                if(sa>sb) return false;
            }
         }
         return ha<hb;
     });
     long long ans = 0;
     for(int i=0; i<v.size(); i++){
         cout << v[i].first << ' ' << v[i].second << '\n';
        ans += (i+1)*v[i].second;
     }
     cout << ans;
}
