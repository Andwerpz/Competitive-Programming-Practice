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

//AtCoder - ARC126E

//completely missed the first observation, but still managed to solve the problem. 
//editorial observes that the answer actually converges to \sum_{i < j} |a[i] - a[j]|. 

//First, let's figure out how to compute the maximum score for a single array, then worry about how
//to handle the queries. Intuitively, it seems like we'll get the maximum score if we sort the array
//and then only do operations on adjacent elements. Since we're operating on the sorted array, notice
//how only the differences between adjacent elements actually matter, so we can transform the current
//problem into an equivalent problem only involving the differences. Naturally, we also must transform
//the operation to match, so our new operation is picking a difference, setting it to 0 and adding half
//of the difference to the two adjacent differences. We'll also add half of the difference to our score.

//Given an example difference array, how can we compute the maximum score? First thing to notice is that
//the order in which you choose the elements doesn't actually matter. Second thing is that the elements
//are actually independent of eachother. If you create two difference arrays that are the componentwise
//sum of the original, you can compute the answer to each of them independently and then sum them to get
//the answer to the original array. Therefore, we can compute the answer to a bunch of elementary 
//difference arrays, and express any difference array as a sum of these elementary difference arrays.

//Let E[x] be the answer to the difference array with a 1 in the xth position, everything else being 0. 
//We can observe some things:
//if x == 1, then E[1] = 1 + E[2] / 2
//else if x == N then E[N] = 1 + E[N - 1] / 2
//otherwise E[x] = 1 + (E[X - 1] + E[X + 1]) / 2
//we can actually solve this system of equations in linear time wrt N, and while the values of E[x] are
//rather difficult to work with, the values of E[x] - E[x + 1] are much more manageable:
//E[x] - E[x + 1] = -N + 2x

//So how can we actually use those differences? If we define D[i] as the ith difference, then our old 
//answer is \sum{D[i] * E[i]}. However, D[i] = A[i + 1] - A[i], and we can refactor everything to
//A[1] * (-E[1]) + A[2] * (E[1] - E[2]) + ... + A[N] * (E[N - 1]). Now, the form of the differences
//is very useful, as when we change an element, we can just keep track of how many elements it displaces
//and increment the answer accordingly. We use a segment tree to keep track of the number of elements, and
//do some coordinate compression to make it fit. 

struct mint;
typedef vector<mint> vm;
typedef vector<vector<mint>> vvm;
typedef pair<mint, mint> pmm;

const ll mod = 998244353;
struct mint {
    ll val; //this should always be in range [0, mod)
    mint(ll _val = 0) {val = _val; if(val >= mod) val %= mod; if(val < 0) val = mod + (val % mod);}
    mint(const mint& other) {val = other.val;}
    bool operator ==(const mint& other) const {return val == other.val;}
    bool operator ==(ll other) const {return val == other;}
    bool operator !=(const mint& other) const {return val != other.val;}
    bool operator !=(ll other) const {return val != other;}
    bool operator >(const mint& other) const {return val > other.val;}
    bool operator >(ll other) const {return val > other;}
    bool operator <(const mint& other) const {return val < other.val;}
    bool operator <(ll other) const {return val < other;}
    mint& operator =(const mint& other) {val = other.val; return *this;}
    mint& operator =(ll other) {val = other; return *this;}
    mint operator +(const mint& other) const {ll ret = val + other.val; while(ret >= mod) {ret -= mod;} return mint(ret);}
    mint operator +(ll other) const {return *this + mint(other);}
    mint& operator +=(const mint& other) {*this = *this + other; return *this;}
    mint& operator +=(ll other) {*this = *this + other; return *this;}
    mint operator -(const mint& other) const {ll ret = val - other.val; while(ret < 0) {ret += mod;} return mint(ret);}
    mint operator -(ll other) const {return *this - mint(other);}
    mint& operator -=(const mint& other) {*this = *this - other; return *this;}
    mint& operator -=(ll other) {*this = *this - other; return *this;}
    mint operator *(const mint& other) const {return mint((val * other.val) % mod);}
    mint operator *(ll other) const {return *this * mint(other);}
    mint& operator *=(const mint& other) {*this = *this * other; return *this;}
    mint& operator *=(ll other) {*this = *this * other; return *this;}
    mint operator /(const mint& other) const {return mint((val / other.val) % mod);}
    mint operator /(ll other) const {return *this / mint(other);}
    mint& operator /=(const mint& other) {*this = *this / other; return *this;}
    mint& operator /=(ll other) {*this = *this / other; return *this;}
    mint operator %(const mint& other) const {return mint(val % other.val);}
    mint operator %(ll other) const {return *this % mint(other);}
    mint& operator %=(const mint& other) {*this = *this % other; return *this;}
    mint& operator %=(ll other) {*this = *this % other; return *this;}

    //don't forget about fermat's little theorem, 
    //a^(m-1) % m = 1. This means that a^(p % m) % m != a^(p) % m, rather a^(p % (m-1)) % m = a^(p) % m. 
    mint pow(const mint& other) const {
        mint ans(1), p(val);
        ll b = other.val;
        while(b != 0) {if(b % 2 == 1) {ans *= p;} p *= p; b /= 2;}
        return ans;
    }
    mint pow(ll other) const {return this->pow(mint(other));}

    //returns X such that A = (B * X) % mod
    mint inv_divide(const mint& other) const {
        return *this * other.pow(mod - 2);
    }

    friend std::ostream& operator<<(std::ostream& os, const mint& m) {os << m.val; return os;}
    friend std::istream& operator>>(std::istream& is, mint& m) {is >> m.val; return is;}
    operator size_t() const {return val;}
};
bool operator ==(ll a, const mint& b) {return mint(a) == b;}
bool operator !=(ll a, const mint& b) {return mint(a) != b;}
bool operator >(ll a, const mint& b) {return mint(a) > b;}
bool operator <(ll a, const mint& b) {return mint(a) < b;}
mint operator +(ll a, const mint& b) {return mint(a) + b;}
mint operator -(ll a, const mint& b) {return mint(a) - b;}
mint operator *(ll a, const mint& b) {return mint(a) * b;}
mint operator /(ll a, const mint& b) {return mint(a) / b;}
mint operator %(ll a, const mint& b) {return mint(a) % b;}

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vl a(n);
    for(ll& x : a) cin >> x;
    vector<pll> qa(q);
    for(int i = 0; i < q; i++){
        ll x, y;
        cin >> x >> y;
        x --;
        qa[i] = {x, y};
    }
    mint dans = 0;
    {
        vl tmpa = a;
        sort(tmpa.begin(), tmpa.end());
        ll ptr = -(n - 1);
        for(int i = 0; i < n; i++){
            dans += ptr * tmpa[i];
            ptr += 2;
        }
    }
    map<ll, ll> mp;
    vl rmp;
    {
        set<ll> s;
        for(int i = 0; i < n; i++) s.insert(a[i]);
        for(int i = 0; i < q; i++) s.insert(qa[i].second);
        rmp = vl(s.size());
        int ptr = 0;
        for(auto i = s.begin(); i != s.end(); i++) rmp[ptr ++] = *i;
        for(int i = 0; i < ptr; i++) mp[rmp[i]] = i;
    }
    function<mint(mint, mint)> fmodify = [](const mint src, const mint val) -> mint{return src + val;};
    function<mint(mint, mint)> fcombine = [](const mint a, const mint b) -> mint{return a + b;};
    Segtree<mint> segt_cnt(rmp.size(), 0, 0, fmodify, fcombine), segt_sum(rmp.size(), 0, 0, fmodify, fcombine);
    for(int i = 0; i < n; i++){
        segt_cnt.modify(mp[a[i]], 1);
        segt_sum.modify(mp[a[i]], a[i]);
    }
    for(int i = 0; i < q; i++){
        ll x = qa[i].first, y = qa[i].second;
        ll o = a[x];
        int io = mp[o], iy = mp[y];
        int l = min(io, iy), r = max(io, iy);
        segt_cnt.modify(io, -1);
        segt_sum.modify(io, -o);
        ll bef = segt_cnt.query(0, io), aft = segt_cnt.query(0, iy);
        mint sum = segt_sum.query(l, r);
        dans -= (mint(-(n - 1)) + (2 * bef)) * o;
        dans += (mint(-(n - 1)) + (2 * aft)) * y;
        if(y >= o) dans -= sum * 2;
        else dans += sum * 2;
        cout << dans.inv_divide(2) << "\n";
        segt_cnt.modify(iy, 1);
        segt_sum.modify(iy, y);
        a[x] = y;
    }
    
    return 0;
}