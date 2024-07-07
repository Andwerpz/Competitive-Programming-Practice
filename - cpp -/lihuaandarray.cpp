#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1797E

//seems like we can implement a custom LCA due to tree height being under 30, and we can also implement custom segtree
//due to each element not changing after more than 30 operations applied. 

//notice that the euler totient function naturally defines a rooted tree; x is the child of phi(x). Also notice that 
//the maximum depth of the tree up to 5 * 10^6 is only 25. 

//if we want to make all the elements in a range equal with the minimum moves, then we want to set all the elements equal
//to the LCA of all the elements. It's obvious to maintain a segment tree to query for LCA over a range. And to find
//the number of operations required, we can simply maintain another segment tree to tell us the sum of distances
//to the root node in a range. 

//handling applying one operation over a range is more problematic. Luckily the tree structure here helps us out again. 
//Since the maximum depth is around 30, we can do a not lazy, lazy segment tree. Instead of doing lazy update, 
//we'll just update every subtree completely. To make it not TLE, we'll keep track for each segment if it just
//consists of all 1s, and not update that subtree if it does. 

int *phi, *tdist;
void calc_totient(int n) {
    phi = new int[n + 1];
    tdist = new int[n + 1];
    for (int i = 0; i <= n; i++)
        phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
    tdist[1] = 0;
    for(int i = 2; i <= n; i++){
        tdist[i] = tdist[phi[i]] + 1;
    }
}

const int K = 5e6 + 100;
int dis[K], fa[K][6];
void init_tree() {
	dis[1] = 1;
    for(int j = 0; j <= 5; j++){
        fa[1][j] = 1;
    }
    for(int i = 2; i < K; i++){
        dis[i] = dis[phi[i]] + 1;
		fa[i][0] = phi[i];
        for(int j = 1; j <= 5; j++){
            fa[i][j] = fa[fa[i][j-1]][j-1];
        }
    }
}

int lca(int u, int v) {
	if(dis[u] < dis[v]) swap(u, v);
    for(int i = 5; i >= 0; i--){
        if(dis[fa[u][i]] >= dis[v]) u = fa[u][i];
    }
	if(u == v) return u;
    for(int i = 5; i >= 0; i--){
        if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    }
	return fa[u][0];
}

struct seg {
    int lcav, dsts, all_one, ign;
    seg(){
        ign = true;
    }
    seg(int _lcav) {
        ign = false;
        lcav = _lcav;
        dsts = tdist[_lcav];
        all_one = _lcav == 1;
    }
};
struct Segtree {
    int n;
    seg* arr;
    Segtree(int _n) {
        n = _n;
        int x = 1;
        while(x < n) {
            x <<= 1;
        }
        n = x;

        arr = new seg[2 * n];
    }

    seg combine(seg a, seg b) {
        if(a.ign) return b;
        if(b.ign) return a;
        seg ret;
        ret.ign = false;
        ret.all_one = a.all_one && b.all_one;
        ret.lcav = lca(a.lcav, b.lcav);
        ret.dsts = a.dsts + b.dsts;
        return ret;
    }

    void build() {
        for (int i = n - 1; i > 0; i--) {   
            arr[i] = combine(arr[i * 2], arr[i * 2 + 1]);
        }
    }

    void modify(int l, int r) {
        _modify(l, r, 0, n, 1);
    }

    void _modify(int l, int r, int tl, int tr, int ind) {
        if(l == r){
            return;
        }
        if(l == tl && r == tr && arr[ind].all_one) {
            return;
        }
        if(l == tl && r == tr && r - l == 1) {
            //apply the update
            arr[ind] = {phi[arr[ind].lcav]};
            return;
        }
        int mid = tl + (tr - tl) / 2;
        if(l < mid) {
            _modify(l, min(r, mid), tl, mid, ind * 2);
        }
        if(r > mid) {
            _modify(max(l, mid), r, mid, tr, ind * 2 + 1);
        }
        arr[ind] = combine(arr[ind * 2], arr[ind * 2 + 1]);
    }

    seg query(int l, int r) {
        return _query(l, r, 0, n, 1);
    }

    seg _query(int l, int r, int tl, int tr, int ind) {
        if(l == r){
            return {};
        }
        if(l == tl && r == tr){
            return arr[ind];
        }
        seg ret = {};
        int mid = tl + (tr - tl) / 2;
        if(l < mid) {
            ret = combine(ret, _query(l, min(r, mid), tl, mid, ind * 2));
        }
        if(r > mid) {
            ret = combine(ret, _query(max(l, mid), r, mid, tr, ind * 2 + 1));
        }
        return ret;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    calc_totient(K);
    init_tree();
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    Segtree segt(n);
    for(int i = 0; i < n; i++){
        segt.arr[i + segt.n] = {a[i]};
    }
    segt.build();
    for(int i = 0; i < m; i++){
        int t, l, r;
        cin >> t >> l >> r;
        l --;
        if(t == 1){
            segt.modify(l, r);   
        }
        else {
            seg q = segt.query(l, r);
            ll ans = q.dsts - (r - l) * tdist[q.lcav];
            cout << ans << "\n";
        }
    }
    
    return 0;
}