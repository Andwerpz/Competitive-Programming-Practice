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

//NAIPC 2014 - F

//given some fixed path from the bandit camp to the king's castle, how can we determine the maximum amount of gold we can
//steal on the path, and still make it back to the bandit camp? We can actually model it as a shortest paths problem. 
//Assume at first we steal gold from everybody on the path. Then, when going back, if we want to go through a village that
//we stole gold from, we need to 'pay them back'. Then, we just need to find the shortest path from the castle back
//to the bandit camp where we need to pay the least amount of gold back. 

//We can actually enumerate all paths. The maximum amount of shortest paths possible is around 3^11, which is around 
//2*10^5. Since for each path we need to run an O((n + m) * log(n)) dijkstra, this might be kinda tight, however notice that 
//as the number of paths possible grows, the amount of edges will shrink, so this should pass with plenty of wiggle room. 

int n;
vvi c;
vi a, d;
int solve(int cur, vb& onp, int gold) {
    if(cur == 1){
        //given path, see what is minimum amount of gold loss
        //i is incoming node, i + n is aux node
        vi dist(2 * n, 1e9);
        priority_queue<pii> q;  //{-dist, ind}
        q.push({0, 1});
        dist[1] = 0;
        while(q.size() != 0){
            int cur = q.top().second;
            int cdist = -q.top().first;
            q.pop();
            if(cdist != dist[cur]) continue;
            if(cur >= n){
                //aux node
                for(int x : c[cur - n]) {
                    if(dist[cur] < dist[x]) dist[x] = dist[cur], q.push({-dist[x], x});
                }
            }
            else {
                //normal node
                int x = cur + n;
                int nd = dist[cur] + (onp[cur]? a[cur] : 0);
                if(nd < dist[x]) dist[x] = nd, q.push({-dist[x], x});
            }
        }
        return gold - dist[0];
    }
    //choose next element in path
    int ans = 0;
    for(int x : c[cur]) {
        if(d[x] == d[cur] - 1) {
            onp[x] = true;
            ans = max(ans, solve(x, onp, gold + a[x]));
            onp[x] = false;
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int m;
    cin >> n >> m;
    c = vvi(n);
    a = vi(n, 0);
    for(int i = 0; i < n - 2; i++){
        cin >> a[i + 2];
    }
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u --, v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    d = vi(n, 1e9);
    d[1] = 0;
    queue<int> q;
    q.push(1);
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        for(int x : c[cur]) if(d[x] > d[cur] + 1) d[x] = d[cur] + 1, q.push(x);
    }
    vi path(0);
    vb onp(n, false);
    cout << solve(0, onp, 0) << "\n";
    
    return 0;
}