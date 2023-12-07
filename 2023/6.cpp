#include <bits/stdc++.h>

using namespace std;
using ll = long long;

vector<int> parse(string&line){
    stringstream ss(line);
    vector<int> ans;
    int x;
    while(ss>>x){
        ans.push_back(x);
    }
    return ans;
}

int main(){
//    string t,d;
//    getline(cin,t);
//    getline(cin,d);
//    t = t.substr(t.find(':')+1);
//    d = d.substr(d.find(':')+1);

//    vector<int> times = parse(t), dists = parse(d);
//    int ans = 1;
//    for(int i=0; i<times.size(); i++){
//        int inter = 0;
//        for(int j=1; j<=times[i]; j++){
//            if((times[i]-j)*j > dists[i]) inter++;
//        }
//        if(inter) ans*=inter;
//        cout << inter << '\n';
//    }

    ll time = 59688274l;
    ll dist = 543102016641022;
    int ans = 0;
    for(ll i = 1; i<=time; i++){
        if((time-i)*i > dist) ans++;
    }

    cout << ans;
}
