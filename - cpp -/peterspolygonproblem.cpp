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

//HammerWars 2025 - F

//can do a divide and conquer sol, fix the max element in segment [l, r), then fix l and binary search for the
//smallest r such that the sum [l, r) > 2 * mx. 

//you have to account for segments such that there are two maximum elements, but that's relatively easy. 

const bool debug = false;

//single modify, range query
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

int n;
vl a, pfx;
Segtree<pll> segt;
int ansl, ansr;

void upd_ans(int l, int r) {
    assert(r - l >= 3);
    // cout << "UPD ANS : " << l << " " << r << "\n";
    if(r - l < ansr - ansl || (r - l == ansr - ansl && l < ansl)) {
        ansl = l;
        ansr = r;
    }
}

void solve(int l, int r) {
    if(l == r) return;
    auto [mxv, mxind] = segt.query(l, r);
    // cout << "SOLVE : " << l << " " << r << " " << mxv << " " << mxind << "\n";
    if(mxind - l < r - mxind) {
        for(int i = l; i <= mxind; i++) {
            if(pfx[r] - pfx[i] <= mxv * 2) break;
            int low = mxind + 1, high = r;
            int cans = high;
            while(low <= high) {
                int mid = low + (high - low) / 2;
                if(pfx[mid] - pfx[i] > mxv * 2) {
                    cans = mid;
                    high = mid - 1;
                }
                else {
                    low = mid + 1;
                }
            }
            upd_ans(i, cans);
        }
    }
    else {
        // cout << "FIX RIGHT\n";
        for(int i = r; i >= mxind + 1; i--) {
            if(pfx[i] - pfx[l] <= mxv * 2) break;
            int low = l, high = mxind;
            int cans = low;
            while(low <= high) {
                int mid = low + (high - low) / 2;
                if(pfx[i] - pfx[mid] > mxv * 2) {
                    cans = mid;
                    low = mid + 1;
                }
                else {
                    high = mid - 1;
                }
            }
            upd_ans(cans, i);
        }
    }
    solve(l, mxind);
    solve(mxind + 1, r);
}

pii solve_fast() {
    pfx = vl(n + 1, 0);
    for(int i = 1; i <= n; i++) pfx[i] = pfx[i - 1] + a[i - 1];
    function<pll(pll, pll)> fmodify = [](const pll src, const pll val) -> pll{return val;};
    function<pll(pll, pll)> fcombine = [](const pll a, const pll b) -> pll{return a.first > b.first? a : b;};
    segt = Segtree<pll>(n, {0, 0}, {-1e18, -1}, fmodify, fcombine);
    for(int i = 0; i < n; i++) segt.modify(i, {a[i], i});
    ansl = 0, ansr = n;
    solve(0, n);
    //account for segments with duplicate maxima
    map<ll, vi> f;
    for(int i = 0; i < n; i++) {
        f[a[i]].push_back(i);
    }
    for(auto i = f.begin(); i != f.end(); i++) {
        ll val = i->first;
        vi occ = i->second;
        for(int j = 1; j < occ.size(); j++) {
            int cur = occ[j];
            int pv = occ[j - 1];
            if(cur + 1 - pv > 2 && segt.query(pv, cur + 1).first < val) {
                upd_ans(pv, cur + 1);
            }
        }
    }
    return {ansl, ansr};
}

pii solve_slow() {
    ansl = 0, ansr = n;
    for(int i = 0; i < n; i++) {
        ll sum = 0, mx = 0;
        for(int j = i; j < n; j++) {
            sum += a[j], mx = max(mx, a[j]);
            if(mx * 2 < sum) {
                upd_ans(i, j + 1);
                break;
            }
        }
    }
    return {ansl, ansr};
}

void verify_sol() {
    pii fans = solve_fast();
    pii sans = solve_slow();
    if(fans != sans) {
        cout << "ERROR : \n";
        for(int i = 0; i < n; i++) cout << a[i] << " ";
        cout << "\n";
        cout << fans.first << " " << fans.second << "\n";
        cout << sans.first << " " << sans.second << "\n";
        cout << endl;
        assert(false);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> n;
    a = vl(n);
    if(debug) {
        srand(time(0));
        while(true) {
            for(int i = 0; i < n; i++) {
                a[i] = rand() + 1;
            }
            verify_sol();
        }
    }
    else {
        for(int i = 0; i < n; i++) cin >> a[i];
        pii ans = solve_fast();
        cout << (ans.first + 1) << " " << ans.second << "\n";
    }
    
    return 0;
}