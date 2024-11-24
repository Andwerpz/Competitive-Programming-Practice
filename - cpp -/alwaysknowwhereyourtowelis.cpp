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

//2024 NA Mid Central Regional - B

//guessforces lol

vl gen(vl a){
    vl ans((1 << (int) a.size()));
    for(int i = 0; i < (1 << (int) a.size()); i++){
        ll cur = 0;
        for(int j = 0; j < a.size(); j++){
            if(i & (1 << j)) {
                cur += a[j];
            }
        }
        ans[i] = cur;
    }
    sort(ans.begin(), ans.end());
    return ans;
}

//sorted ascending
bool check(vl& a, vl& b, ll val) {
    int bptr = b.size() - 1;
    ll ways = 0;
    for(int i = 0; i < a.size(); i++){
        while(bptr != -1 && a[i] + b[bptr] > val){
            bptr --;
        }
        if(bptr != -1 && a[i] + b[bptr] == val) {
            ways ++;
        }
        if(ways >= 2) return true;
    }
    return false;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    ll sum = 0;
    vl a(n);
    vl l(0), r(0);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        sum += a[i];
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    // random_shuffle(a.begin(), a.end());
    for(int i = 0; i < n; i++){
        if(i < n / 2) l.push_back(a[i]);
        else r.push_back(a[i]);
    }
    vl sl = gen(l), sr = gen(r);
    ll ans = -1;
    for(int i = 0; i < n; i++){
        // cout << "CHECK : " << sum << "\n";
        if(check(sl, sr, sum / 2)) {
            ans = sum / 2;
            break;
        }
        sum -= a[i];
    }
    cout << ans << "\n";
    
    return 0;
}