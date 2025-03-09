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

//UTPC Contest 2-26-25 Div.1 - C

//we can sort all queries and answer all of them in linear time. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vector<pii> ev(2 * n);  //{pos, change}
    vector<pii> qs(q);  //{pos, ind}
    for(int i = 0; i < n; i++){
        int l, r;
        cin >> l >> r;
        r ++;
        ev[i * 2 + 0] = {l, 1};
        ev[i * 2 + 1] = {r, -1};
    }
    sort(ev.begin(), ev.end());
    for(int i = 0; i < q; i++){
        int t;
        cin >> t;
        qs[i] = {t, i};
    }
    sort(qs.begin(), qs.end());
    int ptr = 0;
    int cans = 0;
    vi ans(q);
    for(int i = 0; i < q; i++){
        int t = qs[i].first, ind = qs[i].second;
        while(ptr != 2 * n && ev[ptr].first <= t) cans += ev[ptr].second, ptr ++;
        ans[ind] = cans;
    }
    for(int i = 0; i < q; i++){
        cout << ans[i] << "\n";
    }
    
    return 0;
}