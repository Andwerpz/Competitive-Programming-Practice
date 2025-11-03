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

//2024 ICPC World Finals - F

//we can binary search for the distance. 
//suppose that we fix the minimum distance to be x, this implies that any two chapters 
//that are closer than distance x are automatically in the same team. 

//so we have a bunch of connected components that have to be in the same team, and we want to choose
//some subset of the components such that the sum of nodes in the chosen components equals n. 
//this is exactly 01 knapsack and we can solve it in O(n^2) time. 

//since n = 500, O(n^2 * 30) is good enough. 

ld epsilon = 1e-9;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vvi p(2 * n, vi(2));
    for(int i = 0; i < 2 * n; i++){
        cin >> p[i][0] >> p[i][1];
    }
    ld low = 0, high = 1e10;
    vi ans; 
    while(high - low > epsilon) {
        ld mid = low + (high - low) / 2.0;
        vvi c(2 * n);
        for(int i = 0; i < 2 * n; i++){
            for(int j = i + 1; j < 2 * n; j++){
                ld d = sqrtl((ld) (p[i][0] - p[j][0]) * (p[i][0] - p[j][0]) + (ld) (p[i][1] - p[j][1]) * (p[i][1] - p[j][1]));
                // cout << "D : " << d << "\n";
                if(d <= mid) {
                    c[i].push_back(j);
                    c[j].push_back(i);
                }
            }
        }
        vi k;
        vvi kid;
        vb v(2 * n, false);
        for(int i = 0; i < 2 * n; i++){
            if(v[i]) continue;
            int cnt = 0;
            vi id;
            v[i] = true;
            queue<int> q;
            q.push(i);
            while(q.size()) {
                int cur = q.front();
                q.pop();
                cnt ++;
                id.push_back(cur);
                for(int x : c[cur]){
                    if(!v[x]) {
                        v[x] = true;
                        q.push(x);
                    }
                }
            }
            k.push_back(cnt);
            kid.push_back(id);
        }
        vb dp(n + 1, false);
        dp[0] = true;
        vector<pii> pv(n + 1, {-1, -1});    //{kind, dpind}
        for(int j = 0; j < k.size(); j++) {
            int x = k[j];
            for(int i = n - x; i >= 0; i--){
                if(dp[i] && !dp[i + x]) {
                    dp[i + x] = true;
                    pv[i + x] = {j, i};
                }
            }
        }
        if(dp[n]) {
            low = mid;
            ans.clear();
            int ptr = n;
            while(ptr != 0){
                int kind = pv[ptr].first;
                assert(kind != -1);
                for(int x : kid[kind]) ans.push_back(x);
                ptr = pv[ptr].second;
            }
        }
        else high = mid;
    }
    assert(ans.size() == n);
    cout << fixed << setprecision(10) << low << "\n";
    for(int i = 0; i < ans.size(); i++) cout << (ans[i] + 1) << "\n";

    return 0;
}