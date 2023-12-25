#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <unordered_set>
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

unordered_map<int,vector<int>> g_al;
vector<pair<int,int>> g_el;
vector<string> nodeToString;
unordered_map<string,int> nodes;

class UFDS {
private:
	vector<int> p, rank, setSizes;
	int numSets;
public:
	UFDS(int N) {
		numSets = N;
		rank.assign(N, 0);
		p.assign(N, 0);
		for (int i = 0; i < N; i++)
			p[i] = i;
		setSizes.assign(N, 1);
	}
	int findSet(int i) {
		return (p[i] == i) ? i : p[i] = findSet(p[i]);
	}
	bool isSameSet(int i, int j) {
		return findSet(i) == findSet(j);
	}
	void unionSet(int i, int j) {
		if (!isSameSet(i, j)) {
			int x = findSet(i), y = findSet(j);
			if (rank[x] > rank[y]) {
				setSizes[findSet(x)] += setSizes[findSet(y)];
				p[y] = x;
			} else {
				setSizes[findSet(y)] += setSizes[findSet(x)];
				p[x] = y;
				if (rank[x] == rank[y])
					rank[y]++;
			}
			numSets--;
		}
	}
	int setSize(int i) {
		return setSizes[findSet(i)];
	}
	int numDisjointSets() {
		return numSets;
	}
};

void parse(string&line){
    string s;
    stringstream ss(line);
    getline(ss,s,':');
    string u = s;
    getline(ss,s,':');
    ss = stringstream(s);
    vector<string> v;
    while(getline(ss,s,' ')){
        if(s.size()) v.push_back(s);
    }
    cout << u << ": ";
    if(!nodes.count(u)) {
        nodes[u] = nodeToString.size();
        nodeToString.push_back(u);
    }
    for(auto&x:v) cout<<x << ',';
    for(auto&x:v){
        if(!nodes.count(x)) {
            nodes[x] = nodeToString.size();
            nodeToString.push_back(x);
        }

        g_el.push_back({nodes[u], nodes[x]});
    }
    cout << '\n';
}

// randomized algorithm, choose edges and union them, until you're left with 2 disjoint sets, then check if the cut has size 3.
bool process(){
    vector<pair<int,int>> el = g_el;
    int n = g_el.size();
    random_shuffle(el.begin(), el.end());
    UFDS ufds(nodes.size());
    for(auto&[u,v]:el){
        if(ufds.numDisjointSets() == 1) return false;
        if(ufds.numDisjointSets() == 2){
            int cutEdges = 0;
            for(auto&[u,v]:el){
                if(!ufds.isSameSet(u,v)) cutEdges++;
                if(cutEdges>3) return false;
            }

            unordered_set<int> s;
            for(int i=0; i<nodes.size(); i++){
                s.insert(ufds.setSize(i));
            }
            ll ans = 1;
            for(auto&x:s) {
                cout <<x << ' '; cout << "\n";
                ans *= x;
            }
            cout << ans << '\n';
            return true;
        }
        if(ufds.isSameSet(u,v)) continue;
        ufds.unionSet(u,v);
    }
    return false;
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
//    for(auto&[u,vv]:g_al){
//        for(auto&x:vv) cout << u << ' ' << x << '\n';
//    }
    while(!process());
    /*
        709
        784
        555856
    */
}
