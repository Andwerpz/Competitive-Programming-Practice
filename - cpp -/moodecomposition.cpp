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

//USACO 2025 US Open - Gold P1

//we want to partition the string [s] * L into subsequences like 'MOOO...OOO' where there are k 'O's. 
//observe that if it's possible to partition [s] * L, then it's always possible to partition s. 
//actually, we can treat each s in [s] * L independently as if some 'M' takes an 'O' from an s
//later on, then it's always impossible to complete the partition. 

//so we just need to compute the number of ways to partition s, then take that to the Lth power. 

//to find the number of ways to partition s, we can first consider the last 'M'. It can freely pick the 
//'O's after it that it wants. Then, the next to last 'M' can choose 'O's and so on. This completely determines
//the partition that we get, and it also covers all partitions. 

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
    mint pow(const ll other) const {
        mint ans(1), p(val);
        ll b = other;
        while(b != 0) {if(b % 2 == 1) {ans *= p;} p *= p; b /= 2;}
        return ans;
    }
    // mint pow(ll other) const {return this->pow(mint(other));}

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    fac_init(1e6 + 100);
    ll k, n, l;
    cin >> k >> n >> l;
    string s;
    cin >> s;
    mint ans = 1;
    int ocnt = 0;
    for(int i = n - 1; i >= 0; i--){
        if(s[i] == 'O') ocnt ++;
        else {
            ans *= nck(ocnt, k);
            ocnt -= k;
        }
    }
    ans = ans.pow(l);
    cout << ans << "\n";
    
    return 0;
}