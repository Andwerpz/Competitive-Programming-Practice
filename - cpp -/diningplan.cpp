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

//Spring 2025 Columbia University Local Contest - G

//first, sort the weeks in ascending order by how many meals you're going to eat. 

//observe that you can literally just try all possible m from 0 to 10^6, any m above 10^6 is going to be 
//worse than a m <= 10^6. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, A, b;
    cin >> n >> A >> b;
    vl c(n);
    for(int i = 0; i < n; i++){
        cin >> c[i];
    }
    sort(c.begin(), c.end());
    ll totc = 0;
    for(int i = 0; i < n; i++) totc += c[i];
    ll mincost = 1e18, minm = -1;
    int cptr = 0;
    for(ll m = 0; m <= 1000000; m++){
        ll ccost = A * m + totc * b;
        if(ccost < mincost) {
            mincost = ccost;
            minm = m;
        }
        while(cptr != n && c[cptr] <= m) cptr ++;
        totc -= n - cptr;
    }
    cout << mincost << " " << minm << "\n";
    
    return 0;
}