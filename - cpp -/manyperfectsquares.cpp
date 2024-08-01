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

int test_x(vl& a, ll x){
    // cout << "TEST X : " << x << "\n";
    int ans = 0;
    for(int i = 0; i < a.size(); i++){
        ll cur = a[i] + x;
        ll sq = floor(sqrt(cur));
        // cout << "CUR : " << cur << " " << (sq * sq == cur) << "\n";
        ans += sq * sq == cur;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vl a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int ans = 1;
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                ll diff = a[j] - a[i];
                ll amt = 2 - (diff % 2);
                while(true){
                    // cout << "AMT : " << amt << endl;
                    ll x = diff / amt - (amt - 1);
                    ll tmp = (x - 1) / 2;
                    if(x <= 0 || tmp * tmp < a[i]) {
                        break;
                    }
                    if((x % 2) != 1 || diff % amt != 0){
                        amt += 2;
                        continue;
                    }
                    ll psq = tmp * tmp;
                    ans = max(ans, test_x(a, psq - a[i]));
                    amt += 2;
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}