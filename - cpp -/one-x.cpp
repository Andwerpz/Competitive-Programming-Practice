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
 
//Codeforces - 1905E

//first observe that the structure of a subtree is solely dependent on the size of the range it represents. 
//Next, make an observation about the number of unique subtree sizes, if you write a brute force checker, it 
//turns out it grows proportional to log(n) (at least that is what the testing indicated). So some
//memoized recursive solution will be fast enough. 

//Define f(n) as the answer to the tree that represents range [1, n]. First, denote the midpoint as m. Then, 
//the left subtree would represent [1, m] and right would represent [m + 1, n]. Let's account for the ways 
//to select the leaves such that the root is the LCA, there are R = (2^n - 1) - (2^m - 1) - (2^{n - m} - 1) ways. 

//Next, we have to account for the left and right subtrees. We can't simply add f(m) + f(n - m) to the answer as
//f(m) and f(n - m) assume that the label for the root node is 1. So how does the answer change when the root label 
//changes?

//to describe this, we define g(n). Let g(n) be the change in the answer to f(n) if you added 1 to the root label.
//Notice that this is exactly the change when f(n) becomes the left subtree, and when f(n) becomes the right 
//subtree, the change is exactly 2 * g(n), because we add 2 to the root label instead of 1. 

//How can we compute g(n)? It can be directly computed as g(n) = 2 * g(m) + 2 * g(n - m) + R, as all the layers
//in the left and right subtrees get 'shifted down', and we add the root node contribution. Then, f(n) can be 
//computed as f(n) = R + f(m) + f(n - m) + g(m) + 2 * g(n - m)

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

//n >= k
mint nck(mint n, mint k) {
    return fac[n] * invfac[k] * invfac[n - k];
}

map<ll, mint> dp, idp;
mint solve(ll n) {
    if(dp.count(n)) return dp[n];
    if(n == 1) return 1;
    ll m = (n + 1) / 2;
    mint rcomb = (mint(2).pow(n) - 1) - (mint(2).pow(m) - 1) - (mint(2).pow(n - m) - 1);
    mint ans = solve(m) + solve(n - m) + rcomb;
    mint li = idp[m], ri = idp[n - m], ci = rcomb;
    ans += li + ri * 2;
    ci += li * 2 + ri * 2;
    dp[n] = ans;
    idp[n] = ci;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    idp[1] = 1;
    int t;
    cin >> t;
    while(t--){
        ll n;
        cin >> n;
        cout << solve(n) << "\n";
    }
    
    return 0;
}