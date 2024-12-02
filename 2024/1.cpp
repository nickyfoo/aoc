#pragma GCC optimize ("O3")
#include <ranges>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include <algorithm>


using namespace std;
using ll = long long;
const ll MOD = 1e9+7;


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int ans = 0;
    string line;
    vector<int> a,b;
    map<int,int> m;
    while(getline(cin, line)){
        stringstream ss(line);
        int x, y; ss >> x >> y;
        a.push_back(x);
        m[y]++;
    }
    ranges::sort(a);
    ranges::sort(b);
    for(int i=0; i<a.size(); ++i){
        ans += a[i]*m[a[i]];
    }
    cout << ans;
}
