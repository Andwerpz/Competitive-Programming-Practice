#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC139C

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    bool reverse = false;
    if(n < m) {
        reverse = true;
        swap(n, m);
    }
    vector<pair<int, int>> ans(0);
    set<int> c0, c1;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= 3; j++){
            int x = i;
            int y = j;
            if(c0.find(x * 3 + y) != c0.end() || c1.find(x + y * 3) != c1.end()) {
                continue;
            }
            c0.insert(x * 3 + y);
            c1.insert(x + y * 3);
            ans.push_back({x, y});
        }
    }
    if(reverse) {
        for(int i = 0; i < ans.size(); i++){
            swap(ans[i].first, ans[i].second);
        }
    }
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i].first << " " << ans[i].second << "\n";
    }
    
    return 0;
}
