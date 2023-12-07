#include <bits/stdc++.h>

using namespace std;
using ll = long long;

vector<ll> parse(string&line){
    stringstream ss(line);
    ll x;
    vector<ll> ans;
    while(ss >> x){
        ans.push_back(x);
    }
    return ans;
}

ll convert(ll src, map<pair<ll,ll>, ll, greater<>>&m) {
    auto it = m.lower_bound({src,INT_MAX});
    if(it!=m.end()){
//        cout << src << ' ' << it->first.first << ' ' << it->first.second << ' ' << it->second << '\n';
        if(it->first.first + it->first.second >= src){
            return src-it->first.first + it->second;
        }
    }
    return src;
}

// src in the form {start,end};
vector<pair<ll,ll>> convert(pair<ll,ll> src, map<pair<ll,ll>, ll, greater<>>&m) {
    vector<pair<ll,ll>> ans;
    for(auto&[msl,mdst]:m){
        auto &[msrc,mlen] = msl;
        ll s = max(msrc, src.first);
        ll e = min(msrc+mlen-1,src.second);
        if(s<=e) ans.push_back({s-msrc+mdst,e-msrc+mdst});
    }
    return ans;
}

void addIdentity(map<pair<ll,ll>, ll, greater<>>&m){
    vector<pair<ll,ll>> toAdd;
    ll prevVal = 1e15;
    for(auto&[msl,mdst]:m){
        auto &[msrc,mlen] = msl;
//        cout << "~~~" << prevVal << ' ' << msrc << ' ' << mlen << ' ' << mdst << '\n';
        if(prevVal > msrc + mlen) {
            toAdd.push_back({msrc+mlen,prevVal-msrc-mlen});
        }
        prevVal = msrc;
    }
    if(prevVal > 0){
        toAdd.push_back({0,prevVal});
    }
    for(auto&[src,len]:toAdd){
        m[{src,len}]=src;
    }
}

int main(){
    string line;
    // each mapping shd be a map of pair.
    string seedLine;
    getline(cin,seedLine);
    seedLine = seedLine.substr(seedLine.find(':')+2);
    vector<ll> seeds = parse(seedLine);
    vector<map<pair<ll,ll>, ll, greater<>>> maps;
    map<pair<ll,ll>,ll, greater<>> m;
    getline(cin,line);
    getline(cin,line);
    while(getline(cin,line)){
        if(line.find("map")!=-1){
            addIdentity(m);
            maps.push_back(m);
            m.clear();
        } else {
            stringstream ss(line);
            ll dst, src, len;
            ss >> dst >> src >> len;
            m[{src,len}] = dst;
        }
    }

    addIdentity(m);
    maps.push_back(m);

    ll ans = 1e15;
//    for(auto&seed:seeds){
//        ll currVal = seed;
//        cout << seed << ": ";
//        for(auto&mapper:maps){
//            currVal = convert(currVal, mapper);
//            cout << currVal << ' ';
//        }
//        cout << '\n';
//        ans = min(ans,currVal);
//    }
    vector<pair<ll,ll>> curr;
    for(int i=0; i<seeds.size(); i+=2){
        curr.push_back({seeds[i],seeds[i]+seeds[i+1]-1});
    }
    for(auto it = maps.begin(); it!=maps.end(); ++it){
//        for(auto&[msl,mdst]:*it){
//            auto &[msrc,mlen] = msl;
//            cout << msrc << ' ' << mlen << ' ' << mdst << '\n';
//        }
//        cout << "CURR:";
//        for(auto&[a,b]:curr){
//            cout << a << ',' << b << ' ';
//        } cout << '\n';

        vector<pair<ll,ll>> inter;
        for(auto&c:curr){
            for(auto&x:convert(c,*it)){
                inter.push_back(x);
            }
        }
        if(next(it) == maps.end()){
            for(auto&[s,e]:inter){
                ans = min(ans,s);
            }
        }
        swap(inter,curr);
    }

    cout << ans;
}
