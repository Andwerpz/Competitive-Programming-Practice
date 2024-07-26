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

//Codeforces - 1995 B1, B2

//for the easy version, you can just do 2 pointer. 

//for the hard version, you need some math. Lets consider flowers of x and x + 1 petals. First, take as many flowers
//of x petals as you can. Then, with the remainder, take as many flowers of x + 1 petals as you can. Finally, if we have
//flowers of x + 1 petals left over, we can swap out flowers of petals x for x + 1, and increase our sum by 1. Do this
//as many times as you can, and that's the answer. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, m;
        cin >> n >> m;
        vector<pll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i].first;
        }
        for(int i = 0; i < n; i++){
            cin >> a[i].second;
        }
        sort(a.begin(), a.end());
        ll ans = 0;
        for(int i = 0; i < n; i++){
            ll va = a[i].first;
            ll ca = a[i].second;
            ll amult = min(ca, m / va);
            ll sum = amult * va;
            if(i != n - 1 && a[i].first + 1 == a[i + 1].first) {
                ll vb = a[i + 1].first;
                ll cb = a[i + 1].second;
                ll bmult = min(cb, (m - sum) / vb);
                sum += bmult * vb;
                ll rem = m - sum;
                sum += min({rem, cb - bmult, amult});
            }
            ans = max(ans, sum);
        }
        cout << ans << "\n";
    }
    
    return 0;
}