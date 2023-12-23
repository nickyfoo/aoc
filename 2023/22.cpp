#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <numeric>
using namespace std;
using ll = long long;

string dirs = "RDLU";
vector<pair<int,int>> d4 {{0,1},{1,0},{0,-1},{-1,0}};
struct Brick {
    int x1, y1, z1, x2, y2, z2;

    friend ostream& operator<<(ostream& out, const Brick&brick){
        out << "Brick(" << brick.x1 << ',' << brick.y1 << ',' << brick.z1 << ',' << brick.x2 << ',' << brick.y2 << ',' << brick.z2 <<")";
        return out;
    }
};

vector<set<int>> al;
vector<set<int>> g_supporting, g_supported;
int n;
vector<set<pair<int,int>>> lineSet;
map<int,map<pair<int,int>,int>> layers;

vector<Brick> bricks;

vector<int> split(string&line){
    vector<int> ans;
    stringstream ss(line);
    string s;
    while(getline(ss,s,',')){
        ans.push_back(stoi(s));
    }
    return ans;
}

void parse(string&line){
    stringstream ss(line);
    string s;
    getline(ss,s,'~');
    vector<int> v = split(s);
    getline(ss,s,'~');
    vector<int> vv = split(s);
    bricks.push_back({v[0],v[1],v[2], vv[0], vv[1], vv[2]});
}

void parseBricks(){
    lineSet.resize(n);

    for(int i=0; i<n; i++){
        auto&[ax1,ay1,az1,ax2,ay2,az2] = bricks[i];
        for(int x=ax1; x<=ax2; x++){
            for(int y=ay1; y<=ay2; y++){
                lineSet[i].insert({x,y});
            }
        }
    }

}

void getBrickOrder(){
    al.resize(bricks.size());
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i==j)continue;
            auto&[ax1,ay1,az1,ax2,ay2,az2] = bricks[i];
            auto&[bx1,by1,bz1,bx2,by2,bz2] = bricks[j];

            if(hasIntersect(i,j)){
                if(az1 < bz2) al[i].insert(j);
                else al[j].insert(i);
                continue;
            }
        }
    }

    vis.assign(n,0);
    for(int i=0; i<n; i++){
        if(!vis[i]) dfs(i);
    }
    for(auto&x:topo) cout << x << ' '; cout << '\n';
    reverse(topo.begin(), topo.end());
}

bool hasIntersect(int i, int j){
    for(auto&[x,y]:lineSet[i]){
        if(lineSet[j].count({x,y})) return true;
    }
    return false;
}
bool hasIntersect(set<pair<int,int>>&si, map<pair<int,int>,int>&sj){
    for(auto&[x,y]:si){
        if(sj.count({x,y})) return true;
    }
    return false;
}

vector<int> topo;
vector<int> vis;
void dfs(int u){
    vis[u] = 1;
    for(auto&v:al[u]){
        if(!vis[v]){
            dfs(v);
        }
    }
    topo.push_back(u);
}
void dropBricks(){
    for(auto&x:topo){
        auto&[ax1,ay1,az1,ax2,ay2,az2] = bricks[x];
        int validLayer = az1;
        int currLayer = az1;
        while(currLayer >= 1){
            if(hasIntersect(lineSet[x],layers[currLayer])) break;
            validLayer = currLayer;
            currLayer--;
        }
        if(az1!=az2){
            az2 -= az1-validLayer;
            az1 = validLayer;
            for(int z=az1; z<=az2; z++){
                layers[z][{ax1,ay1}] = x;
            }
        } else {
            az1 = az2 = validLayer;
            for(auto&p:lineSet[x]){
                layers[validLayer][p] = x;
            }
        }
    }
}
void processSupports(){
    g_supporting.resize(n);
    g_supported.resize(n);
    for(int i=0; i<n; i++){
        auto&[ax1,ay1,az1,ax2,ay2,az2] = bricks[i];
        for(auto&p:lineSet[i]){
            {
                auto it = layers[az2+1].find(p);
                if(it!=layers[az2+1].end()){
                    g_supporting[i].insert(it->second);
                    g_supported[it->second].insert(i);
                }
            }
            {
                auto it = layers[az1-1].find(p);
                if(it!=layers[az1-1].end()){
                    g_supporting[it->second].insert(i);
                    g_supported[i].insert(it->second);
                }
            }
        }
    }
}

int breakBrick(int i){
    vector<set<int>> supporting = g_supporting, supported = g_supported;
    queue<int> q;
    q.push(i);
    int ans = 0;
    while(q.size()){
        auto u = q.front(); q.pop();
        for(auto&v:supporting[u]){
            supported[v].erase(u);
            if(supported[v].empty()){
                ans++;
                q.push(v);
            }
        }
    }
    return ans;
}

int main()
{
//    freopen("test.txt", "r", stdin);
    freopen("input.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    string line;
    while (getline(cin,line)) {
        parse(line);
    }
    n = bricks.size();
    parseBricks();
    getBrickOrder();
    // now we have a top down order stored in topo to process the bricks in.
    dropBricks();


//    cout << "Supporting:\n";
//    for(int i=0; i<n; i++){
//        cout << i << ": ";
//        for(auto&x:supporting[i]) cout << x << ' ';
//        cout << '\n';
//    }
//
//    cout << "Supported:\n";
//    for(int i=0; i<n; i++){
//        cout << i << ": ";
//        for(auto&x:supported[i]) cout << x << ' ';
//        cout << '\n';
//    }
    set<int> keyStones;
    for(int i=0; i<n; i++){
        if(g_supported[i].size()==1){
            keyStones.insert(*g_supported[i].begin());
        }
    }

    cout << keyStones.size() << '\n';
    cout << n-keyStones.size() << '\n';
    int ans = 0;
    for(int i=0; i<n; i++){
        ans += breakBrick(i);
    }
    cout << ans << '\n';
}
