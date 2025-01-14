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

//Codeforces - 1918F

//TLDR : just use a modified dfs traversal, greedily go towards subtrees with lowest maximum depth.
// then when exiting each subtree, you can record a potential use of the trampoline, and you take the top
// k + 1 of them. 

//hmm, seems like proving my solution is optimal is actually pretty involved, so i'll just leave it 
//at that. Go look at editorial if interested. 

int calc_mxd(int cur, int cd, vvi& c, vi& mxd) {
    mxd[cur] = cd;
    for(int next : c[cur]) {
        mxd[cur] = max(calc_mxd(next, cd + 1, c, mxd), mxd[cur]);
    }
    return mxd[cur];
}

void dfs(int cur, int cd, vvi& c, vi& mxd, vi& t) {
    vector<pii> a;
    for(int x : c[cur]) a.push_back({mxd[x], x});
    sort(a.begin(), a.end());
    for(int i = 0; i < (int) a.size() - 1; i++) {
        t.push_back(a[i].first - cd * 2);
    }
    if(cur == 0 && a.size() != 0) t.push_back(a[a.size() - 1].first - cd * 2);
    for(int x : c[cur]) dfs(x, cd + 1, c, mxd, t);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vvi c(n);
    for(int i = 1; i < n; i++){
        int p;
        cin >> p;
        p --;
        c[p].push_back(i);
    }
    vi mxd(n, -1);
    calc_mxd(0, 0, c, mxd);
    int ans = 2 * n - 2;
    vi t;
    dfs(0, 0, c, mxd, t);
    sort(t.begin(), t.end());
    reverse(t.begin(), t.end());
    for(int i = 0; i < min((int) t.size(), k + 1); i++){
        if(t[i] < 0) break;
        ans -= t[i];
    }
    cout << ans << "\n";
    
    return 0;
}