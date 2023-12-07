#include <bits/stdc++.h>

using namespace std;

vector<pair<int,int>> d8{{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

int ans = 0;

void process(vector<string>&grid){
    int m = grid.size(), n = grid[0].size();
    for(int i=0; i<grid.size(); i++){
        int currVal = 0;
        bool isPart = false;
        for(int j=0; j<grid[0].size(); j++){
            if(isdigit(grid[i][j])){
                currVal*=10;
                currVal += grid[i][j]-'0';
                for(auto&[di,dj]:d8){
                    if(0<=i+di && i+di<m && 0<=j+dj && j+dj<n){
                        char c = grid[i+di][j+dj];
                        if(!isdigit(c) && c!='.') isPart = true;
                    }
                }
            } else {
//                cout << grid[i] << ' ' << currVal << ' ' << isPart << '\n';
                if(isPart) ans += currVal;
                currVal = 0;
                isPart = false;
            }
        }
        if(isPart) ans += currVal;
    }
}

map<pair<int,int>,vector<int>> gears;

void process2(vector<string>&grid){
    int m = grid.size(), n = grid[0].size();
    for(int i=0; i<grid.size(); i++){
        int currVal = 0;
        bool isPart = false;
        set<pair<int,int>> currGears;
        for(int j=0; j<grid[0].size(); j++){
            if(isdigit(grid[i][j])){
                currVal*=10;
                currVal += grid[i][j]-'0';
                for(auto&[di,dj]:d8){
                    if(0<=i+di && i+di<m && 0<=j+dj && j+dj<n){
                        char c = grid[i+di][j+dj];
                        if(!isdigit(c) && c!='.') isPart = true;
                        if(c=='*'){
                            currGears.insert({i+di,j+dj});
                        }
                    }
                }
            } else {
//                cout << grid[i] << ' ' << currVal << ' ' << isPart << '\n';
                if(isPart) {
                    for(auto&gear:currGears){
                        gears[gear].push_back(currVal);
                    }
                }
                currVal = 0;
                isPart = false;
                currGears.clear();
            }
        }
        if(isPart) {
            for(auto&gear:currGears){
                gears[gear].push_back(currVal);
            }
        }
    }
}

int main(){
    string line;
    vector<string> grid;
    while(getline(cin,line)){
        grid.push_back(line);
    }
//    process(grid);
    process2(grid);
    long long ans = 0;
    for(auto&[gear,val]:gears){
        if(val.size()==2){
            ans += val[0]*val[1];
        }
    }
    cout << ans;

}
