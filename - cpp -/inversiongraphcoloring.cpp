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

//Codeforces - 2143 D1 D2

//how can we tell if some sequence is good?
//observe that a good sequence cannot have a strictly decreasing subsequence of length 3
//actually, this is a necessary and sufficient condition. So to put it more intuitively, if for every element of the 
//sequence, it's not less than an element that's itself less than another element, then it's a good sequence. 

//easy version can be solved using dp:
//dp[i][j][k] = number of ways given
// we're on element i
// j = maximum element in the sequence so far
// k = maximum element in the sequence that's less than another element so far. 
//complexity : O(n^3)

//hard version can be solved using some segment tree abuse. Note that this solution is probably not intended. 
//to derive this solution, you just need to observe that for every i, you only update O(n) elements in the dp table. 
//can simulate these updates using some range sum queries, increment modifications. Total complexity : O(n^2 * log(n))
//had to do some constant factor optimizations to get it to not TLE, such as getting rid of lambdas

struct mint;
typedef vector<mint> vm;
typedef vector<vector<mint>> vvm;
typedef pair<mint, mint> pmm;

const ll mod = 1e9 + 7;
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
    mint pow(ll b) const {
        mint ans(1), p(val);
        while(b != 0) {if(b % 2 == 1) {ans *= p;} p *= p; b /= 2;}
        return ans;
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

struct Segtree {
    //note that t[0] is not used
    int n;
    mint* t;

    Segtree() {}
    Segtree(int n) {
        this->n = n;
        t = new mint[2 * n];
        for(int i = 0; i < n; i++) t[i + n] = 0;
        build();
    }

	// build the tree after manually assigning the values.
    void build() { 
        for (int i = n - 1; i > 0; i--)
            t[i] = t[i * 2] + t[i * 2 + 1];
    }

    void modify(int p, mint value) { // set value at position p
        p += n;
        t[p] += value;
        for (p /= 2; p > 0; p /= 2)
            t[p] = t[p * 2] + t[p * 2 + 1];
    }

    mint query(int l, int r) { // sum on interval [l, r)
        mint l_res = 0, r_res = 0;
        bool l_none = true, r_none = true;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) {
                if(l_none) {l_none = false; l_res = t[l];}
                else l_res = l_res + t[l];
                l++;
            }
            if (r % 2 == 1) {
                r--;
                if(r_none) {r_none = false; r_res = t[r];}
                else r_res = t[r] + r_res;
            }
        }
        if(l_none) return r_res;
        if(r_none) return l_res;
        return l_res + r_res;
    }

    mint query(int ind) {
        return this->query(ind, ind + 1);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        vector<Segtree> row(n + 1);
        vector<Segtree> col(n + 1);
        for(int i = 0; i <= n; i++) {
            row[i] = Segtree(n + 1);
            col[i] = Segtree(n + 1);
        }
        row[0].modify(0, 1);
        col[0].modify(0, 1);
        // for(int j = 0; j <= n; j++) {
        //     for(int k = 0; k <= n; k++) {
        //         cout << row[j].query(k) << " ";
        //     }
        //     cout << "\n";
        // }
        // cout << "\n";
        for(int i = 0; i < n; i++) {
            //vertical rect
            for(int j = a[i] + 1; j <= n; j++) {
                mint val = row[j].query(0, a[i] + 1);
                row[j].modify(a[i], val);
                col[a[i]].modify(j, val);
            }
            //horizontal rect
            for(int j = 0; j <= n; j++) {
                mint val = col[j].query(0, a[i] + 1);
                col[j].modify(a[i], val);
                row[a[i]].modify(j, val);
            }
            // for(int j = 0; j <= n; j++) {
            //     for(int k = 0; k <= n; k++) {
            //         cout << row[j].query(k) << " ";
            //     }
            //     cout << "\n";
            // }
            // cout << "\n";
        }
        mint ans = 0;
        for(int i = 0; i <= n; i++) ans += row[i].query(0, n + 1);
        cout << ans << "\n";

        // -- easy version sol
        // int n;
        // cin >> n;
        // vi a(n);
        // for(int i = 0; i < n; i++) cin >> a[i];
        // //dp[i][j][k]
        // // j = maximum element so far
        // // k = maximum element less than another element so far
        // vector<vvm> dp(n + 1, vvm(n + 1, vm(n + 1, 0)));
        // dp[0][0][0] = 1;
        // for(int i = 0; i < n; i++) {
        //     for(int j = 0; j <= n; j++) {
        //         for(int k = 0; k <= j; k++) {
        //             //do nothing
        //             dp[i + 1][j][k] += dp[i][j][k];
        //             //take this element
        //             if(a[i] >= k) {
        //                 if(a[i] >= j) dp[i + 1][max(j, a[i])][k] += dp[i][j][k];
        //                 else dp[i + 1][j][max(k, a[i])] += dp[i][j][k];
        //             }
        //         }
        //     }
        //     for(int j = 0; j <= n; j++) {
        //         for(int k = 0; k <= n; k++) {
        //             cout << dp[i][j][k] << " ";
        //         }
        //         cout << "\n";
        //     }
        //     cout << "\n";
        // }
        // mint ans = 0;
        // for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) ans += dp[n][i][j];
        // cout << ans << "\n";
    }
    
    return 0;
}