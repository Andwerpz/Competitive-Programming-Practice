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

//Codeforces - 1340C

//my first time seeing 01 BFS. 

//first, lets sort all the safe spots in ascending order. 
//We can use dp to solve this. dp[i][j] = minimum number of red lights to get to safe spot i, with j time left
//over in the current green light. For transitions, if you're at safe spot i, you can either move to spot i + 1 or
//i - 1 if it exists, and you have enough time to move there. Of course, if you start with 0 time, then you should
//transition to state dp[i][g]. 

//this can actually be turned into a graph traversal. Each dp state is now a node in the graph, and each transition
//is an edge. Note that we want to compute the minimum costs to travel to nodes dp[m - 1][i] for all i, from the
//initial node dp[0][g]. 

//since each node in the graph either has weight 0 or 1 (depending on whether you still have time at your starting node),
//we can actually solve this in linear time using 01 BFS. The problem constraints actually hint towards this, as
//the number of nodes is m * g, or around 10^7, and you're only given 1 second. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vi d(m);
    for(int i = 0; i < m; i++){
        cin >> d[i];
    }
    sort(d.begin(), d.end());
    int g, r;
    cin >> g >> r;
    vvi dp(m, vi(g + 1, 1e9));
    dp[0][g] = 0;
    vvb v(m, vb(g + 1, false));
    vector<stack<pii>> q(1e5);
    int qptr = 0;
    q[0].push({0, g});
    while(true){
        while(qptr != q.size() && q[qptr].size() == 0){
            qptr ++;
        }
        if(qptr == q.size()) {
            break;
        }
        pii qent = q[qptr].top();
        q[qptr].pop();
        int cur = qent.first;
        int remt = qent.second;
        if(v[cur][remt]) {
            continue;
        }
        v[cur][remt] = true;
        ll ncost = dp[cur][remt];
        if(remt == 0){
            remt = g;
            ncost ++;
        }
        //to left
        if(cur != 0){
            int dist = d[cur] - d[cur - 1];
            if(dist <= remt && dp[cur - 1][remt - dist] > ncost) {
                dp[cur - 1][remt - dist] = ncost;
                q[ncost].push({cur - 1, remt - dist});
            }
        }
        //to right
        if(cur != m - 1){
            int dist = d[cur + 1] - d[cur];
            if(dist <= remt && dp[cur + 1][remt - dist] > ncost) {
                dp[cur + 1][remt - dist] = ncost;
                q[ncost].push({cur + 1, remt - dist});
            }
        }
    }
    ll ans = 1e18;
    for(int i = 0; i <= g; i++){
        if(dp[m - 1][i] == 1e9){
            continue;
        }
        ans = min(ans, (ll) (g + r) * dp[m - 1][i] + (g - i));
    }
    cout << (ans == 1e18? -1 : ans) << "\n";

    return 0;
}