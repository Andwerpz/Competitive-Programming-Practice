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

//ICPC NERC 2025-2026 - A

//this problem statement is hard to read lmao

//we can calculate each street in O(1), just have to keep track for each letter, how many we have
//and how many streets require each letter

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    vl ft(26, 0), f(26, 0);
    for(int i = 0; i < n; i++) {
        for(char c : a[i]) {
            ft[c - 'A'] += m;
            f[c - 'A'] ++;
        }
    }
    vl ans(n, 0);
    for(int i = 0; i < n; i++) {
        for(char c : a[i]) {
            ft[c - 'A'] -= m + 1;
            f[c - 'A'] --;
        }
        bool is_valid = true;
        for(int j = 0; j < 26; j++) if(ft[j] < 0) is_valid = false;
        if(!is_valid) {
            ans[i] = -1;
        }
        else {
            ans[i] = 1e18;
            for(int j = 0; j < 26; j++) {
                if(f[j] == 0) continue;
                ans[i] = min(ans[i], ft[j] / f[j]);
            }
        }
        for(char c : a[i]) {
            ft[c - 'A'] += m + 1;
            f[c - 'A'] ++;
        }
    }
    for(int i = 0; i < n; i++) cout << ans[i] << " ";
    cout << "\n";
    
    return 0;
}