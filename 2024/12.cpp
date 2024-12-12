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

int dfs(set<tuple<int, int, int, int>>& peri, vector<string>& grid,
        vector<vector<int>>& vis, int i, int j) {
  int m = grid.size(), n = grid[0].size();
  int ans = 1;
  vis[i][j] = 1;
  for (auto& [di, dj] : d4) {
    if (0 <= i + di && i + di < m && 0 <= j + dj && j + dj < n) {
      if (!vis[i + di][j + dj] && grid[i + di][j + dj] == grid[i][j]) {
        ans += dfs(peri, grid, vis, i + di, j + dj);
      } else {
        if (grid[i][j] != grid[i + di][j + dj])
          peri.insert({i, j, i + di, j + dj});
      }
    } else {
      peri.insert({i, j, i + di, j + dj});
    }
  }
  return ans;
}

int GetLines(set<tuple<int, int, int, int>>& peri) {
  // map from {di,dj} to map from lineid to orth pos;
  map<pair<int, int>, map<double, set<int>>> horiz, vert;
  for (auto& [x1, y1, x2, y2] : peri) {
    int di = x2 - x1, dj = y2 - y1;
    if (di == 0) {
      vert[{di, dj}][double(y1 + y2) / 2.0].insert(x1);
    } else if (dj == 0) {
      horiz[{di, dj}][double(x1 + x2) / 2.0].insert(y1);
    }
  }
  ll ans = 0;
  for (auto& [_, line] : horiz) {
    cout << "Horiz line ";
    for (auto& [id, pos] : line) {
      int prev = *pos.begin();
      cout << id << ": ";
      for (auto& x : pos) {
        cout << x << ' ';
        if (x - prev > 1) ans++;
        prev = x;
      }
      ans++;
      cout << endl;
    }
  }

  for (auto& [_, line] : vert) {
    cout << "Vert line ";
    for (auto& [id, pos] : line) {
      int prev = *pos.begin();
      cout << id << ": ";
      for (auto& x : pos) {
        cout << x << ' ';
        if (x - prev > 1) ans++;
        prev = x;
      }
      ans++;
      cout << endl;
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  vector<string> grid;
  string line;
  while (getline(cin, line)) {
    grid.push_back(line);
  }

  vector<vector<int>> vis(grid.size(), vector<int>(grid[0].size(), 0));
  ll ans = 0;
  for (int i = 0; i < grid.size(); ++i) {
    for (int j = 0; j < grid[0].size(); ++j) {
      if (!vis[i][j]) {
        set<tuple<int, int, int, int>> peri;
        ll sz = dfs(peri, grid, vis, i, j);
        ll v = GetLines(peri);

        cout << "Outside: " << i << ' ' << j << ' ' << sz << ' ' << v << ' '
             << grid[i][j] << endl;
        // for (auto& [x, y] : peri) {
        //   cout << x << ',' << y << ' ';
        // }
        // cout << endl;

        // ans += sz * peri.size();
        ans += sz * GetLines(peri);
      }
    }
  }
  cout << ans << endl;
}
