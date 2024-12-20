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

//2024-2025 ICPC NERC - M

//first use greedy algorithm to fix which pairs are supposed to have matching processes, then
//use swaps to actually make them have matching processes. 

//to construct the pairs, we can greedily pick off leaves of the tree, and connect the leaf and it's 
//parent into a pair until we can't anymore. I have no idea why this results in the maximum amount
//of pairs. Proof by intuition ig.

//To construct the swaps, note that the constructed pairs kinda induce a graph, connecting 
//different processes (not machines) together. Since there are exactly 2 copies of each process within
//the tree, the induced graph on processes will be a collection of cycles and chains. 

//We can solve cycles pretty easily. Consider the cycle:
//(1, 2), (2, 3), (3, 4), (4, 1)
//where we label each node by it's process it's currently running. 
//we can do swaps like so:
//(1, 1), (2, 3), (3, 4), (4, 2)
//(1, 1), (4, 3), (3, 4), (2, 2)
//(1, 1), (4, 4), (3, 3), (2, 2)
//to fix all the pairs. In general, for any length cycle this pattern of swaps will hold. 

//to solve chains, we just need to swap the first element in the chain out to make it into a cycle.
//This is always possible because the replicant process of the last process in the chain will never
//be contained within any other chain or cycle. 

vector<vector<pair<int, pii>>> construct_pairs(vi& a, vvi& c) {
    int n = c.size();
    queue<int> q;
    vi v(n, false);
    vi deg(n, 0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < c[i].size(); j++){
            deg[c[i][j]] ++;
        }
    }
    for(int i = 0; i < n; i++){
        if(deg[i] == 1) {
            q.push(i);
        }
    }
    vector<vector<pair<int, pii>>> cp(n / 2);
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        if(v[cur]) continue;
        int other = -1;
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i];
            if(v[next]) continue;
            other = next;
            break;
        }
        if(other != -1) {
            v[cur] = true;
            v[other] = true;
            int u = a[cur];
            int v = a[other];
            cp[u].push_back({v, {cur, other}});
            cp[v].push_back({u, {other, cur}});
            deg[other] = 0;
            for(int i = 0; i < c[other].size(); i++){
                int next = c[other][i];
                deg[next] --;
                if(deg[next] == 1) q.push(next);
            }
        }
    }
    return cp;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(2 * n);
        vector<pii> b(n, {-1, -1});  //tells us which machines are running each process
        for(int i = 0; i < 2 * n; i++){
            cin >> a[i];
            a[i] --;
            if(b[a[i]].first == -1) b[a[i]].first = i;
            else b[a[i]].second = i;
        }
        vvi c(2 * n);
        for(int i = 0; i < 2 * n - 1; i++){
            int u, v;
            cin >> u >> v;
            u --, v--;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        vector<vector<pair<int, pii>>> cp = construct_pairs(a, c);
        // for(int i = 0; i < cp.size(); i++){
        //     cout << "OUT EDGES : " << i << "\n";
        //     for(int j = 0; j < cp[i].size(); j++){
        //         cout << "EDGE : " << cp[i][j].first << " " << cp[i][j].second.first << " " << cp[i][j].second.second << "\n";
        //     }
        // }
        vector<pii> ans;
        vb v(n, false);
        for(int i = 0; i < n; i++){
            if(v[i]) continue;
            //find connected component to i
            v[i] = true;
            queue<int> q;
            q.push(i);
            vi g;
            while(q.size() != 0){
                int cur = q.front();
                q.pop();
                g.push_back(cur);
                for(int j = 0; j < cp[cur].size(); j++){
                    int next = cp[cur][j].first;
                    if(v[next]) continue;
                    v[next] = true;
                    q.push(next);
                }
            }
            // cout << "G : \n";
            // for(int j = 0; j < g.size(); j++){
            //     cout << g[j] << " ";
            // }
            // cout << "\n";
            if(g.size() == 1) continue; //not connected to anything else
            //see if we should start at specific node (if it's a chain not a cycle)
            int ptr = g[0];
            bool is_chain = false;
            for(int j = 0; j < g.size(); j++){
                if(cp[g[j]].size() == 1){
                    ptr = g[j];
                    is_chain = true;
                    break;
                }
            }
            // cout << "START : " << ptr << "\n";
            //create ordering
            for(int j = 0; j < g.size(); j++) v[g[j]] = false;
            vi m;
            v[ptr] = true;
            while(true) {
                bool done = true;
                for(int j = 0; j < cp[ptr].size(); j++){
                    int next = cp[ptr][j].first;
                    if(!v[next]) {
                        v[next] = true;
                        done = false;
                        m.push_back(cp[ptr][j].second.first);
                        m.push_back(cp[ptr][j].second.second);
                        ptr = next;
                        break;
                    }
                }
                if(done) break;
            }
            if(!is_chain) {
                // cout << "CONNECT LAST TO FIRST : " << ptr << " " << g[0] << "\n";
                int first = g[0];
                int last = ptr;
                if(cp[last][0].first == first && cp[last][0].second.first != m[0] && cp[last][0].second.second != m[0]) {
                    m.push_back(cp[last][0].second.first);
                    m.push_back(cp[last][0].second.second);
                }
                else {
                    m.push_back(cp[last][1].second.first);
                    m.push_back(cp[last][1].second.second);
                }
            }
            // cout << "M : \n";
            // for(int j = 0; j < m.size(); j++){
            //     cout << m[j] << " ";
            // }
            // cout << "\n";
            //construct swaps
            if(is_chain) {  //make into a cycle
                // cout << "CHAIN CORRECTION\n";
                int last = g[g.size() - 1];
                int lastm = m[m.size() - 1];
                if(lastm != b[last].first) ans.push_back({m[0], b[last].first});
                else ans.push_back({m[0], b[last].second});
            }
            for(int j = 0; j < (m.size() / 2) - 1; j++){
                ans.push_back({m[j + 1], m[m.size() - 1 - j]});
            }
        }
        cout << ans.size() << "\n";
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i].first + 1 << " " << ans[i].second + 1 << "\n";
        }
    }
    
    return 0;
}