#include <bits/stdc++.h>

using namespace std;

int getNum(string&s){
    int ans = 0;
    for(auto&c:s){
        if(isdigit(c)){
            ans *= 10;
            ans += c-'0';
        } else {
            if(ans) return ans;
        }
    }
    return -1;
}

vector<int> eval(vector<string> toks){
//    for(auto&x:toks){
//        cout << x << ' ';
//    } cout << '\n';
    vector<int> ans(3,0);
    vector<string> colors{"red","green","blue"};
    for(auto&tok:toks){
        stringstream ss(tok);
        string s;
        while(getline(ss,s,',')){
            for(int i=0; i<3; i++){
                const string&color = colors[i];
                if(s.find(color)!=-1){
                    ans[i] = max(ans[i],getNum(s));
                }
            }
        }
    }
    return ans;
}

vector<string> split(string&line){
    stringstream ss(line);
    string s;
    vector<string> toks;
    while(getline(ss,s,';')){
        toks.push_back(s);
    }
    int pos = toks[0].find(':');
    toks[0] = toks[0].substr(pos+2);
    return toks;
}



int main(){
    string line;
    int ans = 0;
    while(getline(cin,line)){
        vector<int> v = eval(split(line));
//        if(v[0]<=12 && v[1]<=13 && v[2]<=14){
//            ans += getNum(line);
//        }
        ans += v[0]*v[1]*v[2];
    }
    cout << ans;

}
