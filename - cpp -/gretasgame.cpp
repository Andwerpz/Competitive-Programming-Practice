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

//ICPC NERC 2025-2026 - G

//my (slightly modified) notes during contest :
/*
for each round, pick a bunch of non-intersecting segments. +1 score to endpoints, then +2 score to everyone else. 
it's possible that there are some people not contained by a segment. 

observe that A[i] <= A[i + 1] + A[i - 1]
suppose that there is a 0 somewhere, can we compute the minimum rounds?

yes we can. 
observe that the amount of rounds to reduce the edges is fixed, then that fixes the amount of rounds to reduce the next edges and so on. 
The amount of rounds is simply the maximum amount of rounds to reduce anything. 

now, the case where there is not a 0, if we simulate enough rounds we'll eventually make a 0. But where is the best placement of 0?

oh, it doesn't really matter where we place 0. lets fix 0 placement at index 1. 
So then, we need to decide how many times it goes to the left vs going to the right. 

actually, a better idea is to fix the amount of times we pick the pair (0, 1). this actually fixes 
the amount of pairs we can choose everywhere. 

edge case is when all positions have an equal amount. need to just add an extra move? no, can just ceil divide by (n - 1) to find rounds. 
so ans is max(ceil(MVS / (n - 1)), MXMV)
*/

//what this thinking doesn't capture is that i also need to consider if n is even or odd.
//actually if n is odd, then there is only one selection of pairs that creates the final array, but if 
//n is even, there can be multiple. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vl a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        ll ans = 0;
        ll sum = 0;
        for(int i = 0; i < n; i++) sum += a[i];
        assert(sum % 2 == 0);
        ans = sum;
        ans /= 2;
        ans = (ans + (n - 2)) / (n - 1);    //lower bound on answer
        ll mxamt = -1;
        vl amt(n, 0);
        ll amtsum = 0;
        for(int i = 1; i < n; i++) {
            amt[i] = a[i] - amt[i - 1];
            amtsum += amt[i];
        }
        if(n % 2 == 0) {
            //we can optimize the max amount
            //first, make it so that even elements are not negative
            ll inc = 0;
            for(int i = 0; i < n; i += 2) {
                inc = max(inc, -amt[i]);
            }
            amt[0] = inc;
            for(int i = 1; i < n; i++) {
                amt[i] = a[i] - amt[i - 1];
                assert(amt[i] >= 0);
            }
            //now, find the point at which maximum is minimized, and everything is still non-negative
            ll mnodd = 1e18, mxodd = -1e18;
            ll mxev = -1e18;
            for(int i = 0; i < n; i++) {
                if(i % 2 == 0) mxev = max(mxev, amt[i]);
                else {
                    mxodd = max(mxodd, amt[i]);
                    mnodd = min(mnodd, amt[i]);
                }
            }
            for(ll B = 30; B >= 0; B--) {
                ll incamt = (1 << B);
                if(incamt > mnodd) continue;
                if(mxev + incamt > mxodd - incamt) continue;
                mnodd -= incamt;
                mxodd -= incamt;
                mxev += incamt;
            }
            mxamt = max(mxev, mxodd);
        }
        else {
            assert(n % 2 == 1);
            //there is a fixed max amount
            ll inc = (sum / 2) - amtsum;
            assert(inc >= 0);
            amt[0] = inc;
            amtsum = inc;
            mxamt = inc;
            for(int i = 1; i < n; i++) {
                amt[i] = a[i] - amt[i - 1];
                amtsum += amt[i];
                assert(amt[i] >= 0);
                mxamt = max(mxamt, amt[i]);
            }
            // for(int i = 0; i < n; i++) cout << amt[i] << " ";
            // cout << endl;
            assert(amtsum == (sum / 2));
        }
        assert(mxamt != -1);
        ans = max(ans, mxamt);
        cout << ans << "\n";
    }
    
    return 0;
}