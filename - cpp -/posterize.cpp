#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2017 - F

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    
    int d, k; cin >> d >> k;
    vector<ll> freq(257);
    for (int i = 0; i < d; ++i) {
        int r; cin >> r;
        cin >> freq[r];
    }

    vector<vector<ll>> prec(257, vector<ll> (257));

    for (ll i = 0; i <= 255; ++i) {
        prec[i][255] = (255-i) * (255-i) * freq[255];
        for (ll j = 254; j > -1; --j) {
            prec[i][j] = prec[i][j+1] + (i - j) * (i - j) * freq[j];
        }
    }

    // cerr << "prec00 : " << prec[200][200] << endl;

    vector<vector<ll>> dp(257, vector<ll> (257, 1e17));

    for (ll i = 0; i <= 255; ++i) {
        dp[i][1] = prec[i][0];
        for (ll j = 2; j <= k; ++j) {
            // cerr << "hey" << endl;
            for (ll l = 0; l < i; ++l) {
                ll comp = dp[l][j-1] - prec[l][(l+i+1)/2] + prec[i][(l+i+1)/2];
                dp[i][j] = min(dp[i][j], comp);
            }
        }
    }

    ll mn = 1e18;

    for (int i = 0; i <= 255; ++i) {
        mn = min(mn, dp[i][k]);
    }

    cout << mn << endl;

    return 0;
}
