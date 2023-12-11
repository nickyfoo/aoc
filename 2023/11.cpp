#include <iostream>
#include <string>
using namespace std;
using ll = long long;

vector<string> grid;
int m, n;
vector<int> cols, rows;
vector<pair<int, int>> galaxies;

void getEmpty()
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == '#')
            {
                galaxies.push_back({i, j});
                rows[i]++;
                cols[j]++;
            }
        }
    }
}

ll getD(ll mult)
{
    ll ans = 0;
    for (int i = 0; i < galaxies.size(); i++)
    {
        auto &[ix, iy] = galaxies[i];
        for (int j = i + 1; j < galaxies.size(); j++)
        {
            auto &[jx, jy] = galaxies[j];
            int lx = min(ix, jx);
            int hx = max(ix, jx);
            int ly = min(iy, jy);
            int hy = max(iy, jy);
            int inter = 0;
            for (int k = lx; k <= hx; k++)
            {
                inter += rows[k] == 0;
            }
            for (int k = ly; k <= hy; k++)
            {
                inter += cols[k] == 0;
            }
            ans += inter * (mult - 1) + hx - lx + hy - ly;
        }
    }
    return ans;
}

int main()
{
    string line;
    while (getline(cin, line))
    {
        grid.push_back(line);
    }
    m = grid.size();
    n = grid[0].size();
    rows.assign(m, 0);
    cols.assign(n, 0);
    getEmpty();
    cout << getD(1000000);
    return 0;
}
