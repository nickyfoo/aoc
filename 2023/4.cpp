#include <bits/stdc++.h>

using namespace std;

unordered_set<int> parse(string&line){
    stringstream ss(line);
    string s;
    unordered_set<int> ans;
    while(ss >> s){
        ans.insert(stoi(s));
    }
    return ans;
}

int points(string&line){
    line = line.substr(line.find(':')+2);
    stringstream ss(line);
    string s;
    getline(ss,s,'|');
    cout << line << ": " << s << '\n';
    unordered_set<int> a,b;
    a = parse(s);
    getline(ss,s,'|');
    cout << line << ": " << s << '\n';
    b = parse(s);
    int ct = 0;
    for(auto&x:a){
        if(b.find(x)!=b.end()) ct++;
    }
//    return ct ? 1<<(ct-1) : 0;
    return ct;
}

int main(){
    string line;
//    int ans = 0;
//    while(getline(cin,line)){
//        ans += points(line);
//    }
    vector<string> grid;
    while(getline(cin,line)){
        grid.push_back(line);
    }
    vector<long long> ans(grid.size(),1);
    for(int i=0; i<grid.size(); i++){
        int lim = points(grid[i]);
        for(int j=0; j<lim; j++){
            ans[i+1+j] += ans[i];
            cout << i << "->" << i+1+j << endl;
        }
        for(auto&x:ans) cout << x << ' '; cout << '\n';
    }
    for(auto&x:ans) cout << x << '\n';
    cout << accumulate(ans.begin(), ans.end(),0LL);

}
