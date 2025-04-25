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

//Spring 2025 Columbia University Local Contest - B

//linear search on the primes suffices as well

vector<ll> lp; //lowest prime factor 
vector<ll> pr; //prime list

void prime_sieve(ll n) {
    lp = vector<ll>(n + 1);
    pr = vector<ll>(0);
    for(ll i = 2; i <= n; i++) {
        if(lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (ll j = 0; i * pr[j] <= n; j++) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
}

//largest prime index that is <= tgt
int lfp(int tgt) {
    int low = 0, high = pr.size() - 1;
    int ans = low;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(pr[mid] <= tgt) ans = mid, low = mid + 1;
        else high = mid - 1;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    prime_sieve(1e6 + 100);
    int t;
    cin >> t;
    while(t--){
        int l, r;
        cin >> l >> r;
        int li = lfp(l), ri = lfp(r);
        if(pr[li] < l) li ++;
        if(li >= ri) cout << "-1\n";
        else {
            int ans = 1e9;
            for(int i = li; i < ri; i++) ans = min(ans, (int) (pr[i + 1] - pr[i]));
            cout << ans << "\n";
        }
    }
    
    return 0;
}