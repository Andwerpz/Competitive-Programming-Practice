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

//ICPC NAC 2025 - E

//divide and conquer / small to large merging. Couldn't get index set to work, too much constant factor. Had to
//offline all the queries and answer them using a segment tree. 

//first compute d[i] = h[i] - a[i] for all i. Instead of non-negative d[i] adding to human score and negative d[i]
//adding to ai score, just have one score and they both add the signed difference to it. Note that if we multiply all
//negative d[i] by k, then we can ignore k from here on (almost).

//Since the ai will flip the maximum d[i] within the subarray, we can do divide and conquer. To solve segment [l, r),
//find the index with the maximum d[i], M. Then, fix the left bound, and find how many right bounds work with this left 
//bound. Finding the number of right bounds that can work can be done in O(log(n)), using a mystery technique we'll
//discuss later. Finally, we can solve segments [l, M), [M + 1, r).

//actually, this is too slow as we fix O(n^2) left bounds. If instead we selectively fix either the left or right bound
//depending on whether M - l or r - M is smaller, we can get this down to O(n * log(n)) via small to large merging. 
//Fixing the right bound and finding the number of compatible left bounds can be done much similarly to fixing the left
//bound and finding the number of right bounds. 

//To query the number of right bounds that can work, we can build an index set at every layer, and maintain them
//in O(n * log(n)^2) using small to large merging. However, the constant factor of this method is too large. Instead, 
//we can notice that we don't have to do all the queries online, we can offline them split them into two prefix queries,
//and sort them by their right bound. Finally, we can handle every prefix query using a segment tree, with much better
//constant factor. 

template <typename T>
struct Segtree {
    //note that t[0] is not used
    int n;
    T* t;
    T uneut, qneut;
    function<T(T, T)> fmodify, fcombine;

    Segtree() {}
    Segtree(int n, T updateNeutral, T queryNeutral, function<T(T, T)> fm, function<T(T, T)> fc) {
        this->n = n;
        t = new T[2 * n];
        this->fmodify = fm;
        this->fcombine = fc;
        uneut = updateNeutral;
        qneut = queryNeutral;
        for(int i = 0; i < n; i++) t[i + n] = uneut;
        build();
    }

    void assign(vector<T>& arr) {
        for(int i = 0; i < min(n, (int) arr.size()); i++)
            t[i + n] = arr[i];
        build();
    }

	// build the tree after manually assigning the values.
    void build() { 
        for (int i = n - 1; i > 0; i--)
            t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
    }

    void modify(int p, T value) { // set value at position p
        p += n;
        t[p] = fmodify(t[p], value);
        for (p /= 2; p > 0; p /= 2)
            t[p] = fcombine(t[p * 2], t[p * 2 + 1]);
    }

    T query(int l, int r) { // sum on interval [l, r)
        T l_res = qneut, r_res = qneut;
        bool l_none = true, r_none = true;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) {
                if(l_none) {l_none = false; l_res = t[l];}
                else l_res = fcombine(l_res, t[l]);
                l++;
            }
            if (r % 2 == 1) {
                r--;
                if(r_none) {r_none = false; r_res = t[r];}
                else r_res = fcombine(t[r], r_res);
            }
        }
        if(l_none) return r_res;
        if(r_none) return l_res;
        return fcombine(l_res, r_res);
    }

    T query(int ind) {
        return this->query(ind, ind + 1);
    }
};

#include <bits/extc++.h> 
using namespace __gnu_pbds;
/*
order_of_key (k) : Number of items strictly smaller than k .
find_by_order(k) : K-th element in a set (counting from zero).
*/
template <class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int N = 2 * 100000 + 100;
vector<vector<ll>> q(N), cq(N);    //{l, val}

Segtree<pll> segt;
vl pfx, d;
ll tans = 0, ans = 0;
ll k;

//{prefix tree, suffix tree}
//{{pfx[r], r}, {sfx[l], l}}
Tree<pll> solve(int l, int r) {
    if(l == r) return {};
    int maxind = segt.query(l, r).second;
    if(d[maxind] < 0) {
        Tree<pll> pfxt;
        for(int i = l; i < r; i++) pfxt.insert({pfx[i + 1], i + 1});
        return pfxt;
    }
    Tree<pll> lt = solve(l, maxind), rt = solve(maxind + 1, r);
    // cout << "MAX : " << l << " " << r << " " << maxind << " " << d[maxind] << "\n";
    // cout << "LT SIZE : " << lt.first.size() << " " << rt.first.size() << "\n";
    if(lt.size() < rt.size()) {
        rt.insert({pfx[maxind + 1], maxind + 1});
        for(int i = l; i <= maxind; i++) {
            ll cscore = pfx[maxind] - pfx[i] - d[maxind] * k;
            ll req = -cscore + pfx[maxind + 1];
            // cout << "REQL : " << i << " " << req << "\n";
            tans += rt.size() - rt.order_of_key({req, -1});

            ans += rt.size();
            cq[r + 1].push_back(req - 1);
            q[maxind + 1].push_back(req - 1);
        }
        for(pll x : lt) rt.insert(x);
        return rt;
    }
    else {
        // lt.first.insert({pfx[maxind + 1], maxind + 1});
        lt.insert({pfx[l], l});
        // for(pll x : lt.second) cout << "(" << x.first << ", " << x.second << ") ";
        // cout << "\n";
        for(int i = r; i > maxind; i--){
            ll cscore = pfx[i] - pfx[maxind + 1] - d[maxind] * k;
            //pfx[maxind] - pfx[l] >= -cscore
            //pfx[maxind] + cscore >= pfx[l]
            //pfx[l] <= pfx[maxind] + cscore
            ll req = pfx[maxind] + cscore;  //what must pfx[l] be less/greater than for [l, i) to have score >= 0?
            tans += lt.order_of_key({req, 1e9});
            
            q[maxind + 1].push_back(req);
            cq[l].push_back(req);
            // cout << "REQR : " << i << " " << req << " " << sfx[i] << " " << inc << "\n";
        }
        lt.erase({pfx[l], l});
        lt.insert({pfx[maxind + 1], maxind + 1});
        for(pll x : rt) lt.insert(x);
        return lt;
    }
}

void solve_fast(int l, int r) {
    if(l == r) return;
    int maxind = segt.query(l, r).second;
    if(d[maxind] < 0) return;
    solve_fast(l, maxind), solve_fast(maxind + 1, r);
    if(maxind - l < r - (maxind + 1)) {
        for(int i = l; i <= maxind; i++) {
            ll cscore = pfx[maxind] - pfx[i] - d[maxind] * k;
            ll req = -cscore + pfx[maxind + 1];
            ans += r - maxind;
            cq[r + 1].push_back(req - 1);
            q[maxind + 1].push_back(req - 1);
        }
    }
    else {
        for(int i = r; i > maxind; i--){
            ll cscore = pfx[i] - pfx[maxind + 1] - d[maxind] * k;
            ll req = pfx[maxind] + cscore;  //what must pfx[l] be less/greater than for [l, i) to have score >= 0?
            q[maxind + 1].push_back(req);
            cq[l].push_back(req);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n;
    cin >> n >> k;
    vl h(n), a(n);
    for(int i = 0; i < n; i++) cin >> h[i];
    for(int i = 0; i < n; i++) cin >> a[i];
    d = vl(n);
    for(int i = 0; i < n; i++){
        d[i] = h[i] - a[i];
        if(d[i] < 0) d[i] *= k;
    }
    // for(int i = 0; i < n; i++) cout << d[i] << " ";
    // cout << "\n";
    pfx = vl(n + 1, 0);
    for(int i = 1; i <= n; i++) pfx[i] = pfx[i - 1] + d[i - 1];
    {
        function<pll(pll, pll)> fmodify = [](const pll src, const pll val) -> pll{return val;};
        function<pll(pll, pll)> fcombine = [](const pll a, const pll b) -> pll{return a.first > b.first? a : b;};
        segt = Segtree<pll>(n, {0, 0}, {-1e18, -1}, fmodify, fcombine);
    }
    for(int i = 0; i < n; i++){
        segt.modify(i, {d[i], i});
    }
    solve_fast(0, n);
    //do coordinate compression
    vl vals(n + 1), itoi(n + 1);
    {
        vector<pll> ord(n + 1); //{val, ind}
        for(int i = 0; i <= n; i++) ord[i] = {pfx[i], i};
        sort(ord.begin(), ord.end());
        for(int i = 0; i <= n; i++){
            vals[i] = ord[i].first;
            itoi[ord[i].second] = i;
        }
    }   
    //set up segt
    function<int(int, int)> fmodify = [](const int src, const int val) -> int{return src + val;};
    function<int(int, int)> fcombine = [](const int a, const int b) -> int{return a + b;};
    Segtree<int> qsegt(n + 1, 0, 0, fmodify, fcombine); 
    function<int(ll)> find_r = [&](ll val) -> int {
        if(vals[n] <= val) return n + 1;
        int low = 0, high = n;  //find first element that is > val
        int cans = high;
        while(low <= high) {
            int mid = low + (high - low) / 2;
            if(vals[mid] > val) cans = mid, high = mid - 1;
            else low = mid + 1;
        }
        return cans;
    };
    //handle queries
    for(int i = 0; i <= n + 1; i++){
        for(int j = 0; j < q[i].size(); j++){
            ans += qsegt.query(0, find_r(q[i][j]));
        }
        for(int j = 0; j < cq[i].size(); j++){
            ans -= qsegt.query(0, find_r(cq[i][j]));
        }
        if(i != n + 1) qsegt.modify(itoi[i], 1);
    }
    // cout << "TANS : " << tans << "\n";
    cout << ans << "\n";
    
    return 0;
}