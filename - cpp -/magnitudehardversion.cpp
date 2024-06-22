#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1984C2

//my observation in the previous problem was correct, but it was not fully descriptive of the process required. 
//specifically, once you perform the first type 2 operation, if you're on the track to create the maximum value then 
//it shouldn't matter whether you perform type 1 or 2 operations from that point onwards. 

//so for every prefix, you can compute the number of ways to get to some value by only using type 1 operations, 
//and then combine that with suffixes. 

//note that we have to consider the case where you don't need to perform any type 2 operations seperately. 

struct mint;
vector<mint> fac;
map<pair<mint, mint>, mint> nckdp;

ll mod = 998244353;
struct mint {
    ll val;
    mint(ll _val = 0) {val = _val;}
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
    mint operator +(ll other) const {ll ret = val + other; while(ret >= mod) {ret -= mod;} return mint(ret);}
    mint& operator +=(const mint& other) {*this = *this + other; return *this;}
    mint& operator +=(ll other) {*this = *this + other; return *this;}
    mint operator -(const mint& other) const {ll ret = val - other.val; while(ret < 0) {ret += mod;} return mint(ret);}
    mint operator -(ll other) const {ll ret = val - other; while(ret < 0) {ret += mod;} return mint(ret);}
    mint& operator -=(const mint& other) {*this = *this - other; return *this;}
    mint& operator -=(ll other) {*this = *this - other; return *this;}
    mint operator *(const mint& other) const {return mint((val * other.val) % mod);}
    mint operator *(ll other) const {return mint((val * other) % mod);}
    mint& operator *=(const mint& other) {*this = *this * other; return *this;}
    mint& operator *=(ll other) {*this = *this * other; return *this;}
    mint operator /(const mint& other) const {return mint((val / other.val) % mod);}
    mint operator /(ll other) const {return mint((val / other) % mod);}
    mint& operator /=(const mint& other) {*this = *this / other; return *this;}
    mint& operator /=(ll other) {*this = *this / other; return *this;}
    mint operator %(const mint& other) const {return mint(val % other.val);}
    mint operator %(ll other) const {return mint(val % other);}
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
    mint pow(ll other) const {
        mint ans(1), p(val);
        ll b = other;
        while(b != 0) {if(b % 2 == 1) {ans *= p;} p *= p; b /= 2;}
        return ans;
    }

    //returns X such that A = (B * X) % mod
    mint inv_divide(const mint& other) const {
        return *this * other.pow(mod - 2);
    }

    friend std::ostream& operator<<(std::ostream& os, const mint& m) {os << m.val; return os;}
    friend std::istream& operator>>(std::istream& is, mint& m) {is >> m.val; return is;}
    operator size_t() const {return val;}
};
bool operator ==(ll a, const mint& b) {return a == b.val;}
bool operator !=(ll a, const mint& b) {return a != b.val;}
bool operator >(ll a, const mint& b) {return a > b.val;}
bool operator <(ll a, const mint& b) {return a < b.val;}
mint operator +(ll a, const mint& b) {ll ret = a + b.val; while(ret >= mod) {ret -= mod;} return mint(ret);}
mint operator -(ll a, const mint& b) {ll ret = a - b.val; while(ret < 0) {ret += mod;} return mint(ret);}
mint operator *(ll a, const mint& b) {return mint((a * b.val) % mod);}
mint operator /(ll a, const mint& b) {return mint((a / b.val) % mod);}
mint operator %(ll a, const mint& b) {return mint(a % b.val);}

ll calc_ans(vector<ll>& a, int n) {
    vector<ll> pfx(n);
    for(int i = 0; i < n; i++){
        pfx[i] = a[i];
        if(i != 0){
            pfx[i] += pfx[i - 1];
        }
    }
    ll cmax = abs(a[0]);
    for(int i = 1; i < n; i++){
        cmax = max(abs(cmax + a[i]), abs(pfx[i - 1] + a[i]));
    }
    return cmax;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<ll> pfx(n + 1, 0), sfx(n + 1, 0);
        vector<mint> pfx_ways(n + 1, 0);
        pfx_ways[0] = 1;
        for(int i = 1; i <= n; i++){
            pfx[i] = pfx[i - 1] + a[i - 1];
            pfx_ways[i] = pfx_ways[i - 1];
            if(pfx[i] >= 0){
                pfx_ways[i] *= 2;
            }
        }
        for(int i = n - 1; i >= 0; i--){
            sfx[i] = sfx[i + 1] + a[i];
        }
        ll cmax = calc_ans(a, n);
        mint ans = 0;
        if(sfx[0] == cmax) {
            ans = mint(2).pow(n);
        }
        else {
            for(int i = 1; i <= n; i++){
                if(abs(pfx[i]) + sfx[i] == cmax) {
                    ans += pfx_ways[i] * mint(2).pow(n - i);
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}