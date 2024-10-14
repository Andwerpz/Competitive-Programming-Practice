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

//Codeforces - 1824A

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        int lcnt = 0, rcnt = 0;
        vi a(n);
        set<int> s;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            if(a[i] == -1){
                lcnt ++;
            }
            else if(a[i] == -2){
                rcnt ++;
            }
            else {
                s.insert(a[i] - 1);
            }
        }
        int ans = 0;
        ans = max(ans, min(m, lcnt + (int) s.size()));
        ans = max(ans, min(m, rcnt + (int) s.size()));
        int cnt = 0;
        for(auto i = s.begin(); i != s.end(); i++){
            int cur = *i;
            int l = cur - cnt;
            int r = m - 1 - cur - (s.size() - cnt - 1);
            ans = max(ans, (int) s.size() + min(l, lcnt) + min(r, rcnt));
            cnt ++;
        }
        cout << ans << "\n";
    }
    
    return 0;
}