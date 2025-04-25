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

//Rutgers University Programming Contest Spring 2025 - A

//note that there are 2^{n - 1} numbers that have an even amount of bits and 2^{n - 1} numbers that have an odd
//amount of bits. It's actually optimal to take either all the even or odd bit numbers. 

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

bool find(int j, vector<vi>& g, vi& btoa, vi& vis) {
    if (btoa[j] == -1) return 1;
    vis[j] = 1; int di = btoa[j];
    for (int e : g[di])
    if (!vis[e] && find(e, g, btoa, vis)) {
    btoa[e] = di;
    return 1;
    }
    return 0;
}

int dfsMatching(vector<vi>& g, vi& btoa) {
    vi vis;
    rep(i,0,sz(g)) {
    vis.assign(sz(btoa), 0);
    for (int j : g[i])
    if (find(j, g, btoa, vis)) {
    btoa[j] = i;
    break;
    }
    }
    return sz(btoa) - (int)count(all(btoa), -1);
}

vi cover(vector<vi>& g, int n, int m) {
    vi match(m, -1);
    int res = dfsMatching(g, match);
    vector<bool> lfound(n, true), seen(m);
    for (int it : match) if (it != -1) lfound[it] = false;
    vi q, cover;
    rep(i,0,n) if (lfound[i]) q.push_back(i);
    while (!q.empty()) {
    int i = q.back(); q.pop_back();
    lfound[i] = 1;
    for (int e : g[i]) if (!seen[e] && match[e] != -1) {
    seen[e] = true;
    q.push_back(match[e]);
    }
    }
    rep(i,0,n) if (!lfound[i]) cover.push_back(i);
    rep(i,0,m) if (seen[i]) cover.push_back(n+i);
    assert(sz(cover) == res);
    return cover;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    // int eid = 0, oid = 0;
    // vb iso(n);
    cout << (1 << (n - 1)) << "\n";
    vi id((1 << n));
    for(int i = 0; i < (1 << n); i++){
        int cnt = 0;
        for(int j = 0; j < n; j++) cnt += (i & (1 << j)) != 0;
        // iso[i] = cnt % 2;
        // if(cnt % 2) id[i] = oid ++;
        // else id[i] = eid ++;
        if(cnt % 2 == 0){
            for(int j = 0; j < n; j++) cout << ((i & (1 << j))? 1 : 0);
            cout << "\n";
        }
    }
    // cout << "EID, OID : " << eid << " " << oid << "\n";
    // vvi c(eid);
    // for(int i = 0; i < n; i++){
    //     if(iso[i]) continue;
    //     for(int j = 0; j < n; j++) {
    //         int next = i ^ (1 << j);
    //         c[id[i]].push_back(id[next]);
    //     }
    // }
    // for(int i = 0; i < eid; i++) {
    //     cout << "I : " << i << ", ";
    //     for(int j = 0; j < c[i].size(); j++) cout << c[i][j] << " ";
    //     cout << "\n";
    // }
    // vi cv = cover(c, eid, oid);
    // for(int i = 0; i < n; i++){
    //     cout << cv[i] << "\n";
    // }
    
    return 0;
}