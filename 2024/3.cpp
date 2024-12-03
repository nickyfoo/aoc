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
bool enabled = true;

ll parse(const string& line) {
  int pos = 0;
  ll ans = 0;
  while (true) {
    int i = line.find("mul(", pos);
    int dopos = line.find("do(", pos);
    int dontpos = line.find("don't(", pos);
    int m = min<int>({i == -1 ? INT_MAX : i, dopos == -1 ? INT_MAX : dopos,
                      dontpos == -1 ? INT_MAX : dontpos});
    if (m == -1) break;
    if (dopos == m) {
      cout << "Do: " << dopos << endl;
      enabled = true;
      pos = dopos + 1;
    } else if (dontpos == m) {
      cout << "Don't: " << dontpos << endl;
      enabled = false;
      pos = dontpos + 1;
    }
    if (i == -1) break;
    // cout << pos << ' ' << i << endl;
    int x = 0, y = 0;
    int j = i + 4;
    bool valid = true;
    for (;; ++j) {
      if (line[j] == ',') break;
      if (!isdigit(line[j])) valid = false;
      x *= 10;
      x += line[j] - '0';
    }
    j++;
    for (;; ++j) {
      //   cout << line[j] << endl;
      if (line[j] == ')') break;
      if (!isdigit(line[j])) valid = false;
      y *= 10;
      y += line[j] - '0';
    }

    if (valid && enabled) {
      ans += x * y;
      cout << x << ' ' << y << ' ' << (x * y) << endl;
    }
    pos = i + 1;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout << "HERE" << endl;
  ll ans = 0;
  string line;
  while (getline(cin, line)) {
    ans += parse(line);
  }
  cout << ans;
}
