#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef pair<int, int> pii;

//2025 ICPC Shenyang Regional - B

//observe that we can treat each different type of color independently. 
//first, count for each color, how many cells of that color we need to have in the final painting. 

//next, consider what the optimal strategy is, given that we can only erase cells. 
//we would want to first create layers for each color, ordered in ascending order by frequency
//from the bottom to top layer
//then we erase holes in each layer so that the less frequent colors can be visible through
//the more visible colors. 

//now consider adding the ability to paint cells. Ideally, we would want to paint the least
//amount of cells possible, so we should always only paint the colors with the least frequency.

//given that the colors are sorted in descending order of frequency, we can just compute for each 
//suffix, what's the cost to paint that suffix, and erase the corresponding prefix. 
//can compute this in O(1) time per suffix. 

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t;
    cin >> t;
    while(t--) {
        ll n, m, a, b;
        cin >> n >> m >> a >> b;
        ll ans = 1e18;
        map<int, int> f;
        ll tsp = 0;
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
            int x;
            cin >> x;
            if(x == 0) tsp ++;
            else f[x] ++;
        }
        vi occ(0);
        for(auto i = f.begin(); i != f.end(); i++) {
            occ.push_back(i->second);
        }
        sort(occ.begin(), occ.end());
        reverse(occ.begin(), occ.end());
        ll left = n * m - tsp;
        ll csum = 0;
        ans = min(ans, left * a);
        for(ll i = 0; i < occ.size(); i++) {
            csum += b * (i * occ[i] + tsp);
            left -= occ[i];
            ans = min(ans, csum + left * a);
        }
        cout << ans << "\n";
    }

    return 0;
}