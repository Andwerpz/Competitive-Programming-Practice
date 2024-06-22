#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1575K

//we don't really care about the number of colors, just the number of 'free cells'. A free cell is a cell for which we can
//freely choose it's color. If the number of free cells is x, then the answer is simply k^x. 

//notice that if a == b, then every cell on the board is a free cell. If a != b, then we can freely determine one
//of the patches, but the other patch is determined by the first one, so x = n * m - r * c. 

struct mint;
vector<mint> fac;
map<pair<mint, mint>, mint> nckdp;

ll mod = 1e9 + 7;
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ll n, m, k, r, c;
    cin >> n >> m >> k >> r >> c;
    ll ax1, ay1, bx1, by1;
    cin >> ax1 >> ay1 >> bx1 >> by1;
    ll pow = n * m;
    //adjust pow by regions
    if(ax1 != bx1 || ay1 != by1) {
        pow -= r * c;
    }
    mint ans = mint(k).pow(pow);
    cout << ans << "\n";
    
    return 0;
}