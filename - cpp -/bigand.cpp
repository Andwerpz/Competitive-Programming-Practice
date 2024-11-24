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

//2024 NA Mid Central Regional - C

//can binary search over the delay. 
//for a given delay, compute the required amounts of inputs at each layer. 

ll n, d, l;
bool is_valid(vl& a, ll mxd) {
    ll cnt = 1;
    ll left = 2;
    for(int i = 0; i < a.size(); i++){
        ll mx_cnt = (mxd - a[i] - l) / d;
        if(mx_cnt > 40){
            return true;
        }
        if(mx_cnt < cnt) {
            return false;
        }
        while(cnt != mx_cnt){
            cnt ++;
            left *= 2;
        }
        if(left == 0){
            return false;
        }
        left --;
    }
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> n >> d >> l;
    vl a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    ll low = 0;
    ll high = 1e18;
    ll ans = high;
    while(low <= high){
        ll mid = low + (high - low) / 2;
        if(is_valid(a, mid)) {
            ans = mid;
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    cout << ans << "\n";
    
    return 0;
}