#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

//SWERC 2020 - A

//just sort stuff

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n, k;
    cin >> n >> k;
    string line;
    getline(cin, line);
    map<string, pair<int, int>> m;
    for(int i = 0; i < n * 3; i++) {
        getline(cin, line);
        pair<int, int> prev = m[line];
        m[line] = {prev.first + 1, i};
    }
    vector<pair<string, pair<int, int>>> ord;
    for(auto i = m.begin(); i != m.end(); i++) {
        ord.push_back({i->first, i->second});
    }
    sort(ord.begin(), ord.end(), [](pair<string, pair<int, int>>& a, pair<string, pair<int, int>>& b) -> bool {
        if(a.second.first != b.second.first) return a.second.first > b.second.first;
        return a.second.second > b.second.second;
    });
    for(int i = 0; i < min((int) ord.size(), k); i++) {
        cout << ord[i].first << "\n";
    }   

    return 0;
}
