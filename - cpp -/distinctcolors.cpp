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

//CSES - 1139

//small to large set merging. Should run in O(n * log(n)^2) time. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vvi c(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    vi ans(n);
    function<set<int>(int, int)> dfs = [&](int cur, int p) -> set<int> {
        set<int> s;
        s.insert(a[cur]);
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i];
            if(next == p){
                continue;
            }
            set<int> ns = dfs(next, cur);
            if(s.size() < ns.size()){
                swap(ns, s);
            }
            for(int x : ns) {
                s.insert(x);
            }
        }
        ans[cur] = s.size();
        return s;
    };
    dfs(0, -1);
    for(int i = 0; i < n; i++){
        cout << ans[i] << " \n"[i == n - 1];
    }
    
    return 0;
}