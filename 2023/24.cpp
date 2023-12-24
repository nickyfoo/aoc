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

string dirs = ">v<^";
vector<pair<ll,ll>> d4 {{0,1},{1,0},{0,-1},{-1,0}};

vector<tuple<ll,ll,ll,ll,ll,ll>> hailstones;

void print(int i){
    auto&[ix,iy,iz,idx,idy,idz] = hailstones[i];
    cout << ix << ',' << iy << ',' << iz << ' ' << idx << ',' << idy << ',' << idz << '\n';
}

vector<ll> split(string&line){
    vector<ll> ans;
    stringstream ss(line);
    string s;
    while(getline(ss,s,',')){
        ans.push_back(stoll(s));
    }
    return ans;
}

void parse(string&line){
    stringstream ss(line);
    string s;
    getline(ss,s,'@');
    vector<ll> v = split(s);
    getline(ss,s,'@');
    vector<ll> vv = split(s);
    hailstones.push_back({v[0],v[1],v[2], vv[0], vv[1], vv[2]});
}

ll lowlim=200000000000000, highlim=400000000000000;
//ll lowlim=7, highlim=27;

bool intersect(ll i, ll j){
//    cout << "Testing: " << i << ',' << j << ":\n";
    auto&[ix,iy,iz,idx,idy,idz] = hailstones[i];
    auto&[jx,jy,jz,jdx,jdy,jdz] = hailstones[j];

    double a1 = idy, b1 = -idx, c1 = iy*idx - idy*ix;
    double a2 = jdy, b2 = -jdx, c2 = jy*jdx - jdy*jx;

    if(a1*b2 - a2*b1 ==0) {
        // identical line
        if(a1*c2-c1*a2 ==0 && b1*c2-c1*b2==0) return true;
        return false;
    } else {
        double x = -double(c1*b2-c2*b1)/(a1*b2-a2*b1);
        double y = -double(a1*c2-a2*c1)/(a1*b2-a2*b1);
        double t1 = (x-ix)/idx;
        double t2 = (x-jx)/jdx;
//        cout << i << ',' << j << ": " << x << ' ' << y << ' ' << t1 << ',' << t2 << '\n';
        return t1>=0 && t2>=0 && lowlim<=x && x<=highlim && lowlim<=y && y<=highlim;
    }

}

vector<vector<int>> factors(2000);
vector<int> primes;
void sieve(){
    vector<int> sv(2000,0);
    for(int i=2; i<2000; i++){
        if(sv[i]==0){
            primes.push_back(i);
            int j = i+i;
            while(j<2000){
                sv[j] = 1;
                j += i;
            }
        }
    }
    for(int i=2; i<2000; i++){
        map<int,int> m;
        int x = i;
        for(auto&p:primes){
            if(x==1) break;
            if(x%p==0){
                m[p]++;
            }
        }
        for(auto&[prime,num]:m){
            int ans = 1;
            for(int i=0; i<num; i++){
                ans *= prime;
            }
            factors[i].push_back(ans);
        }
    }
//    for(auto&x:primes) cout << x << ' '; cout << '\n';
//    for(int i=0; i<2000; i++) {
//        cout << i<< ": ";
//        for(auto&factor:factors[i]) cout << factor << ',';
//    cout << '\n';
//     }
}


template <int coord>
ll getD(){
    set<int> ans;
    for(int i=-1000; i<=1000; i++){
        bool valid = true;
        map<int,set<int>> mapper;
        set<int> parallels;
        for(auto&hailstone: hailstones){
            ll x = get<coord>(hailstone);
            ll dx = get<coord+3>(hailstone);
            ll m = abs(dx-i);
            if(m){
                mapper[m].insert(x%m);
            } else {
                parallels.insert(x);
            }
        }

        for(auto&[m,vs]:mapper){
                if(vs.size() > 1) valid = false;
        }
        if(parallels.size()>1) valid = false;
        if(!valid) continue;
//        cout << i << '\n';
//        for(auto&[m,vs]:mapper){
//            cout << i << ": ";
//            cout << m << ": ";
//            for(auto&x:vs){
//                cout << x << ',' ;
//            }
//            cout<< "\n";
//        }
//        cout << '\n';
        ans.insert(i);
        // congruent to a mod m {a,m}
        set<pair<ll,ll>> inter;

        for(auto&[m,vs]:mapper){
            for(auto&factor:factors[m]){
                inter.insert({*vs.begin()%factor,factor});
            }
        }
        string s = "xyz";
        string x = string(1,s[coord]);
        string ax = "a" + x;
        string nx = "n" + x;
        cout << i << ":\n";
        cout << ax << " = [";
        for(auto&[a,m]:inter) cout << a << ','; cout << "]\n";
        cout << nx << " = [";
        for(auto&[a,m]:inter) cout << m << ','; cout << "]\n";
        cout << x << " = chinese_remainder(" + nx + ',' + ax + ")\n";
    }
    return *ans.begin();
}

void p2(){
    /*
    can split by dimensions,
    for the x dimension, you want
    x+t*dx = ix+t*idx
    for some int t.
    that means x-ix % idx-dx == 0
    we try by brute force to find a dx such that each congruence class of idx-dx has only 1 input.

    this determines our velocity.

    from here, we have a bunch of congruence equations that are not coprime, so we need to extract the (largest) prime factors
    and get the proper system of congruence equations.

    To find the starting position, we need to solve the system of congruence equations with CRT.
    (python because of overflow)

    */
    ll finalDX = getD<0>(), finalDY = getD<1>(), finalDZ=getD<2>();
    cout << finalDX << ' ' << finalDY << ' ' << finalDZ << '\n';
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
//    for(auto&[x,y,z,dx,dy,dz]:hailstones) {
//        cout << x << ',' << y << ',' << z << ' ' << dx << ',' << dy << ',' << dz << '\n';
//    }

// part 1
//    ll ans = 0;
//    for(ll i=0; i<hailstones.size(); i++){
//        for(ll j=i+1; j<hailstones.size(); j++){
//            if(intersect(i,j)) {
////                cout << i << ',' << j << "\n\n";
//                ans++;
//            }
//        }
//    }
//    cout << ans << '\n';

    sieve();
    p2();
}
