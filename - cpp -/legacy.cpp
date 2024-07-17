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
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 787D

//apparently my dijkstra implementation is just bad D:

//after reading this problem, probably the most obvious technique to apply is auxillary nodes. 
//we want some way of having a node represent a range, and that brings to mind segment trees. 
//actually, the idea of having nodes represent segments like a segment tree is perfect for this problem. 

//we'll have to have 2 segment trees of nodes, one representing going into a range, and one representing going 
//out of a range. Each plan can be represented by at most log(n) nodes. Once we are done building the graph, we can
//just run dijkstra on it. 

//note that the time and mem limits are rather tight on this problem, so you'll probably have to use an optimized 
//segment tree building technique to AC. 

const int N = 1e5 + 100;
vector<pii> c[N * 3];

void _dijkstra(int n, int start, vector<ll>& dist) {
    vb v(n, false);
    dist = vl(n, 1e18);
    priority_queue<pair<ll, int>> q;
    q.push({0, start});
    dist[start] = 0;
    while(q.size() != 0){
        int cur = q.top().second;
        q.pop();
        if(v[cur]) {
            continue;
        }
        v[cur] = true;
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i].first;
            if(dist[next] > dist[cur] + c[cur][i].second) {
                dist[next] = dist[cur] + c[cur][i].second;
                q.push({-dist[next], next});    
            }
        }
    }
}

int n, q, s;
vi outm, inm;

void gen_in(int l, int r, ll cost, int id) {
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l % 2 == 1) {
            c[id].push_back({inm[l], cost});
            l++;
        }
        if (r % 2 == 1) {
            r--;
            c[id].push_back({inm[r], cost});
        }
    }
}

void gen_out(int l, int r, ll cost, int id) {
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l % 2 == 1) {
            c[outm[l]].push_back({id, cost});
            l++;
        }
        if (r % 2 == 1) {
            r--;
            c[outm[r]].push_back({id, cost});
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> n >> q >> s;
    s--;
    inm = vi(n * 2), outm = vi(n * 2);
    for(int i = 0; i < n; i++){
        inm[i + n] = i;
        outm[i + n] = i;
    }
    {
        int ptr = n;
        for(int i = 0; i < n; i++){
            inm[i] = ptr ++;
            outm[i] = ptr ++;
        }
        for(int i = n - 1; i > 0; i--){
            c[inm[i]].push_back({inm[i * 2], 0});
            c[inm[i]].push_back({inm[i * 2 + 1], 0});
            c[outm[i * 2]].push_back({outm[i], 0});
            c[outm[i * 2 + 1]].push_back({outm[i], 0});
        }
    }
    for(int i = 0; i < q; i++){
        int t;
        cin >> t;
        if(t == 1){
            ll v, u, w;
            cin >> v >> u >> w;
            v --;
            u --;
            c[v].push_back({u, w});
        }
        else if(t == 2){
            ll v, l, r, w;
            cin >> v >> l >> r >> w;
            v --;
            l --;
            gen_in(l, r, w, v);
        }
        else {
            ll v, l, r, w;
            cin >> v >> l >> r >> w;
            v --;
            l --;
            gen_out(l, r, w, v);
        }
    }
    vl dist;
    _dijkstra(n * 3, s, dist);
    for(int i = 0; i < n; i++){
        cout << (dist[i] == 1e18? -1 : dist[i]) << " ";
    }
    cout << "\n";
    
    return 0;
}