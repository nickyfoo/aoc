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
string instructions;
unordered_map<string,pair<string,string>> al;

int numSteps(string curr){
    int steps = 0;
    int n = instructions.size();

    while(curr[2]!='Z'){
        if(instructions[steps%n]=='R')curr = al[curr].second;
        else curr = al[curr].first;
        steps++;
    }
    return steps;
}

int main(){
    getline(cin,instructions);
    string line;
    getline(cin,line);
    queue<string> q;
    while(getline(cin,line)){
        string u = line.substr(0,3);
        string l = line.substr(7,3);
        string r = line.substr(12,3);
        al[u]={l,r};
        if(u[2]=='A') q.push(u);
    }

    vector<ll> steps;
    while(q.size()){
        auto u = q.front(); q.pop();
        steps.push_back(numSteps(u));
    }
    ll ans = steps[0];
    for(int i=1; i<steps.size(); i++){
        ans = (ans*steps[i])/gcd(ans,steps[i]);
    }
    cout << ans;
}
