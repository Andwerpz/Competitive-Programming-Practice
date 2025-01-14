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

//Codeforces - 1767E

//boils down to solving maximum independent weighted set with meet in the middle. 

//instead of trying to pick which colors to activate, let's instead try to pick the most colors
//that we can leave unactivated. If we can maximize this, then just subtract from sum of costs to 
//find the answer. 

//What colors can we leave deactivated? There are a few criteria:
// - color cannot be first or last
// - color cannot appear twice in a row
//note that any union of deactivated colors must also follow these two rules. So the problem is now
//how can we pick colors to deactivate such that no two deactivated tiles are adjacent?

//consider the graph of m nodes where nodes i and j are adjacent if there exists two tiles of colors i 
//and j that are adjacent. If we can just find the maximum independent weighted set on this graph, 
//then that just solves our problem. The only issue is that MIS is NP. 

//no big deal, we can use meet in the middle to solve MIS in O(2^(m / 2) * m) complexity. 
//subdivide the nodes into two sets, and for each set compute for every subset whether or not it's
//independent, and if it is, it's weight sum (this can be sped up using SOS dp). 

//then, for one set, use SOS dp to compute an array b[mask] = maximum weight sum of an independent
//sum that is subset of mask. Then to combine the two, just have to go through all entries in the other
//set and access the corresponding element in b. 

vl calc_half(vi& h, vvb& c, vl& w) {
    //isv[bits] = true if bits represents an independent set
    vb isv((1 << h.size()), true);
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
    //res[bits] = sum of nodes given that nodes form independent set
    vl res((1 << h.size()), -1e18);
    for(int i = 0; i < res.size(); i++){
        if(!isv[i]) continue;
        res[i] = 0;
        for(int j = 0; j < h.size(); j++){
            if(i & (1 << j)) res[i] += w[h[j]];
        }
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vi a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        a[i] --;
    }
    vl w(m);
    ll sum = 0;
    for(int i = 0; i < m; i++){
        cin >> w[i];
        sum += w[i];
    }
    ll ans = sum;
    vvb c(m, vb(m, false));
    for(int i = 0; i < n - 1; i++){
        int u = a[i], v = a[i + 1];
        c[u][v] = true;
        c[v][u] = true;
    }
    vi l, r;
    for(int i = 0; i < m; i++){
        if(a[0] == i || a[n - 1] == i || c[i][i]) continue;
        if(l.size() <= r.size()) l.push_back(i);
        else r.push_back(i);
    }
    vl bl = calc_half(l, c, w), br = calc_half(r, c, w);
    //now, br[bits] = maximum weight sum of independent subset that is subset of bits
    for(int i = 0; i < r.size(); i++){
        for(int j = 0; j < (1 << r.size()); j++){
            if(j & (1 << i)) {
                br[j] = max(br[j], br[j ^ (1 << i)]);
            }
        }
    }
    vi lmask(l.size(), 0);
    for(int i = 0; i < l.size(); i++){
        int mask = (1 << r.size()) - 1;
        for(int j = 0; j < r.size(); j++){
            int u = l[i], v = r[j];
            if(c[u][v]) mask ^= (1 << j);
        }
        lmask[i] = mask;
    }
    for(int i = 0; i < bl.size(); i++){
        int mask = (1 << r.size()) - 1;
        ll cans = sum - bl[i];
        for(int j = 0; j < l.size(); j++){
            if(i & (1 << j)) mask = mask & lmask[j];
        }
        cans -= br[mask];
        ans = min(ans, cans);
    }
    cout << ans << "\n";
    
    return 0;
}