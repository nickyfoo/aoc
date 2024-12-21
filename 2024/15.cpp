#pragma GCC optimize ("O3")
#include <ranges>
#include <vector>
#include <string>
#include <sstream>
#include<unordered_map>
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
        if(!s.empty()) ans.push_back(stoll(s));
    }
    return ans;
}

string dir = "^>v<";
vector<pair<int,int>> d4{{-1,0},{0,1},{1,0},{0,-1}};

int x,y;
vector<string> grid;

void mvlr(int dir){
    const auto&[dx,dy] = d4[dir];
    int k = 1;
    while(true){
        if(0<= x+k*dx && x+k*dx<grid.size() && 0<=y+k*dy && y+k*dy<grid[0].size()){
            if(grid[x+k*dx][y+k*dy]=='.') {
                for(int i=k; i>0; --i){
//                    cout << "mv: " << x+i*dx << ' ' << y+i*dy << ' ' << x+(i-1)*dx << ' ' << y+(i-1)*dy << endl;
                    swap(grid[x+i*dx][y+i*dy], grid[x+(i-1)*dx][y+(i-1)*dy]);
                }
                x += dx;
                y += dy;
                return;
            }else if(grid[x+k*dx][y+k*dy]=='#'){
                return;
            }
        } else {
            return;
        }
        ++k;
    }
    return;
}

void mvud(int dir){
    const auto&[dx,dy] = d4[dir];
    int k = 1;
    vector<set<int>> attSets;
    attSets.push_back({y});
    while(true){
        set<int> nxtAttSet = attSets.back();
        int spaces = 0;
        for(auto&yy:attSets.back()){
            if(grid[x+k*dx][yy] == '#') return;
            else if(grid[x+k*dx][yy]=='['){
                nxtAttSet.insert(yy+1);
            } else if(grid[x+k*dx][yy]==']'){
                nxtAttSet.insert(yy-1);
            } else {
                nxtAttSet.erase(yy);
                spaces++;
            }
        }
//        cout << "found"<<endl;
        attSets.push_back(nxtAttSet);
        ++k;
        if(nxtAttSet.empty()){
//                cout << "kis:" << k<<endl;
//            for(int i=0; i<attSets.size(); ++i){
//                cout << i << ":";
//                for(auto&x:attSets[i]) cout <<x <<','; cout << endl;
//            }
            for(int i=k-1; i>0; --i){
                for(auto&yy:attSets[i-1]){
//                        cout <<x+i*dx<< ' ' << yy << ' ' << x+(i-1)*dx << ' ' << yy << endl;
                    swap(grid[x+i*dx][yy],grid[x+(i-1)*dx][yy]);
                }
            }
            x += dx;
            return;
        }

    }
    return;
}


int main(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
    string line;
    while(getline(cin,line)){
        if(line.empty()) break;
        string expLine;
        for(auto c:line){
            if(c=='#') expLine +="##";
            else if(c=='O') expLine += "[]";
            else if(c=='.') expLine += "..";
            else expLine += "@.";
        }
        grid.push_back(expLine);
    }
    for(int i=0; i<grid.size(); ++i){
        for(int j=0; j<grid[0].size(); ++j){
            if(grid[i][j]=='@') {
                x=i; y=j;
            }
        }
    }

    while(getline(cin,line)){
        for(auto&c:line){
            int d = dir.find(c);
            if(c=='<' || c=='>') mvlr(dir.find(c));
            else mvud(dir.find(c));
//            cout << dir[d] << ":\n";
//            for(auto&x:grid) cout << x << '\n'; cout << endl;
        }
    }

    ll ans = 0;
    for(int i=0; i<grid.size(); ++i){
        for(int j=0; j<grid[0].size(); ++j){
            if(grid[i][j]=='[') {
                cout << 100*i + j << endl;
                ans += 100*i+j;
            }
        }
    }
    cout << ans << endl;

}

