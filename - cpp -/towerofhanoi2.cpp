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

//2025 ICPC Asia Pacific Championship - D

//first, let's see how to answer queries of type [l, r] in linear time. Denote h(n) as the number of steps required to 
//solve the hanoi puzzle with all n discs on the second or third pole. h(n) = 2^n - 1.

//consider the largest disc. We want to move the largest disc to pole 1. If it is not initially at pole 1, lets say it's at 
//pole 2, then we first need to move all other discs to pole 3, move largest disc to pole 1, then move all other discs to pole
//1. If we define f(k, 1) as the cost to move all discs with size <= k to pole 1, then f(k, 1) = f(k - 1, 3) + h(k) + 1. 

//observe that if the largest disc is already at it's target pole, then we can skip all these other steps, so it would look
//like f(k, 1) = f(k - 1, 1). 

//To answer the queries in sublinear time, we can use a segment tree. Let's say we have two segments, L, R, and we know
//for each segment if I want to move the largest disc in segment R to p, then what the cost of doing so is, and if there
//was a smaller disc, what position I would have to move that one to. Then, merging segments is not too bad (look at code),
//and handling the modify queries is simply replacing a segment and merging up. 

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

struct mint;
typedef vector<mint> vm;
typedef vector<vector<mint>> vvm;
typedef pair<mint, mint> pmm;

const ll mod = 998244353;
struct mint {
    ll val; //this should always be in range [0, mod)
    mint(ll _val = 0) {val = _val; if(val < 0) val = mod + (val % mod); val %= mod;}
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
    mint operator /(const mint& other) const {return *this * other.pow(mod - 2);}
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

const int N = 1e6;
vm pow2(N);

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    pow2[0] = 1;
    for(int i = 1; i < N; i++) pow2[i] = pow2[i - 1] * 2;
    int n, q;
    cin >> n >> q;
    struct seg {
        array<int, 4> rec;
        array<mint, 4> cost;
        int len;
        seg() {
            rec = {-1, 1, 2, 3};
            cost = {-1, 0, 0, 0};
            len = 0;
        }
        seg(int cur) {
            for(int i = 1; i <= 3; i++){
                if((i ^ cur) == 0) rec[i] = i, cost[i] = 0;
                else rec[i] = i ^ cur, cost[i] = 1;
            }
            // cout << "INIT SEG : " << cost[1] << " " << cost[2] << " " << cost[3] << "\n";
            len = 1;
        }
        seg(const seg l, const seg r) {
            for(int i = 1; i <= 3; i++){
                rec[i] = l.rec[r.rec[i]];
                cost[i] = r.cost[i] * pow2[l.len] + l.cost[r.rec[i]];
            }
            len = l.len + r.len;
        }
    };
    function<seg(seg, seg)> fmodify = [](const seg src, const seg val) -> seg{return val;};
    function<seg(seg, seg)> fcombine = [](const seg l, const seg r) -> seg{return seg(l, r);};
    Segtree<seg> segt(n, seg(), seg(), fmodify, fcombine); 
    {
        vector<seg> a(n);
        for(int i = 0; i < n; i++){
            int cur;
            cin >> cur;
            a[i] = seg(cur);
        }
        segt.assign(a);
    }
    // cout << "DONE ASSIGN" << endl;
    for(int i = 0; i < q; i++){
        string type;
        cin >> type;
        if(type == "c") {
            int x, y;
            cin >> x >> y;
            x --;
            segt.modify(x, seg(y));
        }
        else {  //type == "s"
            int l, r;
            cin >> l >> r;
            l --;
            seg ret = segt.query(l, r);
            // cout << "RET : " << "\n";
            // cout << ret.rec[1] << " " << ret.rec[2] << " " << ret.rec[3] << "\n";
            // cout << ret.cost[1] << " " << ret.cost[2] << " " << ret.cost[3] << "\n";
            // cout << ret.len << "\n";
            cout << ret.cost[1] << "\n";
        }
    }

    return 0;
}