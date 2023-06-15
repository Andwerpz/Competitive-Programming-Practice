#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSES - 1681

//topological sort + basic dp. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<int> in(n, 0);
    vector<vector<int>> c(n, vector<int>(0));
    ll mod = 1e9 + 7;
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        c[a].push_back(b);
        in[b] ++;
    }
    vector<ll> ans(n, 0);
    ans[0] = 1;
    stack<int> s;
    for(int i = 0; i < n; i++){
        if(!in[i]) {
            s.push(i);
        }
    }
    while(s.size()) {
        int cur = s.top();
        s.pop();
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i];
            in[next] --;
            ans[next] += ans[cur];
            ans[next] %= mod;
            if(!in[next]) {
                s.push(next);
            }
        }
    }
    cout << ans[n - 1] << "\n";
    
    return 0;
}
