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

//2014 NAIPC - I

//observe that after you flip a switch, you must go and collect all coins related to that switch. So for each
//switch, first precompute the minimum distance to go flip the switch, then end at some coin. 

//then, we can do bitmask dp over all the switches. 

struct vec3 {
    ld x, y, z;
};

ld dist(vec3& a, vec3& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vec3 m;
    cin >> m.x >> m.y >> m.z;
    vector<vector<vec3>> c(n);
    vector<vec3> s(n);
    for(int i = 0; i < n; i++){
        int k;
        cin >> k;
        cin >> s[i].x >> s[i].y >> s[i].z;
        for(int j = 0; j < k; j++){
            vec3 p;
            cin >> p.x >> p.y >> p.z;
            c[i].push_back(p);
        }
    }
    //for each switch, precompute the minimum distances to end at each coin
    vvd stc(n);
    for(int i = 0; i < n; i++){
        int k = c[i].size();
        vvd dp((1 << k), vd(k, 1e9));
        //base case, start at every coin
        for(int j = 0; j < k; j++){
            dp[(1 << j)][j] = dist(s[i], c[i][j]);
        }
        //do dp
        for(int bits = 1; bits < (1 << k); bits++){
            for(int cur = 0; cur < k; cur++){
                if(!(bits & (1 << cur))) continue;
                for(int next = 0; next < k; next++){
                    if(bits & (1 << next)) continue;
                    dp[bits ^ (1 << next)][next] = min(dp[bits ^ (1 << next)][next], dp[bits][cur] + dist(c[i][cur], c[i][next]));
                }
            }
        }
        stc[i] = dp[(1 << k) - 1];
    }
    //do dp across all switches
    vvd dp((1 << n), vd(n, 1e9));
    //base case, start at all switches
    for(int i = 0; i < n; i++){
        dp[(1 << i)][i] = dist(m, s[i]);
    }
    //do dp
    for(int bits = 1; bits < (1 << n); bits++){
        for(int curs = 0; curs < n; curs++){
            if(!(bits & (1 << curs))) continue;
            int k = c[curs].size();
            for(int curc = 0; curc < k; curc++){
                for(int nexts = 0; nexts < n; nexts++){
                    if(bits & (1 << nexts)) continue;
                    dp[bits ^ (1 << nexts)][nexts] = min(dp[bits ^ (1 << nexts)][nexts], dp[bits][curs] + stc[curs][curc] + dist(c[curs][curc], s[nexts]));
                }
            }
        }
    }
    ld ans = 1e18;
    for(int i = 0; i < n; i++){
        int k = c[i].size();
        for(int j = 0; j < k; j++){
            ans = min(ans, dp[(1 << n) - 1][i] + stc[i][j]);
        }
    }
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}