#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1929E

//naively, we can perform some dp like dp[i] = minimum number of painted edges required to satisfy the bitset of 
//paths i. Transitions are of course to include some edge. If an edge falls on some bitset of paths j, then our
//transition is dp[i | j] = dp[i] + 1. 

//the trick to solving this problem is to notice that the number of unique values of j is relatively small, I guess
//around k^2. With 10^6 states, and 400 transitions per state, that's fast enough to pass. 

//we also don't have to worry about double counting any edges. Since the dp will give us the optimal answer for any i,
//and we can trivially reduce a double counted answer to a better answer with no double counting, the answer that we
//extract will not have any edges painted twice. 

vector<int> get_path(int n, vector<vector<int>>& c, int start, int end) {
    vector<int> prev(n, -1);
    queue<int> q;
    q.push(start);
    prev[start] = -2;
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i];
            if(prev[next] == -1){
                prev[next] = cur;
                q.push(next);
            }
        }
    }
    vector<int> path(0);
    int ptr = end;
    while(ptr != -2){
        path.push_back(ptr);
        ptr = prev[ptr];
    }
    return path;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<vector<int>> c(n);
        map<pair<int, int>, int> m;
        for(int i = 0; i < n - 1; i++){
            int u, v;
            cin >> u >> v;
            u --;
            v --;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        int k;
        cin >> k;
        for(int i = 0; i < k; i++){
            int a, b;
            cin >> a >> b;
            a --;
            b --;
            vector<int> path = get_path(n, c, a, b);
            for(int j = 1; j < path.size(); j++){
                int u = path[j - 1];
                int v = path[j];
                m[{u, v}] += (1 << i);
                m[{v, u}] += (1 << i);
            }
        }
        set<int> s;
        for(auto i = m.begin(); i != m.end(); i++){
            s.insert(i -> second);
        }
        vector<int> dp((1 << k), 1e9);
        dp[0] = 0;
        for(auto i = s.begin(); i != s.end(); i++){
            int cur = *i;
            for(int j = 0; j < dp.size(); j++){
                dp[j | cur] = min(dp[j | cur], dp[j] + 1);
            }
        }
        cout << dp[(1 << k) - 1] << "\n";
    }
    
    return 0;
}