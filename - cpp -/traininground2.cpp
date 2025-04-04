#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//2024 ICPC NAC - M

//first note that there is a naive dp solution like so: dp[i][j][k] = can visit or not where
//i = number of problems considered
//j = thinking skill
//k = implementing skill

//we can actually get rid of i (kinda) and do dp[i][j] = can visit where 
//i = thinking skill, j = implementing skill. 

//note that if a problem requires thinking skill in range [l1, r1] and implementing in [l2, r2], then it corresponds to a 
//rectangle in the dp table. If we solve the problem, then each visitable cell can either travel to i + 1 or j + 1. 

//as it only makes sense to visit each cell once, we can just keep track of the positions of all cells that haven't been
//transitioned on each row, and transition them whenever we see a rectangle cover them. 

//the final answer is the maximum sum of thinking and implementation skill that is visitable. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, imp, thi; cin >> n >> imp >> thi;

    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1));
    vector<set<ll>> newvisit(n + 1);
    newvisit[0].insert(0);

    ll res = 0;

    for(ll i = 0; i < n; i++) {
        ll il, ih, tl, th; cin >> il >> ih >> tl >> th;

        il -= imp;
        ih -= imp;
        tl -= thi;
        th -= thi;

        set<array<ll,2>> newvisits;

        for(ll j = max(0LL, il); j <= min(n, ih); j++) {

            while(newvisit[j].lower_bound(tl) != newvisit[j].end() && (*newvisit[j].lower_bound(tl)) <= th) {
                ll x = *newvisit[j].lower_bound(tl);
                newvisit[j].erase(x);
                newvisits.insert({j,x});
            }

        }
        
        for(auto [newi, newt] : newvisits) {
            if(dp[newi][newt] == 0) {
                dp[newi][newt] = 1;
                newvisit[newi + 1].insert(newt);
                newvisit[newi].insert(newt + 1);
                res = max(res, newi + newt + 1);
            }
        }

    }

    cout << res << '\n';

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     ll n, imp, thi; cin >> n >> imp >> thi;

//     vector<ll> dp(n + 1,-1);
//     dp[0] = 0;

//     for(ll i = 0; i < n; i++) {
//         ll il, ih, tl, th; cin >> il >> ih >> tl >> th;
//         il -= imp, ih -= imp, tl -= thi, th -= thi;
//         for(ll j = n; j >= 0; j--) {

//             ll best = dp[j];
//             if(dp[j] != -1 && j >= il && j <= ih && dp[j] >= tl && dp[j] <= th) {
//                 best = max(best, dp[j] + 1);
//             }
//             if(j && (j - 1) >= il && (j - 1) <= ih && dp[j-1] != -1 && dp[j-1] >= tl && dp[j-1] <= th) {
//                 best = max(best, dp[j-1]);
//             } else if(j && dp[j-1] != -1 && (j - 1) >= il && (j - 1) <= ih && dp[j-1] >= tl) {
//                 best = max(best, th);
//             }
//             dp[j] = best;

//         }
//     }

//     ll ans = 0;
//     for(ll i = 0; i <= n; i++) {
//         if(dp[i] != -1) {
//             ans = max(ans, i + dp[i]);
//         }
//     }

//     cout << ans << '\n';

//     return 0;
// }