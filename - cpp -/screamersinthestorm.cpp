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

//CTU Open 2021 - J

const ll MOD = 1e9 + 7;

vector<vector<ll>> matmult(vector<vector<ll>> &a, vector<vector<ll>> &b) {
    vector<vector<ll>> c(a.size(), vector<ll>(a.size()));

    for(int i = 0; i < a.size(); i++) {
        for(int j = 0; j < a.size(); j++) {
            for(int k = 0; k < a.size(); k++) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return c;
}

vector<vector<ll>> matexp(vector<vector<ll>> &a, vector<vector<ll>> &b, ll pow) {
    while(pow) {
        if(pow & 1) {
            a = matmult(a,b);
        }
        pow /= 2;
        b = matmult(b,b);
    }
    return a;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll k, n; cin >> k >> n;

    vector<vector<ll>> a(k, vector<ll>(k));

    for(int i = 1; i <= k; i++) {
        for(int j = 1; j <= k; j++) {
            if(gcd(i,j) == 1) {
                a[i-1][j-1] = 1;
            }
        }
    }

    vector<vector<ll>> res(k, vector<ll>(k));
    for(int i = 0; i < k; i++) {
        res[i][i] = 1;
    }

    res = matexp(res, a, n - 1);

    ll ans = 0;
    for(auto &x : res) {
        for(auto &y : x) {
            ans += y;
        }
    }

    cout << ans % MOD << '\n';
    
    return 0;
}