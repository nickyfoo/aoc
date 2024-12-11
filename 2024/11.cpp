#pragma GCC optimize("O3")
#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;

vector<ll> split(const string& line, char delim = ' ') {
  stringstream ss(line);
  string s;
  vector<ll> ans;
  while (getline(ss, s, delim)) {
    if (!s.empty()) ans.push_back(stoi(s));
  }
  return ans;
}

vector<pair<int, int>> d4{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
vector<pair<int, int>> d8{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                          {0, 1},   {1, -1}, {1, 0},  {1, 1}};

int dfs(vector<string>& grid, vector<vector<int>>& vis, int i, int j,
        int prev = -1) {
  int m = grid.size(), n = grid[0].size();
  int ans = (prev == 8 && grid[i][j] == '9');
  vis[i][j] = 1;
  for (auto& [di, dj] : d4) {
    if (0 <= i + di && i + di < m && 0 <= j + dj && j + dj < n &&
        !vis[i + di][j + dj]) {
      if (grid[i + di][j + dj] == grid[i][j] + 1) {
        ans += dfs(grid, vis, i + di, j + dj, grid[i][j] - '0');
      }
    }
  }
  return ans;
}

vector<ll> blink(vector<ll>& v) {
  vector<ll> ans;
  for (auto& x : v) {
    if (x == 0)
      ans.push_back(1);
    else {
      string s = to_string(x);
      if (s.size() % 2 == 0) {
        ans.push_back(stoll(s.substr(0, s.size() / 2)));
        ans.push_back(stoll(s.substr(s.size() / 2, s.size() / 2)));
      } else {
        ans.push_back(x * 2024);
      }
    }
  }
  return ans;
}

map<pair<ll, ll>, ll> cache;
ll f(ll x, ll times) {
  if (auto it = cache.find({x, times}); it != cache.end()) return it->second;
  ll& ans = cache[{x, times}];
  ans = 1;
  // ll ans = 1;
  if (times == 0) return ans = 1;
  if (x == 0) {
    return ans = f(1, times - 1);
  } else {
    string s = to_string(x);
    if (s.size() % 2 == 0) {
      ll a = stoll(s.substr(0, s.size() / 2));
      ll b = stoll(s.substr(s.size() / 2, s.size() / 2));
      return ans = f(a, times - 1) + f(b, times - 1);
    } else {
      return ans = f(x * 2024, times - 1);
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  vector<string> grid;
  string line;
  getline(cin, line);
  vector<ll> v = split(line, ' ');
  ll ans = 0;
  for (auto& x : v) ans += f(x, 75);
  // for (int i = 0; i < 75; ++i) {
  //   cout << i << endl;
  //   v = blink(v);
  // }
  // cout << v.size() << endl;
  cout << ans << endl;
}
