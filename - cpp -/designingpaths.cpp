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

//Meta Hacker Cup 2025 Round 1 - C

//can build some auxillary nodes to represent this, then do dijkstra

//on each tram line, build a segment tree structure of nodes. This way, we can represent the range of nodes
//that each node can reach via tram by just adding log(k) edges. 
//constructing the segment tree takes O(l) nodes and edges. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ifstream in("designing_paths_input.txt");
    streambuf *cinbuf = cin.rdbuf(); //save old buf
    cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    ofstream out("--out--.txt");
    streambuf *coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    
    int t;
    cin >> t;
    int casi = 0;
    while(t--) {
        casi ++;
        int n, k, m;
        cin >> n >> k >> m;
        int N = n;
        vi l(m);
        vvi a(m);
        for(int i = 0; i < m; i++) {
            cin >> l[i];
            a[i] = vi(l[i] * 2, -1);
            for(int j = 0; j < l[i]; j++) {
                int x;
                cin >> x; 
                x --;
                a[i][j + l[i]] = x;
            }
            for(int j = l[i] - 1; j > 0; j--) {
                a[i][j] = n ++;
            }
        }
        // cout << "DONE READING" << endl;
        vector<vector<pii>> c(n);
        for(int i = 0; i < m; i++) {
            for(int j = l[i] - 1; j > 0; j--) {
                int u = a[i][j];
                int v1 = a[i][j * 2], v2 = a[i][j * 2 + 1];
                c[u].push_back({v1, 0});
                c[u].push_back({v2, 0});
            }
            for(int j = 0; j < l[i]; j++) {
                int cur = a[i][j + l[i]];
                int le = j + 1, ri = min(j + 1 + k, l[i]);
                // cout << "LE RI : " << le << " " <<
                for(le += l[i], ri += l[i]; le < ri; le /= 2, ri /= 2) {
                    // cout << "LE RI : " << le << " " << ri << endl;
                    if(le % 2 == 1) {
                        // cout << "SEGT EDGE : " << cur << " " << a[i][le] << "\n";
                        c[cur].push_back({a[i][le], 1});
                        le ++;
                    }
                    if(ri % 2 == 1) {
                        ri --;
                        // cout << "SEGT EDGE : " << cur << " " << a[i][ri] << "\n";
                        c[cur].push_back({a[i][ri], 1});
                    }
                }
            }
        }
        // cout << "DONE BUILDING" << endl;
        vi d(n, 1e9);
        priority_queue<pii> q;  //{-dist, ind}
        q.push({0, 0});
        d[0] = 0;
        while(q.size() != 0) {
            int cur = q.top().second;
            int cdist = -q.top().first;
            q.pop();
            if(d[cur] != cdist) {
                continue;
            }
            for(pii x : c[cur]) {
                int next = x.first;
                int ndist = cdist + x.second;
                if(ndist < d[next]) {
                    d[next] = ndist;
                    q.push({-ndist, next});
                }
            }
        }
        // cout << "D : \n";
        // for(int i = 0; i < n; i++) cout << i << " : " << d[i] << "\n";
        ll ans = 0;
        for(int i = 0; i < N; i++) {
            ll val = d[i];
            if(d[i] == 1e9) val = -1;
            ans += val * (i + 1);
        }
        cout << "Case #" << casi << ": " << ans << "\n";
    }
    
    return 0;
}