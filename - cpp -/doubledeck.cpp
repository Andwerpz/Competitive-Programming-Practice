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

//NCPC 2024 - D

//lis?

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k; cin >> n >> k;
    vector<int> a(n*k), b(n*k);
    for (auto& x : a)
        cin >> x;
    for (auto& x : b)
        cin >> x;
    
    vector<int> dp(k*n+1, 1e9);
    dp[0] = -1;
    
    vector<vector<int>> aa(n+1);

    for (int i = n*k-1; i > -1; --i) {
        aa[b[i]].push_back(i);
    }

    for (int i = 0; i < n*k; ++i) {
        for (auto idx : aa[a[i]]) {
            int lo = 0, hi = n*k;
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                if (dp[mid] >= idx)
                    hi = mid;
                else
                    lo = mid+1;
            }
            dp[lo] = idx;
        }
    }

    int cnt = 0;
    for (int i = n*k; i; --i) {
        if (dp[i] < 1e9) {
            cout << i << "\n";
            return 0;
        }
    }
    
    return 0;
}