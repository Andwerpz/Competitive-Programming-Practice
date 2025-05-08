#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<ll> vl;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

//3rd Universal Cup, Stage 7: Warsaw - L

//notice that the input is generated randomly. This means that writing a brute force tester and making
//some observations is probably the way to go. 

//calculate the number of good subarrays of some given length. You'll notice that the distribution
//peaks near 0 and near n / 2, with everything else being close to 0. So for large n just look
//close to those two points, and for small n just brute force. 

vl randperm(int n) {
    vl p(n);
    for(int i = 0; i < n; i++) p[i] = i + 1;
    random_shuffle(p.begin(), p.end());
    return p;
}

vector<ld> get_distribution(int n) {
    int tcnt = 100;
    vector<ld> ans(n + 1, 0);
    while(tcnt --){
        vl pfx(n + 1, 0);
        vl p = randperm(n);
        // cout << "P : ";
        // for(int i = 0; i < n; i++) 
        for(int i = 1; i <= n; i++) pfx[i] = pfx[i - 1] + p[i - 1];
        for(int i = 1; i <= n; i++){
            ll tgt = (ll) i * (ll) i;
            for(int j = 0; j + i <= n; j++){
                if(pfx[i + j] - pfx[j] == tgt) ans[i] ++;
            }
        }
    }
    for(int i = 1; i <= n; i++) ans[i] /= (ld) 100;
    for(int i = 1; i <= n; i++) cout << i << " : " << fixed << setprecision(10) << ans[i] << "\n";
    return ans;
}

int solve_fast(vl& p) {
    int n = p.size();
    vl pfx(n + 1, 0);
    for(int i = 1; i <= n; i++) pfx[i] = pfx[i - 1] + p[i - 1];
    int sqn = sqrt(n);
    int ans = 0;
    for(int i = 1; i <= sqn * 3; i++){
        ll tgt = (ll) i * (ll) i;
        for(int j = 0; j + i <= n; j++){
            if(pfx[i + j] - pfx[j] == tgt) ans ++;
        }
    }
    for(int i = n / 2 - sqn * 2; i <= n / 2 + sqn * 2; i++){
        ll tgt = (ll) i * (ll) i;
        for(int j = 0; j + i <= n; j++){
            if(pfx[i + j] - pfx[j] == tgt) ans ++;
        }
    }
    return ans;
}

int solve_slow(vl& p){
    int n = p.size();
    vl pfx(n + 1, 0);
    for(int i = 1; i <= n; i++) pfx[i] = pfx[i - 1] + p[i - 1];
    int ans = 0;
    for(int i = 1; i <= n; i++){
        ll tgt = (ll) i * (ll) i;
        for(int j = 0; j + i <= n; j++){
            if(pfx[i + j] - pfx[j] == tgt) ans ++;
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    // int n;
    // cin >> n;
    // get_distribution(n);

    // int n;
    // cin >> n;
    // vl p = randperm(n);
    // cout << solve_slow(p) << " " << solve_fast(p) << "\n";
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vl p(n);
        for(ll& x : p) cin >> x;
        int ans = 0;
        if(n <= 2000) ans = solve_slow(p);
        else ans = solve_fast(p);
        cout << ans << "\n";
    }

    return 0;
}