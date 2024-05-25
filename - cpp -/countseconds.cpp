#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1704E

//we can first do n iterations. If there still are non-zero nodes left in the graph after n iterations, then
//the node with no out edges is guaranteed to be non-zero as well. Let's denote this node with no out edges as
//the 'sink'. 

//In fact, it's also now true that any node that is currently a zero node will not become a non-zero node, and that
//the sink will be the last non-zero node. 

//so now, we just have to compute for each node that is remaining, how much value it gives to the sink. This can
//be done using dp and topological sort. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll mod = 998244353;
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<vector<int>> c(n, vector<int>(0));
        vector<ll> indeg(n, 0);
        for(int i = 0; i < m; i++){
            int x, y;
            cin >> x >> y;
            x --;
            y --;
            c[x].push_back(y);
            indeg[y] ++;
        }
        bool done = false;
        ll ans = -1;
        //n single iterations
        for(int i = 0; i < n; i++){
            done = true;
            vector<bool> subt(n, false);
            for(int j = 0; j < n; j++){
                if(a[j] != 0){
                    done = false;
                    subt[j] = true;
                }
            }
            if(done) {
                ans = i;
                break;
            }
            for(int j = 0; j < n; j++){
                if(subt[j]) {
                    a[j] --;
                    for(int k = 0; k < c[j].size(); k++){
                        a[c[j][k]] ++;
                    }
                }
            }
        }
        if(done) {
            cout << ans << "\n";
            continue;
        }
        ans = n;
        //otherwise, do toposort and stuff
        queue<int> q;
        for(int i = 0; i < n; i++){
            if(indeg[i] == 0){
                q.push(i);
            }
        }
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            if(c[cur].size() == 0){
                ans = (ans + a[cur]) % mod;
                break;
            }
            for(int i = 0; i < c[cur].size(); i++){
                int next = c[cur][i];
                a[next] = (a[next] + a[cur]) % mod;
                indeg[next] --;
                if(indeg[next] == 0){
                    q.push(next);
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}