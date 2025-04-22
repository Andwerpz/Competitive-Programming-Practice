#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

void lower_by(ll& val, ll& by) {
    ll amt = min(val, by);
    val -= amt, by -= amt;
}

bool solve(int n, vl h, ll val) {
    for(int i = 0; i < n; i++){
        ll ex = val - h[i];
        if(ex >= 0) {
            //where can we apply these extra operations?
            //first, lower behind if needed
            if(i != 0){
                ll bamt = h[i - 1] - val;
                if(bamt > 0) {
                    ll diff = min(ex, bamt);
                    ex -= diff, h[i - 1] -= diff;
                }
            }
            //place everything else in front
            if(i != n - 1) {
                ll famt = h[i + 1] - h[i];
                ll diff = famt / 2;
                if(famt > 0) {
                    diff = min(diff, ex);
                    ex -= diff, h[i + 1] -= diff;
                }
            }
        }
        else {
            //heelp mee
        }
    }
    for(int i = 0; i < n; i++) if(h[i] > val) return false;
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;
    vl h(n);
    for(int i = 0; i < n; i++) cin >> h[i];
    ll low = 0, high = 1e9 + 100;
    ll ans = high;
    while(low <= high) {
        ll mid = low + (high - low) / 2;
        if(solve(n, h, mid)) ans = mid, high = mid - 1;
        else low = mid + 1;
    }
    cout << ans << "\n";

    return 0;
}