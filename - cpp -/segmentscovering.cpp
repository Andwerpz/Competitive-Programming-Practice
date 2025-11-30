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

//Codeforces - 2125D

//just take the sum of probabilities over all possible ways that the entire thing can be covered exactly once
//dp[i] = sum of probabilities over all ways that we can make the prefix [0, i)
//to transition from dp[i], we can look at all segments that start at i, and try each of them. We'll need to also keep track of
//the product of probabilities of any segment that would have to not exist given that we are taking the transition segment. 

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> m >> n;
    vm dp(n + 1, 0);
    dp[0] = 1;
    vm pfx(n + 1, 1);   //query product of 1 - p/q in range. 
    vector<vvi> c(n);   //{r, p, q}
    for(int i = 0; i < m; i++){
        int l, r, p, q;
        cin >> l >> r >> p >> q;
        l --;
        pfx[l + 1] *= mint(1) - mint(p) / mint(q);
        c[l].push_back({r, p, q});
    }
    for(int i = 1; i <= n; i++) pfx[i] *= pfx[i - 1];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < c[i].size(); j++){
            int r = c[i][j][0], p = c[i][j][1], q = c[i][j][2];
            mint prob = mint(p) / mint(q);
            dp[r] += dp[i] * prob * pfx[r] / pfx[i] / (mint(1) - prob);
        }
    }
    cout << dp[n] << "\n";
    
    return 0;
}