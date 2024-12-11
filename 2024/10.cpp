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

vector<int> split(const string& line, char delim = ' ') {
  stringstream ss(line);
  string s;
  vector<int> ans;
  while (getline(ss, s, delim)) {
    if (!s.empty()) ans.push_back(stoi(s));
  }
  return ans;
}

vector<pair<int, int>> d4{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  vector<string> grid;
  string line;
  while (getline(cin, line)) {
    grid.push_back(line);
  }

  int ans = 0;
  for (int i = 0; i < grid.size(); ++i) {
    for (int j = 0; j < grid[i].size(); ++j) {
      if (grid[i][j] == '0') {
        vector<vector<int>> vis(grid.size(), vector<int>(grid[0].size(), 0));
        ans += dfs(grid, vis, i, j);
      }
    }
  }
  cout << ans << endl;
}
