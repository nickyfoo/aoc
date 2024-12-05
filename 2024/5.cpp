#pragma GCC optimize("O3")
#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;

vector<int> split(const string& line, char delim = ' ') {
  stringstream ss(line);
  string s;
  vector<int> ans;
  while (getline(ss, s, delim)) {
    if (!s.empty()) ans.push_back(stoi(s));
  }
  return ans;
}

vector<set<int>> al;

bool valid(vector<int>& v) {
  int n = v.size();
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (!al[v[i]].count(v[j])) return false;
    }
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  ll ans1 = 0;
  ll ans2 = 0;
  al.resize(100);
  vector<string> grid;
  string line;
  while (getline(cin, line)) {
    if (line.size() == 0) break;
    auto v = split(line, '|');
    al[v[0]].insert(v[1]);
  }

  while (getline(cin, line)) {
    auto v = split(line, ',');
    if (valid(v)) {
      ans1 += v[v.size() / 2];
    } else {
      vector<pair<int, int>> v2;
      for (auto& x : v) v2.push_back({0, x});
      for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v.size(); ++j) {
          if (al[v[i]].count(v[j])) v2[i].first++;
        }
      }
      sort(v2.begin(), v2.end());
      ans2 += v2[v2.size() / 2].second;
    }
  }
  cout << ans1 << endl;
  cout << ans2 << endl;
}
