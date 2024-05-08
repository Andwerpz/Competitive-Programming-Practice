#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//ACPC 2024 Spring Contest - F

//notice that the number of rows must be a divisor of |S|, and there aren't that many divisors, so
//we can just try them all. 

bool do_test(string& s, int n, int m) {
    vector<int> dr = {-1, 1, 0, 0, -1, -1, 1, 1};
    vector<int> dc = {0, 0, -1, 1, 1, -1, 1, -1};
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(s[i * m + j] != 'T') {
                continue;
            }
            for(int k = 0; k < 8; k++){
                int nr = i + dr[k];
                int nc = j + dc[k];
                if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                    continue;
                }
                if(s[nr * m + nc] == 'T') {
                    return false;
                }
            }
        }
    }
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s;
    cin >> s;
    vector<pair<int, int>> ans(0);
    for(int i = 1; i <= s.size(); i++){
        if(s.size() % i == 0 && do_test(s, i, s.size() / i)){
            ans.push_back({i, s.size() / i});
        }
    }
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i].first << "x" << ans[i].second << "\n";
    }
    
    return 0;
}
