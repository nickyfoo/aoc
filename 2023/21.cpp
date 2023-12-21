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

vector<string> grid;

void replaceInternal(){
    int m = grid.size(), n = grid[0].size();
    pair<int,int> start {m/2,n/2};

    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j]=='S') {
                grid[i][j] = '.';
            }
        }
    }

    queue<pair<int,int>> q;
    q.push(start);
    while(q.size()){
        auto [i,j] = q.front(); q.pop();
        for(auto&[di,dj]:d4){
            if(0<=i+di && i+di<m && 0<=j+dj && j+dj<n){
                if(grid[i+di][j+dj]=='.') {
                    grid[i+di][j+dj] = ' ';
                    q.push({i+di,j+dj});
                }
            }
        }
    }

    for(auto&r:grid){
        for(auto&x:r){
            if(x=='.') x='#';
            if(x==' ') x='.';
        }
    }
}

void process(int layers){
    int m = grid.size(), n = grid[0].size();
    pair<int,int> start{m/2,n/2};
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j]=='S') {
                grid[i][j] = '.';
            }
        }
    }

    set<pair<int,int>> q;
    vector<int> blocked(2,0), cblocked(2,0), tblocked(2,0);
    q.insert(start);
    for(int layer=0; layer<layers; layer++){
        set<pair<int,int>> next;
        for(auto&[i,j]:q){
            for(auto&[di,dj]:d4){
                if(0<=i+di && i+di<m && 0<=j+dj && j+dj<n){
                    if(grid[i+di][j+dj]=='.') {
                        next.insert({i+di,j+dj});
                    }
                }
            }
        }
//        cout << layer << ' ' << next.size() << '\n';
        swap(next,q);
    }
    vector<string> g=grid;
    for(auto&[i,j]:q){
        g[i][j] = ' ';
    }


    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            tblocked[(i+j)%2] += g[i][j] =='#';
            if(abs(i-m/2) + abs(j-n/2) < 196) blocked[(i+j)%2]+=g[i][j]=='#';
            else cblocked[(i+j)%2]+=g[i][j]=='#';
        }
    }
    for(auto&x:g) cout << x << '\n';
    cout << "Actual: " << layers<< ' ' <<  q.size() << ' ' << blocked[0] << ' ' << blocked[1] << ' ' << cblocked[0] << ' ' << cblocked[1] << ' ' << tblocked[0] << ' ' << tblocked[1] << '\n';
}

//1 + 2 + .. + steps + .. + 2 + 1
ll triangleSum(ll steps){
    ll ans = 0;
    for(ll i=1; i<=steps-1; i++){
        ans += 2*i;
    }
    ans += steps;
    return ans;
}


/*
from investigation:
the grid is 131 x 131, and has diamond shapes.

When extended, we can split them into diamond blocks.

this means that we can split the distance into counting the number of rocks in a nice region.


call the block containing S an odd block, and then any other one that is axis aligned with this one is also an odd block.
the rest are even blocks.

Now we also need to split the grid by parity, since each step basically is only on an odd or even square.
then note that because the grid is 131x131 (odd number), the parity will change for the blocked tiles.
e.g. in the central block, there are 528 odd and 594 even rocks, but in a subsequent block, there will be 594 odd and 528 even.

After playing around with the even blocks, one can realise that you can rearrange them such that the internal parity doesn't matter,
we just need the total number of them.

for odd blocks, we need to count the number of odd odd blocks, and even odd blocks.from there, we know what to multiply.
*/
void getAns(ll start){
    // blocked plots.
    /*
    blocked plots
    centre diamond: 1122 = (528, 594),
    outer triangles: 1179 = (617, 562),
    */
    ll total = 0, oddTotal = 0, evenTotal = 0;

    for(ll i=1; i<=start; i++){
        oddTotal += i*2;
    }
    oddTotal += start+1;

    for(ll i=1; i<start; i++){
        evenTotal += i*2;
    }
    evenTotal += start;

    ll steps = (start-65)/131+1; //202300;
    cout << start << ": steps:" << steps << ", ";
    ll oa = triangleSum(steps), ob = triangleSum(steps-1);
    ll evenBlocks=0;

    for(ll i=1; i<=steps-1; i++){
        evenBlocks += (i*2);
    }
    ll ea = evenBlocks/2, eb = evenBlocks-ea; // even blocks internal parity don't matter
    cout << oa << ' ' << ob << ' ' << ea << ' ' << eb << ' ';
    // determined this after some trial and erroring
    if(start%2==0) cout << oddTotal - oa*528 - ob*594 - evenBlocks*(1179) << '\n';
    else cout << oddTotal - ob*528 - oa*594 -  evenBlocks*(1179) << '\n';
}

void getStats(){
    int m = grid.size(), n = grid[0].size();
    int ans = 0;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j]=='#') ans++;
        }
    }
    cout << ans << '\n';
}

int main()
{
//    freopen("test.txt", "r", stdin);
    freopen("input.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
//    string line;
//    while (getline(cin,line)) {
//
//        grid.push_back(line);
//    }
    string line;
    // resizes the grid for p2
    int sz = 3;
    while (getline(cin,line)) {
        string bigline = "";
        for(int i=0; i<sz; i++){
            bigline += line;
        }
        grid.push_back(bigline);
    }
    int z = grid.size();
    for(int i=0; i<sz-1; i++){
        for(int j=0; j<z; j++){
            grid.push_back(grid[j]);
        }
    }
    // some are not stones but are still inaccessible!
    replaceInternal();
    getStats();

    process(64);
    process(65);
    process(66);
    process(196);

    getAns(64);
    getAns(65);
    getAns(66);
    getAns(196);
    getAns(26501365);

    // for part 2, we can tell that it's quadratic, and use lagrange interpolation to get the ans.

}
