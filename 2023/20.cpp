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
using Module = pair<int, vector<string>>;
unordered_map<string, Module> modules;
unordered_map<string, vector<string>> inputs;
unordered_map<string, unordered_map<string, int>> conjunctionInput;

vector<string> split(string s){
    stringstream ss(s);
    vector<string> toks;
    string tok;
    while(getline(ss,tok,',')){
        toks.push_back(tok);
    }
    for(auto&x:toks){
        x = x.substr(1);
    }
    return toks;
}

ostream& operator<<(ostream& out, Module& m){
    out << "Type " << m.first << " Outs: ";
    for(auto&x:m.second) out << x << ",";
    return out;
}

void parse(string&line){
    string types = "%&";
    int type = types.find(line[0])+1;
    string name;
    if(type){
        name = line.substr(1,line.find(' ')-1);
    } else {
        name = line.substr(0,line.find(' '));
    }
    vector<string> outs = split(line.substr(line.find('>')+1));
    for(auto&out:outs){
        if(name!="broadcaster") inputs[out].push_back(name);
    }
    modules[name] = {type,outs};
}
ll l=0,h=0;
int times = 0;
unordered_map<string,int> status;
void process(){
    // {signal, inModule, module}
    queue<tuple<int,string,string>> q;
    q.push({0,string("button"),string("broadcaster")});
    while(q.size()){
        auto [signal, inModuleName, moduleName] = q.front(); q.pop();
//        cout << inModuleName << ' ' << signal << ' ' << moduleName << '\n';
        if(moduleName=="zr" && signal){
            cout << inModuleName << ' ' << moduleName << ' ' << signal << ' ' << times << '\n';
        }
        if(signal) h++;
        else l++;
        auto &[type, outs] = modules[moduleName];
        if(type==0){
            for(auto&outModule:outs){
                q.push({signal, moduleName, outModule});
            }
        } else if(type==1){
            if(signal) continue;
            int &currStatus = status[moduleName];
            currStatus ^= 1;
            for(auto&outModule:outs){
                q.push({currStatus, moduleName, outModule});
            }
        } else {
            conjunctionInput[moduleName][inModuleName] = signal;
            int inter = 0;
            for(auto&[k,v]:conjunctionInput[moduleName]) inter += v;

            for(auto&outModule:outs){
                q.push({inter!=inputs[moduleName].size(), moduleName, outModule});
            }
        }
    }
}

int main()
{
//    freopen("test.txt", "r", stdin);
    freopen("input.txt", "r", stdin);
    string line;
    while (getline(cin,line)) {
        parse(line);
    }
    for(auto&[k,v]:modules){
        cout << k << ": " << v << '\n';
    }
    for(auto&[k,v]:inputs){
        cout << k << ": ";
        for(auto&x:v) cout << x << ',';
        cout << '\n';
    }
    times = 0;
    while(true){
        process();
        times++;
    }
//    cout << l << ' ' << h << ' ' << l*h << '\n';

/*
    by inspecting the graph, we see that there are 4 distinct branches,
    from there we can see the cycle for each branch, and then compute by hand the lcm

    gc: 3852 7705 11558 cycle: 3853
    xf: 4072 8145 12218 cycle: 4073
    cm: 4090 8181 12272 cycle: 4091
    sz: 4092 8185 12278 cycle: 4093

    lcm: 262775362119547
*/
}

/*
https://csacademy.com/app/graph_editor/
zk vl
zr rx
pp nz
pp ms
zb dn
zb zf
sz zr
km ks
km qx
gb bk
gb ks
jk nr
pn dn
pn jk
bj tc
bj xx
cs gb
dz zb
dz dn
mn tc
mn xs
xx tc
xx xg
kb ms
kb tl
qx ks
qx rh
tc mn
tc xf
tc jl
tc xs
tc zk
gc zr
ms lq
ms fm
ms sz
kf dz
kf dn
hd dn
hd mm
tl pp
tl ms
fl ms
nv pn
nv dn
zv mz
zv ms
zf dn
jm ms
jm cp
mm nv
cp fl
cp ms
pz td
pz tc
bk zz
bk ks
xk cs
xk ks
ps tc
ps vz
jl ps
vl jl
vl tc
nz jm
nz ms
mf ks
mf km
ks jn
ks cs
ks cm
vz pz
vz tc
hf qf
fm zv
qf kf
lq ms
lq fm
nr hf
zz ks
zz vd
td bj
td tc
xf zr
rh ks
broadcaster mn
broadcaster jn
broadcaster hd
broadcaster lq
ml mf
ml ks
dn jk
dn qf
dn gc
dn hf
dn hd
dn nr
dn mm
cm zr
vd ks
vd ml
jn ks
jn xk
xg tc
mz ms
mz gx
gx ms
gx kb
xs zk

*/
