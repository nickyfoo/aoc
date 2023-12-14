#include <iostream>
#include <string>
#include <map>
using namespace std;
using ll = long long;

void tiltNorth(vector<string> &grid)
{
    int m = grid.size(), n = grid[0].size();
    for (int j = 0; j < n; j++)
    {
        int prevPos = 0;
        for (int i = 0; i < m; i++)
        {
            if (grid[i][j] == 'O')
            {
                swap(grid[prevPos++][j], grid[i][j]);
            }
            else if (grid[i][j] == '#')
            {
                prevPos = i + 1;
            }
        }
    }
}
void tiltSouth(vector<string> &grid)
{
    int m = grid.size(), n = grid[0].size();
    for (int j = 0; j < n; j++)
    {
        int prevPos = m - 1;
        for (int i = m - 1; i >= 0; i--)
        {
            if (grid[i][j] == 'O')
            {
                swap(grid[prevPos--][j], grid[i][j]);
            }
            else if (grid[i][j] == '#')
            {
                prevPos = i - 1;
            }
        }
    }
}

void tiltWest(vector<string> &grid)
{
    int m = grid.size(), n = grid[0].size();
    for (int i = 0; i < m; i++)
    {
        int prevPos = 0;
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == 'O')
            {
                swap(grid[i][prevPos++], grid[i][j]);
            }
            else if (grid[i][j] == '#')
            {
                prevPos = j + 1;
            }
        }
    }
}

void tiltEast(vector<string> &grid)
{
    int m = grid.size(), n = grid[0].size();
    for (int i = 0; i < m; i++)
    {
        int prevPos = n - 1;
        for (int j = n - 1; j >= 0; j--)
        {
            if (grid[i][j] == 'O')
            {
                swap(grid[i][prevPos--], grid[i][j]);
            }
            else if (grid[i][j] == '#')
            {
                prevPos = j - 1;
            }
        }
    }
}

void cycle(vector<string> &grid)
{
    tiltNorth(grid);
    tiltWest(grid);
    tiltSouth(grid);
    tiltEast(grid);
}

int getLoad(vector<string> &grid)
{
    int m = grid.size(), n = grid[0].size();
    int ans = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == 'O')
            {
                ans += grid.size() - i;
            }
        }
    }
    return ans;
}

int main()
{
    freopen("input.txt", "r", stdin);
    string line;
    vector<string> grid;
    while (getline(cin, line))
    {
        grid.push_back(line);
    }
    int m = grid.size(), n = grid[0].size();
    ll cycleCount = 0;
    map<vector<string>, ll> mapper;
    while (mapper.find(grid) == mapper.end())
    {
        mapper[grid] = cycleCount++;
        cycle(grid);
    }
    cout << "Prev: " << mapper[grid] << '\n';
    cout << "Curr: " << cycleCount << '\n';
    ll cycleSize = cycleCount - mapper[grid];
    cout << "CycleSize: " << cycleSize << '\n';
    ll target = 1000000000;
    target -= cycleCount;
    target %= cycleSize;
    cout << target << '\n';
    for (int i = 0; i < target; i++)
    {
        cycle(grid);
    }
    for (auto &x : grid)
        cout << x << '\n';
    cout << getLoad(grid);
    return 0;
}
