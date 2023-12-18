#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
using ll = long long;

string dirs = "RDLU";
vector<pair<int,int>> d4 {{0,1},{1,0},{0,-1},{-1,0}};
string h="0123456789abcdef";

// return dir, dist;
pair<ll,ll> parse(string&color){
    string d = color.substr(2,5);
    long long res = 0;
    for(auto c:d){
        res *= 16;
        res += h.find(c);
    }

    return {color[7]-'0', res};
}

void process2(){
    string line;

    vector<pair<ll,ll>> pos;
    pair<ll,ll> p = {400,400};
    pos.push_back(p);
    while(getline(cin,line)){
        char c; int len; string color;
        stringstream ss(line);
        ss >> c >> len >> color;
        auto [dir,dist] = parse(color);
        // to test w part 1
//        int dir = dirs.find(c);
//        int dist = len;
//        cout << dir << ' ' << dist << '\n';
        p.first += d4[dir].first * dist;
        p.second += d4[dir].second * dist;
        pos.push_back(p);
    }

    for(auto&[a,b]:pos) cout << a << ' ' << b << '\n';
    vector<ll> xs;
    for(auto&[x,y]:pos){
        xs.push_back(x);
    }
    sort(xs.begin(), xs.end());
    xs.resize(unique(xs.begin(), xs.end())-xs.begin());
//    for(auto&x:xs) cout << x << '\n';

    ll ans = 0;

    vector<vector<ll>> yOverlaps;
    // for each x block find the ys that are valid
    for(int i=1; i<xs.size(); i++){
        ll lx = xs[i-1], hx = xs[i];
        vector<ll> ys;
        for(int j=1; j<pos.size(); j++){
            auto&[prevx,prevy] = pos[j-1];
            auto&[currx,curry] = pos[j];
            if(prevx==currx) continue;
            // this line passes through our current x interval
            if(prevx <= lx && currx >= hx || prevx >= hx && currx <=lx)
                ys.push_back(curry);
        }
        cout << lx << '~' << hx << ": ";
        sort(ys.begin(), ys.end());
        ys.resize(unique(ys.begin(), ys.end())-ys.begin());
        // store the ys to count overlaps later
        yOverlaps.push_back(ys);
        for(auto&y:ys) cout << y << ' '; cout << '\n';
        for(int j=0; j+1<ys.size(); j+=2){
            ans += (hx-lx+1) * (ys[j+1]-ys[j]+1);
            if(j+1==ys.size()-1) {

            }
        }
    }

    cout << ans << '\n';

    // remove the y overlaps
    for(int i=1; i<yOverlaps.size(); i++){
        vector<ll> prev = yOverlaps[i-1];
        vector<ll> curr = yOverlaps[i];
        for(int j=0; j<prev.size(); j+=2){
            ll pjy=prev[j];
            ll cjy=prev[j+1];
            ll overlap = 0;
            for(int k=0; k<curr.size(); k+=2){
                ll pky=curr[k];
                ll cky=curr[k+1];
                if(pjy > cky || pky > cjy) continue;
                if(pjy <= pky && pky <= cjy && pjy<=cky && cky<=cjy){
                    overlap += cky-pky+1;
                } else if(pjy <= pky && pky <= cjy) {
                    overlap += cjy-pky+1;
                } else if(pjy<=cky && cky<=cjy) {
                    overlap += cky-pjy+1;
                } else {
                    overlap += cjy-pjy+1;
                }
            }
            ans -= overlap;
        }
    }
    cout << ans << '\n';
}
void process();
int main()
{
//    freopen("test.txt", "r", stdin);
    freopen("input.txt", "r", stdin);
    process2();
    return 0;
}


void process(){

    string line;
    int n = 800;
    vector<string> grid(n, string(n,'.'));
    int x=n/2, y=n/2;
    grid[x][y] = '#';
    while (getline(cin,line)) {
        char dir; int len; string color;
        stringstream ss(line);
        ss >> dir >> len >> color;
        auto d = dirs.find(dir);
        auto&[di,dj] = d4[d];
        for(int i=0; i<len; i++){
            x += di;
            y += dj;
            grid[x][y] = '#';
        }
    }
    for(auto&x:grid) cout << x << '\n';
    queue<pair<int,int>> q;
    q.push({0,0});
    grid[0][0] = 'O';
    while(q.size()){
        auto [i,j] = q.front(); q.pop();
        for(auto&[di,dj]:d4){
            if(0<=i+di && i+di<n && 0<=j+dj && j+dj<n && grid[i+di][j+dj]=='.'){
                grid[i+di][j+dj] = 'O';
                q.push({i+di,j+dj});
            }
        }
    }

    int outside = 0, inside = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j]=='O') outside++;
            else inside++;
        }
    }
    cout << outside << ' ' << inside << '\n';
}

