#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

struct SegtreeLazy {
    public:
        ll n;
        ll* t;    //stores product of range
        ll* d;    //lazy tree
        bool* upd;   //upd[i] = true if t[i] needs to be updated
        ll uneut, qneut;

        //single element modify
        function<ll(ll, ll)> fmodify;

        //k element modify
        function<ll(ll, ll, ll)> fmodifyk;

        //product of two elements for query
        function<ll(ll, ll)> fcombine;

        SegtreeLazy(ll maxSize, ll updateNeutral, ll queryNeutral, function<ll(ll, ll)> fmodify, function<ll(ll, ll, ll)> fmodifyk, function<ll(ll, ll)> fcombine) {
            n = maxSize;
            uneut = updateNeutral;
            qneut = queryNeutral;

            this -> fmodify = fmodify;
            this -> fmodifyk = fmodifyk;
            this -> fcombine = fcombine;

            //raise n to nearest pow 2
            ll x = 1;
            while(x < n) {
                x <<= 1;
            }
            n = x;

            t = new ll[n * 2];
            d = new ll[n * 2];
            upd = new bool[n * 2];

            //make sure to initialize values
            for(ll i = 0; i < n * 2; i++){
                t[i] = uneut;
            }
            for(ll i = 0; i < n * 2; i++){
                d[i] = uneut;
                upd[i] = false;
            }
        }

        void modify(ll l, ll r, ll val) {    //modifies the range [l, r)
            _modify(l, r, val, 0, n, 1);
        }

        ll query(ll l, ll r) {   //queries the range [l, r)
            return _query(l, r, 0, n, 1);
        }

    private:
        //calculates value of node based off of children
        //k is the amount of values that this node represents. 
        void combine(ll ind, ll k) {
            if(ind >= n){
                return;
            }
            ll l = ind * 2;
            ll r = ind * 2 + 1;
            //make sure children are correct value before calculating
            push(l, k / 2);
            push(r, k / 2);
            t[ind] = fcombine(t[l], t[r]);
        }

        //registers a lazy change llo this node
        void apply(ll ind, ll val) {
            upd[ind] = true;
            d[ind] = fmodify(d[ind], val);
        }

        //applies lazy change to this node
        //k is the amount of values that this node represents. 
        void push(ll ind, ll k) {
            if(!upd[ind]) {
                return;
            }
            t[ind] = fmodifyk(t[ind], d[ind], k);
            if(ind < n) {
                ll l = ind * 2;
                ll r = ind * 2 + 1;
                apply(l, d[ind]);
                apply(r, d[ind]);
            }
            upd[ind] = false;
            d[ind] = uneut;
        }

        void _modify(ll l, ll r, ll val, ll tl, ll tr, ll ind) {
            if(l == r){
                return;
            }
            if(upd[ind]){
                push(ind, tr - tl);
            }
            if(l == tl && r == tr) {
                apply(ind, val);
                push(ind, tr - tl);
                return;
            }
            ll mid = tl + (tr - tl) / 2;
            if(l < mid) {
                _modify(l, min(r, mid), val, tl, mid, ind * 2);
            }
            if(r > mid) {
                _modify(max(l, mid), r, val, mid, tr, ind * 2 + 1);
            }
            combine(ind, tr - tl);
        }

        ll _query(ll l, ll r, ll tl, ll tr, ll ind) {
            if(l == r){
                return qneut;
            }  
            if(upd[ind]) {
                push(ind, tr - tl);
            }
            if(l == tl && r == tr){
                return t[ind];
            }
            ll mid = tl + (tr - tl) / 2;
            ll lans = qneut;
            ll rans = qneut;
            if(l < mid) {
                lans = _query(l, min(r, mid), tl, mid, ind * 2);
            }
            if(r > mid) {
                rans = _query(max(l, mid), r, mid, tr, ind * 2 + 1);
            }
            return fcombine(lans, rans);
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll large = 1e18;
    int t;
    cin >> t;
    while(t--){
        ll n, k;
        cin >> n >> k;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<ll> hot(k + 1);
        vector<ll> cold(k + 1);
        for(int i = 1; i <= k; i++){
            cin >> cold[i];
        }
        for(int i = 1; i <= k; i++){
            cin >> hot[i];
        }
        //base state
        function<ll(ll, ll)> fmodify = [](const ll src, const ll val) -> ll{return src + val;};
        function<ll(ll, ll, ll)> fmodifyk = [](const ll src, const ll val, const ll k) -> ll{return src + val;};
        function<ll(ll, ll)> fcombine = [](const ll a, const ll b) -> ll{return min(a, b);};
        SegtreeLazy segt(3 * 1e5 + 100, 0, large, fmodify, fmodifyk, fcombine);
        segt.modify(0, k + 1, large);
        while(segt.query(0, 1) != 0){
            segt.modify(0, 1, -segt.query(0, 1));
        }
        // for(int j = 0; j <= k; j++){
        //     ll next = segt.query(j, j + 1);
        //     cout << (next > 1e15? "." : to_string(next)) << " ";
        // }
        // cout << "\n";
        for(int i = 0; i < n; i++){
            //run next program on cpu with a[i - 1]. 
            //if a[i - 1] == a[i], then everyone should use hot. 
            ll prev = i == 0? 0 : a[i - 1];
            ll base_add = (i != 0 && a[i] == prev)? hot[a[i]] : cold[a[i]];
            //make the previous a[i] into the wildcard
            ll prev_w_val = min(cold[a[i]] + segt.query(0, k + 1), hot[a[i]] + segt.query(a[i], a[i] + 1));
            segt.modify(0, k + 1, base_add);
            ll mamt = prev_w_val - segt.query(prev, prev + 1);
            mamt = min(mamt, 0ll);
            //cout << mamt << " " << mamt + segt.query(prev, prev + 1) << "\n";
            while(segt.query(prev, prev + 1) != 0){
                segt.modify(prev, prev + 1, -segt.query(prev, prev + 1));
            }
            //cout << segt.query(prev, prev + 1) << "\n";
            segt.modify(prev, prev + 1, prev_w_val);
            //segt.modify(prev, prev + 1, mamt);
            
            // cout << "BASE ADD : " << base_add << "\n";
            // cout << "PREV_W_VAL : " << prev_w_val << " " << prev << " " << segt.query(prev, prev + 1) << "\n";
            // for(int j = 0; j <= k; j++){
            //     ll next = segt.query(j, j + 1);
            //     cout << (next > 1e15? "." : to_string(next)) << " ";
            // }
            // cout << "\n";
        }
        cout << segt.query(0, k + 1) << "\n";


        // ll unv = 1e18;
        // vector<vector<ll>> dp(n + 1, vector<ll>(k + 1, unv));
        // dp[0][0] = 0;
        // for(int i = 0; i < n; i++){
        //     for(int j = 0; j <= k; j++){
        //         if(dp[i][j] == unv) {
        //             continue;
        //         }
        //         int prev = i == 0? 0 : a[i - 1];
        //         //run next program on cpu with j
        //         if(a[i] == j) {
        //             dp[i + 1][prev] = min(dp[i + 1][prev], dp[i][j] + hot[a[i] - 1]);
        //         }
        //         else {
        //             dp[i + 1][prev] = min(dp[i + 1][prev], dp[i][j] + cold[a[i] - 1]);
        //         }
        //         //run next program on cpu with a[i - 1]
        //         if(i != 0 && a[i] == prev) {
        //             dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + hot[a[i] - 1]);
        //         }
        //         else {
        //             dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + cold[a[i] - 1]);
        //         }
        //     }
        // }
        // for(int i = 0; i <= n; i++){
        //     for(int j = 0; j <= k; j++){
        //         cout << (dp[i][j] == unv? "." : to_string(dp[i][j])) << " ";
        //     }
        //     cout << "\n";
        // }
        // ll ans = 1e18;
        // for(int i = 0; i <= k; i++){
        //     ans = min(ans, dp[n][i]);
        // }
        // cout << ans << "\n";
    }
    
    return 0;
}
