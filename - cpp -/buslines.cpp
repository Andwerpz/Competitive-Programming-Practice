#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//KTH Challenge 2021 - B

//can make all edge sums from 3 to n + (n - 1). 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> ans(0);
    for(int i = 3; i <= n + n - 1 && ans.size() != m; i++){
        int u = min(n, i - 1);
        int v = i - u;
        if(u < 1 || v < 1 || u > n || v > n){
            break;
        }
        ans.push_back({u, v});
    }
    if(ans.size() < n - 1 || ans.size() != m) {
        cout << "-1\n";
        return 0;
    }
    for(int i = 0; i < m; i++){
        cout << ans[i].first << " " << ans[i].second << "\n";
    }
    
    return 0;
}