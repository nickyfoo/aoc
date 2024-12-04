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

vector<int> split(const string& line) {
  stringstream ss(line);
  string s;
  vector<int> ans;
  while (getline(ss, s, ' ')) {
    if (!s.empty()) ans.push_back(stoi(s));
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  ll ans = 0;
  vector<string> grid;
  string line;
  while (getline(cin, line)) {
    grid.push_back(line);
  }

  int m = grid.size(), n = grid[0].size();

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      // Part 1
      // string s = "XMAS";
      // vector<pair<int, int>> d8{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
      //                           {0, 1},   {1, -1}, {1, 0},  {1, 1}};
      // if (grid[i][j] == 'X') {
      //   for (auto& [di, dj] : d8) {
      //     bool found = true;
      //     for (int k = 0; k < 4; ++k) {
      //       if (0 <= i + di * k && i + di * k < m && 0 <= j + dj * k &&
      //           j + dj * k < n) {
      //         if (grid[i + di * k][j + dj * k] != s[k]) found = false;
      //       } else
      //         found = false;
      //     }
      //     if (found) {
      //       ans++;
      //     }
      //   }
      // }

      // Part 2
      // vector<pair<int, int>> d4{{-1, -1}, {1, -1}, {1, 1}, {-1, 1}};
      // string tgt = "MMSS";
      // if (grid[i][j] == 'A') {
      //   string cs;
      //   for (auto& [di, dj] : d4) {
      //     if (0 <= i + di && i + di < m && 0 <= j + dj && j + dj < n) {
      //       cs += (grid[i + di][j + dj]);
      //     }
      //   }
      //   if (cs.size() == 4) {
      //     for (int k = 0; k < 4; ++k) {
      //       if (cs == tgt) ans++;
      //       rotate(cs.begin(), cs.begin() + 1, cs.end());
      //     }
      //   }
      // }
    }
  }
  cout << ans << endl;
}
