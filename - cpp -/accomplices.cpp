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

//Mines HSPC 2025 Open Division - A

//the problem pretty much asks you to solve maximum independent set using meet in the middle. 

//you can do this using SOS dp. 

vl calc_half(vi& h, vvb& c) {
    //isv[bits] = true if bits represents an independent set
    vl isv((1 << h.size()), 1);
    for(int i = 0; i < h.size(); i++){
        for(int j = i + 1; j < h.size(); j++){
            int u = h[i], v = h[j];
            if(c[u][v]) isv[(1 << i) ^ (1 << j)] = false;
        }
    }
    for(int i = 0; i < h.size(); i++){
        for(int j = 0; j < (1 << h.size()); j++){
            if(j & (1 << i)) {
                isv[j] = isv[j] && isv[j ^ (1 << i)];
            }
        }
    }
    return isv;
    // //res[bits] = is this an independent set or not
    // vl res((1 << h.size()), -1e18);
    // for(int i = 0; i < res.size(); i++){
    //     if(!isv[i]) continue;
    //     res[i] = 0;
    //     for(int j = 0; j < h.size(); j++){
    //         if(i & (1 << j)) res[i] += 1;
    //     }
    // }
    // return res;
}

void solve_slow(int n, vvb c) {
    vi ans(n + 1, 0);
    for(int i = 0; i < (1 << n); i++){
        vi a(0);
        bool is_valid = true;
        for(int j = 0; j < n; j++) if(i & (1 << j)) a.push_back(j);
        for(int j = 0; j < a.size(); j++) for(int k = j + 1; k < a.size(); k++) {
            if(c[a[j]][a[k]]) is_valid = false;
        }
        if(is_valid) {
            ans[a.size()] ++;
        }
    }
    for(int i = 0; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int bruh = -1;
    int n, m;
    cin >> n >> m;
    vvb c(n, vb(n, false));
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u --, v --;
        c[u][v] = true;
        c[v][u] = true;
    }
    vi l, r;
    for(int i = 0; i < n; i++){
        if(l.size() <= r.size()) l.push_back(i);
        else r.push_back(i);
    }
    // cout << "L : " << "\n";
    // for(int i = 0; i < l.size(); i++) cout << l[i] << "\n";
    vl bl = calc_half(l, c), br = calc_half(r, c);
    // cout << "DONE CALC : " << endl;
    vvl sr((1 << r.size()), vl(r.size() + 1, 0));
    for(int i = 0; i < (1 << r.size()); i++){
        if(!br[i]) continue;
        int cnt = 0;
        for(int j = 0; j < r.size(); j++) if(i & (1 << j)) cnt += 1;
        sr[i][cnt] = 1;
    }
    //now, br[bits][i] = number of indepedent sets of size i that are subset of bits
    for(int i = 0; i < r.size(); i++){
        for(int j = 0; j < (1 << r.size()); j++){
            if(j & (1 << i)) {
                for(int k = 0; k <= r.size(); k++){
                    sr[j][k] += sr[j ^ (1 << i)][k];
                }
                // br[j] = max(br[j], br[j ^ (1 << i)]);
            }
        }
    }
    //lmask[i] = what nodes in r is node i in l connected to?
    vi lmask(l.size(), 0);
    for(int i = 0; i < l.size(); i++){
        int mask = (1 << r.size()) - 1;
        for(int j = 0; j < r.size(); j++){
            int u = l[i], v = r[j];
            if(c[u][v]) mask ^= (1 << j);
        }
        lmask[i] = mask;
        // cout << "LMASK : " << lmask[i] << "\n";
    }
    vl ans = vl(n + 1, 0);
    for(int i = 0; i < bl.size(); i++){
        if(!bl[i]) continue;
        int mask = (1 << r.size()) - 1;
        int cnt = 0;
        for(int j = 0; j < l.size(); j++){
            if(i & (1 << j)) mask = mask & lmask[j], cnt ++;
        }
        // cout << "LBITS : " << i << "\n" << mask << "\n";
        for(int j = 0; j <= r.size(); j++){
            ans[cnt + j] += sr[mask][j];
        }
    }
    for(int i = 0; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";

    // solve_slow(n, c);
    
    return 0;
}