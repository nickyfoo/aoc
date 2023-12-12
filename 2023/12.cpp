#include <bits/stdc++.h>

using namespace std;

using ll = long long;

vector<int> split(string&x){
    stringstream ss(x);
    string s;
    vector<int> v;
    while(getline(ss,s,',')){
        v.push_back(stoi(s));
    }
    return v;
}
ll memo[150][50][20]{};

ll process(string&x, vector<int>&v, int i, int j, int curr){
    if(j==v.size() && curr) return 0;
    if(i==x.size()){
        if(curr){
            if(j<v.size() && curr==v[j]) return process(x,v,i,j+1,0);
            return 0;
        } else return (j==v.size());
    }
    ll &ans = memo[i][j][curr];
    if(ans!=-1) return ans;
    ans = 0;
    if(x[i]=='#'){
        if(j<v.size() && curr+1<=v[j]) ans += process(x,v,i+1,j,curr+1);
    } else if(x[i]=='.'){
        if(j<v.size() && curr==v[j]) ans += process(x,v,i+1,j+1,0);
        else if(!curr) ans += process(x,v,i+1,j,curr);
    } else {
//        x[i] = '#';
        if(j<v.size() && curr+1<=v[j])ans += process(x,v,i+1,j,curr+1);
//        x[i] = '.';
        if(j<v.size() && curr==v[j]) ans += process(x,v,i+1,j+1,0);
        else if(!curr) ans += process(x,v,i+1,j,curr);
//        x[i] = '?';
    }
    return ans;
}

ll parse(string&line){
    stringstream ss(line);
    string x, y;
    ss >> x >> y;
    vector<int> v = split(y);
    string xx = "";
    vector<int> vv;
    for(int i=0; i<5; i++){
        xx += x;
        if(i!=4) xx += '?';
        for(auto&vx:v) vv.push_back(vx);
    }
    return process(xx, vv, 0,0,0);
}


int main(){
    string line;
    ll ans = 0;
    while(getline(cin,line)){
        for(int i=0; i<150; i++){
            for(int j=0; j<50; j++){
                for(int k=0; k<20; k++){
                    memo[i][j][k] = -1;
                }
            }
        }
        ll v = parse(line);
        ans += v;
    }
    cout << (ans);
}
