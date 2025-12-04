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

//Kattis - greetings
//NAIPC 2016 - C

//can easily find cost for some subset of letters, just find the envelope that fits tightly to the subset. 
//dp[S][i] = cost for all letters in set S given that we've bought i letters
//issue is, have to add subset to S, can't add single element
//observation: actually, how many envelope sizes are actually relevant?
// only around n^2 envelope sizes are actually relevant (needs to be of existing letter width, height)
// so instead if 2^n transitions, only really have n^2 unique transitions.

//hmm, but then each transition gets less information, namely which letters does it apply to?
//if a letter can be contained by two different envelopes, it will always want to be contained by the one with smaller area. 
//so if we fix the envelope sizes, then the optimal solution is just to greedily pick for each letter the envelope with smallest
//area that can contain that letter. 

//so as long as we compute for each transition, the cost to contain only the letters that are not already contained, then 
//there will exist an ordering of transitions such that we get the optimal solution. 

//can do in O(2^n * n^3) by observing that the cost per transition doesn't depend on how many envelopes we've purchased. 
//also need to be constant factor aware, time limit is quite tight. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vector<array<ll, 3>> a(n);  //{w, h, q}
    for(int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
    }
    vector<array<ll, 3>> ev;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            ll w = a[i][0];
            ll h = a[j][1];
            int bits = 0;
            for(int ii = 0; ii < n; ii++) {
                if(w >= a[ii][0] && h >= a[ii][1]) {
                    bits |= (1 << ii);
                }
            }
            ev.push_back({w, h, bits});
        }
    }
    vector<ll> evc(ev.size());
    vector<vector<ll>> asc(ev.size(), vl(n));
    for(int i = 0; i < ev.size(); i++) {
        for(int j = 0; j < n; j++) {
            if(ev[i][0] >= a[j][0] && ev[i][1] >= a[j][1]) {
                asc[i][j] = (ev[i][0] * ev[i][1] - a[j][0] * a[j][1]) * a[j][2];
            }
        }
    }
    vector dp((1 << n), vector<ll>(k + 1, 1e18));
    dp[0][0] = 0;
    for(int bits = 0; bits < (1 << n); bits++) {
        for(int i = 0; i < ev.size(); i++) {
            ll cost = 0;
            for(int j = 0; j < n; j++) {
                if(bits & (1 << j)) continue;
                if(ev[i][0] >= a[j][0] && ev[i][1] >= a[j][1]) {
                    cost += asc[i][j];
                }
            }
            evc[i] = cost;
        }
        for(int i = 0; i < k; i++) {
            for(int j = 0; j < ev.size(); j++) {
                dp[bits | ev[j][2]][i + 1] = min(dp[bits | ev[j][2]][i + 1], dp[bits][i] + evc[j]);
            }
        }
    }
    ll ans = 1e18;
    for(int i = 0; i <= k; i++) ans = min(ans, dp[(1 << n) - 1][i]);
    cout << ans << "\n";
    
    return 0;
}