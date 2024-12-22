#pragma GCC optimize ("O3")
#include <ranges>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>
#include <unordered_map>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <algorithm>


using namespace std;
using ll = long long;

vector<ll> split(const string&line, char delim){
    stringstream ss(line);
    string s;
    vector<ll> ans;
    while(getline(ss,s,delim)){
        if(!s.empty()) ans.push_back(stoll(s));
    }
    return ans;
}

vector<pair<int,int>> d4{{0,1},{1,0},{0,-1},{-1,0}};
struct Sim{

    ll registers[3]{};
    ll instruction_pointer = 0;
    vector<ll> ops;
    vector<ll> outs;

    Sim(ll a, const vector<ll>& ops_){
        registers[0] = a;
        ops = ops_;
    }

    ll GetComboOperand(int operand){
        if(operand<=3) return operand;
        if(operand==7) exit(1);
        return registers[operand-4];
    }

    void adv(int operand){
        registers[0] /= (1LL<<GetComboOperand(operand));
    }

    void bxl(int operand) {
        registers[1] ^= operand;
    }

    void bst(int operand) {
        registers[1] = GetComboOperand(operand)%8;
    }

    void jnz(int operand){
        if(registers[0]==0) return;
        // minus 2 here so that it gets incremented after.
        instruction_pointer = operand-2;
    }

    void bxc(int operand){
        registers[1] ^= registers[2];
    }

    void out(int operand){
        cout << "Outputting: " << GetComboOperand(operand)%8 << endl;
        outs.push_back(GetComboOperand(operand)%8);
    }

    void bdv(int operand){
        registers[1] = registers[0] / (1LL<<GetComboOperand(operand));
    }

    void cdv(int operand){
        registers[2] = registers[0] / (1LL<<GetComboOperand(operand));
    }

    vector<void(Sim::*)(int)> fs{adv,bxl,bst,jnz,bxc,out,bdv,cdv};

    bool sim(){

        while(instruction_pointer+1 < ops.size()){
            cout << "Exec " << ops[instruction_pointer] << " with op: " << ops[instruction_pointer+1] << ' ' << " with registers:\n"; for(auto&x:registers) cout << bitset<50>(x) << '\n'; cout << endl;

            (this->*fs[ops[instruction_pointer]])(ops[instruction_pointer+1]);

            instruction_pointer += 2;
        }
        return outs == ops;
    }
};

vector<ll> f(ll a){
    vector<ll> outs;
    while(a){
        ll b = a%8;
        b ^= 2;
        ll c = a>>b;
        b ^= c;
        b ^= 3;
        outs.push_back(b%8);
        a/=8;
    }
    return outs;
}

bool valid(const vector<ll>&v, const vector<ll>&ops){
    for(int i=0; i<v.size(); ++i){
            cout << "comparing: " << (16-v.size()+i) << " with " << i << endl;
        if(ops[16-v.size()+i]!=v[i]) return false;
    }
    return true;
}

ll g(const vector<ll>& ops){
    ll a = 1;
    for(int i=15; i>0; --i){
        a *= 8;
        vector<ll> v = f(a);
        while(!valid(v,ops)){
            a++;
            v = f(a);
            cout << a << ": "; for(auto&x:v) cout << x << ' '; cout << endl;
        }
        cout << a <<'\n';
    }
    return a;
}

int main(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
//    string s;
//    cin >> s >> s >> registers[0];
//    cin >> s >> s >> registers[1];
//    cin >> s >> s >> registers[2];
//
//    cin >> s >> s;
//    cin >> s;
//    vector<ll> ops = split(s,',');

    vector<ll> ops {2,4,1,2,7,5,4,1,1,3,5,5,0,3,3,0};
    // lmao trying to brute force it and overshot
    Sim sim(9,ops);
//    Sim sim(38878582193652LL,ops);
    sim.sim();

    // trying to find the starting point from the back 
//    int lim = 12;
    // 38878582193652
//    for(ll i = 37'000'000'000'000; i<38'878'582'193'652; i+=10000){
//        vector<int> v = f(i);
//        if(v.size() != 16) continue;
//        bool valid = true;
//        for(int i=16-lim; i<16; ++i){
//            if(v[i]!=ops[i]) {
//                valid = false;
//                break;
//            }
//        }
//        if(valid) {
//            cout << i << ": "; for(auto&x:v) cout << x << ','; cout << endl;
//        }
//    }

    cout << g(ops) << endl;
    for(auto&x:f(g(ops))) cout << x << ' '; cout << endl;
    while(true){
        ll x; cin >> x;
        for(auto&x:f(x)) cout << x << ' '; cout << endl;
    }

}

/**
actual program:
for(; a; a /= 8){
    b = a%8;
    b ^= 2;
    c = a/(1<<b);
    b ^= c;
    b ^= 3;
    print(b%8);
}

35000000000000 1,1,1,7,3,1,7,7,1,1,0,1,7,7,6, ~15
36000000000000 1,1,1,1,0,4,7,7,1,3,1,2,7,0,3,0, ~16
37000000000000 1,1,1,3,7,4,0,2,7,0,1,3,1,3,3,0, ~16
38000000000000 1,1,1,5,7,1,1,7,5,1,4,4,3,4,3,0, ~16
39000000000000 1,1,1,7,4,1,1,5,4,1,4,3,7,3,3,0, ~16
40000000000000 1,1,1,1,3,3,1,3,7,7,3,5,3,3,1,0, ~16
41000000000000 1,1,1,3,7,0,7,3,7,0,3,1,4,1,1,0, ~16
42000000000000 1,1,1,5,1,5,5,7,3,4,7,3,3,4,1,0, ~16
43000000000000 1,1,1,7,7,3,1,7,3,0,1,3,6,3,1,0, ~16
44000000000000 1,1,1,1,2,5,6,1,7,2,1,1,1,5,1,0, ~16
45000000000000 1,1,1,3,4,6,1,3,4,3,3,0,7,2,1,0, ~16
46000000000000 1,1,1,5,7,2,1,7,0,3,7,7,1,3,1,0, ~16
47000000000000 1,1,1,7,0,7,3,1,1,4,6,4,7,4,1,0, ~16
48000000000000 1,1,1,1,5,1,3,1,2,7,2,3,1,4,1,0, ~16
49000000000000 1,1,1,3,0,5,1,3,3,6,1,3,1,3,7,0, ~16
50000000000000 1,1,1,5,1,1,6,0,3,6,1,7,0,1,7,0, ~16
51000000000000 1,1,1,7,3,2,7,1,4,7,1,6,1,4,7,0, ~16
52000000000000 1,1,1,1,4,7,4,3,6,1,1,3,6,2,7,0, ~16
53000000000000 1,1,1,3,1,7,7,6,7,1,5,1,3,1,5,0, ~16
54000000000000 1,1,1,5,6,1,7,2,1,7,3,7,2,1,5,0, ~16
55000000000000 1,1,1,7,5,6,3,7,3,5,6,1,1,4,5,0, ~16
56000000000000 1,1,1,1,7,7,7,1,7,5,1,5,5,4,5,0, ~16
57000000000000 1,1,1,3,1,0,5,3,7,7,2,7,2,5,5,0, ~16
58000000000000 1,1,1,5,1,7,3,7,4,4,1,1,0,5,4,0, ~16
59000000000000 1,1,1,7,7,4,1,5,1,1,7,6,1,7,4,0, ~16
60000000000000 1,1,1,1,6,4,7,1,2,1,4,3,5,4,4,0, ~16
61000000000000 1,1,1,3,6,5,1,1,7,2,1,3,5,1,4,0, ~16
62000000000000 1,1,1,5,6,3,0,1,5,5,7,6,7,5,7,0, ~16
63000000000000 1,1,1,7,1,6,7,7,4,1,6,5,3,1,7,0, ~16
64000000000000 1,1,1,1,1,3,2,1,5,1,6,1,3,4,7,0, ~16
65000000000000 1,1,1,3,2,1,1,1,7,3,5,7,6,0,7,0, ~16
66000000000000 1,1,1,5,1,1,3,7,1,1,7,3,1,7,6,0, ~16
67000000000000 1,1,1,7,3,1,2,7,3,2,4,5,3,7,6,0, ~16
68000000000000 1,1,1,1,3,5,0,2,7,6,4,6,3,7,6,0, ~16
69000000000000 1,1,1,3,3,1,6,3,5,1,2,1,2,4,6,0, ~16
70000000000000 1,1,1,5,5,4,3,5,0,0,3,3,1,5,6,0, ~16
71000000000000 1,1,1,7,5,7,6,3,7,4,7,1,1,0,5,1, ~16
72000000000000 1,1,1,1,3,3,7,3,3,7,1,5,6,1,5,1, ~16
73000000000000 1,1,1,3,3,3,6,7,3,7,1,1,5,7,5,1, ~16
*/
