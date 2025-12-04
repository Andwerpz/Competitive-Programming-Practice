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

//Codeforces - 2152B

//for this problem, it might be useful to visualize the cells that D can reach as a function of time. It looks like 
//a big square that grows by 1 cell each second. K's boundary looks like a diamond. So the first observation is that
//K always wants to travel away from D.

//the second observation is that once K gets to an edge, then they have no better moves than to just travel along the
//edge and wait for D to catch them. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        ll rk, ck, rd, cd;
        cin >> rk >> ck >> rd >> cd;
        //transform such that rd <= rk, cd <= ck
        if(rd > rk) {
            rk = n - rk;
            rd = n - rd;
        }
        if(cd > ck) {
            ck = n - ck;
            cd = n - cd;
        }
        ll ans = 0;
        {
            //down
            if(rk == rd) ans = max(ans, abs(ck - cd));
            else {
                ans = max(ans, (n - rk) + abs(rk - rd));
            }
        }

        {
            //right
            if(ck == cd) ans = max(ans, abs(rk - rd));
            else ans = max(ans, (n - ck) + abs(ck - cd));
        }
        cout << ans << "\n";
    }
    
    return 0;
}