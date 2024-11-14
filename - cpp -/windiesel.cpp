#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
// typedef pair<ll, ll> pii;
// typedef pair<ll, ll> pll;
// typedef vector<ll> vi;
// typedef vector<ll> vl;
// typedef vector<bool> vb;
// typedef vector<ld> vd;
// typedef vector<vector<ll>> vvi;
// typedef vector<vector<ll>> vvl;
// typedef vector<vector<bool>> vvb;
// typedef vector<vector<ld>> vvd;
// typedef __ll128 lll;
// typedef __float128 lld;

//CTU Open 2021 - L

ll lifts[20][200000];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, m; cin >> n >> m;
    vector<vector<ll>> adj(n);
    for(ll i = 0; i < m; i++) {
        ll a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<ll> depths(n,-1);
    vector<vector<ll>> atdepth(n);
    vector<ll> vis(n);

    queue<array<ll,2>> q;
    q.push({0,0});
    while(q.size()) {
        auto [i, d] = q.front();
        q.pop();
        if(vis[i]) continue;
        vis[i] = 1;
        depths[i] = d;
        atdepth[d].push_back(i);
        for(ll c : adj[i]) {
            q.push({c,d+1});
        }
    }

    vector<ll> parents(n);

    for(ll i = 0; i < n; i++) {
        ll bestprev = INT_MAX;
        for(ll c : adj[i]) {
            if(depths[c] == depths[i] - 1) {
                bestprev = min(bestprev, c);
            }
        }

        parents[i] = bestprev;

    }

    // cout << "depths\n";
    // for(ll x : depths) cout << x << " ";
    // cout << '\n';

    vector<ll> drill_order;

    for(ll depth = 1; depth < n; depth++) {
        sort(atdepth[depth].begin(), atdepth[depth].end());
        for(ll idx : atdepth[depth]) {
            drill_order.push_back(idx);
        }
    }

    parents[0] = 0;

    // cout << "parents\n";
    // for(ll x : parents) cout << x << " ";
    // cout << '\n';

    for(ll i = 0; i < n; i++) {
        lifts[0][i] = parents[i];
    }

    for(ll i = 1; i < 20; i++) {
        for(ll j = 0; j < n; j++) {
            lifts[i][j] = lifts[i-1][lifts[i-1][j]];
        }
    }

    auto goupk = [&](ll a, ll k) -> ll {
        for(ll i = 0; i < 20; i++) {
            if((k >> i) & 1) {
                a = lifts[i][a];
            }
        }
        return a;
    };

    // cout << "drill order\n";
    // for(ll x : drill_order) cout << x << " ";
    // cout << '\n';

    auto getdist = [&](ll i, ll j) {
        if(depths[i] > depths[j]) {
            swap(i,j);
        }
        ll res = depths[j] - depths[i];
        j = goupk(j, res);

        for(ll k = 19; k >= 0; k--) {
            if(goupk(i,1 << k) != goupk(j, 1 << k)) {
                res += 1 << (k + 1);
                i = goupk(i,1 << k);
                j = goupk(j, 1 << k);
            }
        }

        if(i != j) {
            res += 2;
        }
        return res;
    };

    ll res = 0;
    ll cur = 0;

    for(ll x : drill_order) {
        res += getdist(x,cur);
        cur = x;
    }

    cout << res << '\n';
    
    return 0;
}