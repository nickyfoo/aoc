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
// return dir, dist;
unordered_map<string, vector<string>> workflows;

void parseWorkflow(string&s){
    string name = s.substr(0,s.find('{'));
    s = s.substr(s.find('{')+1);
    s.pop_back();
    stringstream ss(s);
    string tok;
    vector<int> part;
    vector<string> checks;
    while(getline(ss,tok,',')){
        checks.push_back(tok);
    }
    workflows[name] = checks;
}

vector<int> parsePart(string&s){
    s = s.substr(1);
    s.pop_back();
    stringstream ss(s);
    string tok;
    vector<int> part;
    vector<string> toks;
    while(getline(ss,tok,',')){
        toks.push_back(tok);
    }
    for(auto&x:toks){
        x = x.substr(x.find('=')+1);
        part.push_back(stoi(x));
    }
    return part;
}

string xmas = "xmas";

bool isAccepted(string workflow, vector<int>&part){
//    cout << workflow << ": ";
//    for(auto&x:part) cout << x << ' '; cout << '\n';
    for(auto&check:workflows[workflow]){
        int pos = check.find(':');
        if(pos==-1){
            if(check=="A") return true;
            else if(check=="R") return false;
            else return isAccepted(check, part);
        } else {
            string condition, res;
            condition = check.substr(0,pos);
            res = check.substr(pos+1);
            int largerPos = condition.find('>');
            int smallerPos = condition.find('<');
            int l = part[xmas.find(condition[0])];
            int r = stoi(condition.substr(2));
            if(condition.find('>')!=-1){
                if(l>r){
                    if(res=="A") return true;
                    else if(res=="R") return false;
                    else return isAccepted(res, part);
                }
            } else {
                if(l<r){
                    if(res=="A") return true;
                    else if(res=="R") return false;
                    else return isAccepted(res, part);
                }
            }
        }
    }
    cout << "DISASTER\n";
    return false;
}

ll ans = 0;

void tryAccepted(string workflow, vector<pair<ll,ll>> part){
    cout << workflow << ": ";
    for(auto&[l,r]:part) cout << l << ','<<r  << ' '; cout << '\n';
    for(auto&check:workflows[workflow]){
        cout << check << '\n';
        int pos = check.find(':');
        if(pos==-1){
            if(check=="A") {
                ll inter = 1;
                for(auto&[l,r]:part){
                    inter *= (r-l+1);
                }
                cout << inter << ": ";
                for(auto&[l,r]:part) cout << l << ','<<r  << ' '; cout << '\n';
                ans += inter;
                return;
            }
            else if(check=="R") return;
            else tryAccepted(check, part);
        } else {
            string condition, res;
            condition = check.substr(0,pos);
            res = check.substr(pos+1);
            int largerPos = condition.find('>');
            int smallerPos = condition.find('<');
            vector<pair<ll,ll>> newPart = part;

            auto &[l,h] = newPart[xmas.find(condition[0])];
            ll r = stoi(condition.substr(2));
            if(condition.find('>')!=-1){
                l = max(l,r+1);
                if(res=="A") {
                    ll inter = 1;
                    for(auto&[l,r]:newPart){
                        inter *= (r-l+1);
                    }
                cout << inter << ": ";
                for(auto&[l,r]:newPart) cout << l << ','<<r  << ' '; cout << '\n';
                    ans += inter;
                }
                else if(res=="R");
                else tryAccepted(res, newPart);

                ll&ph = part[xmas.find(condition[0])].second;
                ph = min(ph, r);
            } else {
                h = min(h,r-1);
                if(res=="A") {
                    ll inter = 1;
                    for(auto&[l,r]:newPart){
                        inter *= (r-l+1);
                    }
            cout << inter << ": ";
            for(auto&[l,r]:newPart) cout << l << ','<<r  << ' '; cout << '\n';
                    ans += inter;
                }
                else if(res=="R");
                else tryAccepted(res, newPart);


                ll&pl = part[xmas.find(condition[0])].first;
                pl = max(pl,r);
            }
        }
    }
}


int main()
{
//    freopen("test.txt", "r", stdin);
    freopen("input.txt", "r", stdin);
    string line;
    bool workflowsDone = false;
    while (getline(cin,line)) {
        if(line.size()){
            if(workflowsDone) {
                vector<int> part = parsePart(line);
//                if(isAccepted("in", part)){
//                    for(auto&x:part) cout << x << ' '; cout << '\n';
//                    ans += accumulate(part.begin(), part.end(), 0);
//                }
            }
            else parseWorkflow(line);
        } else {
            workflowsDone = true;
        }
    }

    for(auto&[k,v]:workflows) {
        cout << k << ": ";
        for(auto&x:v) cout << x << ", ";
        cout << '\n';
    }
//    cout << ans << '\n';
    vector<pair<ll,ll>> part{{1,4000},{1,4000},{1,4000},{1,4000}};
    tryAccepted("in",part);
    cout << ans;
    return 0;
}
