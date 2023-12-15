#include <iostream>
#include <string>
#include <map>
#include <sstream>
using namespace std;
using ll = long long;

int h(string &s)
{
    int currVal = 0;
    for (auto &c : s)
    {
        currVal += c;
        currVal *= 17;
        currVal %= 256;
    }
    return currVal;
}

int process(vector<string> &toks)
{
    int ans = 0;
    for (auto &tok : toks)
    {
        ans += h(tok);
    }
    return ans;
}

int process2(vector<string> &toks)
{
    vector<vector<pair<string, int>>> lenses(256);
    unordered_map<string, int> labelToBox;
    for (auto &tok : toks)
    {
        if (tok.find('=') != -1)
        {
            string label = tok.substr(0, tok.find('='));
            int box = h(label);
            labelToBox[label] = box;

            bool found = false;
            for (auto it = lenses[box].begin(); it != lenses[box].end(); it++)
            {
                if (it->first == label)
                {
                    it->second = tok.back() - '0';
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                lenses[box].push_back({label, tok.back() - '0'});
            }
        }
        else
        {
            string label = tok.substr(0, tok.find('-'));
            int box = labelToBox[label];
            for (auto it = lenses[box].begin(); it != lenses[box].end(); it++)
            {
                if (it->first == label)
                {
                    lenses[box].erase(it);
                    break;
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < 256; i++)
    {
        int slot = 1;
        for (auto &[label, len] : lenses[i])
        {
            // cout << i << ": " << slot << ' ' << label << ' ' << len << '\n';
            ans += (i + 1) * (slot++) * len;
        }
    }
    return ans;
}

int main()
{
    freopen("input.txt", "r", stdin);
    string line;
    getline(cin, line);
    stringstream ss(line);
    string s;
    vector<string> toks;

    while (getline(ss, s, ','))
    {
        toks.push_back(s);
    }

    cout << process(toks) << endl;
    cout << process2(toks) << endl;

    return 0;
}
