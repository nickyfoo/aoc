#include <iostream>
#include <map>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <queue>
using namespace std;
using ll = long long;

unordered_set<int> emptyCol, emptyRow;

void getEmpty(vector<string> &grid)
{
    int m = grid.size();
    int n = grid[0].size();
    vector<string> ans;
    for (int j = 0; j < n; j++)
    {
        int inter = 0;
        for (int i = 0; i < m; i++)
        {
            if (grid[i][j] == '#')
                inter++;
        }
        if (inter == 0)
            emptyCol.insert(j);
    }
    for (int i = 0; i < m; i++)
    {
        int inter = 0;
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == '#')
                inter++;
        }
        if (inter == 0)
            emptyRow.insert(i);
    }
}
vector<string> expand(vector<string> &grid)
{
    int m = grid.size();
    int n = grid[0].size();
    vector<string> ans;

    for (int i = 0; i < m; i++)
    {
        string inter = "";
        for (int j = 0; j < n; j++)
        {
            inter += grid[i][j];
            if (emptyCol.count(j))
            {
                inter += '.';
            }
        }
        ans.push_back(inter);
        if (emptyRow.count(i))
        {
            ans.push_back(string(n + emptyCol.size(), '.'));
        }
    }
    cout << ans.size() << '\n';
    return ans;
}

vector<pair<int, int>> d4{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
ll getD(vector<string> &grid, ll mult)
{

    int m = grid.size(), n = grid[0].size();
    vector<pair<int, int>> s;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == '#')
            {
                s.push_back({i, j});
            }
        }
    }
    ll ans = 0;
    int count = 0;
    for (int i = 0; i < s.size(); i++)
    {
        queue<pair<int, int>> q;
        q.push(s[i]);
        vector<vector<ll>> d(m, vector<ll>(n, -1));
        d[s[i].first][s[i].second] = 0;
        while (q.size())
        {
            auto [i, j] = q.front();
            q.pop();
            for (auto &[di, dj] : d4)
            {
                if (0 <= i + di && i + di < m && 0 <= j + dj && j + dj < n && d[i + di][j + dj] == -1)
                {
                    d[i + di][j + dj] = d[i][j] + emptyRow.count(i + di) + emptyCol.count(j + dj);
                    q.push({i + di, j + dj});
                }
            }
        }
        for (auto &[ox, oy] : s)
        {
            ans += d[ox][oy] * (mult - 1) + llabs(s[i].first - ox) + llabs(s[i].second - oy);
        }
    }
    return ans;
}

int main()
{
    string line;
    vector<string> grid;
    cout << "HERE\n";
    while (getline(cin, line))
    {
        grid.push_back(line);
    }
    getEmpty(grid);
    // grid = expand(grid);

    for (auto &x : grid)
    {
        cout << x << '\n';
    }
    cout << getD(grid, 1000000) / 2;
    return 0;
}
