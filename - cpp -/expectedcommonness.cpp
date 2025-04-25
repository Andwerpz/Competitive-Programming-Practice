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

//Spring 2025 Columbia University Local Contest - J

// total number of ways to build the tree is (n - 1)!

// for some node i, what's the amount of ways for the subtree rooted at i to have size k?
// there are i - 1 nodes placed before node i

// so i + 1th node has 1 way to be in i's subtree, (i - 1) ways to not be in i's subtree
// can do dp? dp[i][j] = nr ways to make given i nodes total and j nodes in the selected subtree

//from here, look up the numbers in the dp table in OEIS, you get A136125. There's a nice formula, so just 
//use that. 

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

mint gcd(mint a, mint b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

vm fac, invfac;
void fac_init(int N) {
    fac = vm(N + 1), invfac = vm(N + 1);
    fac[0] = 1;
    for(int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i;
    invfac[N] = mint(1) / fac[N];
    for(int i = N; i > 0; i--) invfac[i - 1] = invfac[i] * i;
}

//sum of ways of (ind)th node
mint calc_ways(int n, int ind) {
    //dp[i][j] = nr ways to make given that 
    // - i nodes in total
    // - j nodes in (ind) subtree
    vvm dp(n + 1, vm(n + 1, 0));
    dp[ind + 1][1] = fac[ind];
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= n; j++){
            if(j > i) break;
            //put into (ind) subtree
            if(j != n) dp[i + 1][j + 1] += dp[i][j] * j;
            //don't put into (ind) subtree
            dp[i + 1][j] += dp[i][j] * (i - j);
        }
    }
    mint ans = 0;
    for(int i = 1; i <= n; i++) ans += dp[n][i] * mint(2).pow(i - 1);
    cout << "WAYS : " << ind << " " << ans << "\n";
    return ans;
}

mint calc_all(int n) {
    //dp[i][j] = nr ways to make given that 
    // - i nodes in total
    // - j nodes in (ind) subtree
    vvm dp(n + 1, vm(n + 1, 0));
    for(int i = 0; i < n; i++) dp[i + 1][1] = fac[i];
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= n; j++){
            if(j > i) break;
            //put into (ind) subtree
            if(j != n) dp[i + 1][j + 1] += dp[i][j] * j;
            //don't put into (ind) subtree
            dp[i + 1][j] += dp[i][j] * (i - j);
        }
    }
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            cout << dp[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    mint ans = 0;
    for(int i = 1; i <= n; i++) ans += dp[n][i] * mint(2).pow(i - 1);
    return ans;
}

mint calc_fast(int n) { 
    mint ans = 0;
    for(int i = 1; i <= n; i++) {
        mint cur;
        if(i == n) cur = fac[n - 1];
        else cur = fac[n] / (mint(i) * (i + 1));
        ans += cur * mint(2).pow(i - 1);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    fac_init(1e6);
    // for(int i = 1; i <= 8; i++) calc_all(i);
    
    int n;
    cin >> n;
    mint ans = 0;
    // for(int i = 0; i < n; i++){
    //     ans += calc_ways(n, i);
    // }
    // ans = calc_all(n);
    ans = calc_fast(n);
    // cout << ans << "\n";
    cout << ans / fac[n - 1] << "\n";
    
    return 0;
}