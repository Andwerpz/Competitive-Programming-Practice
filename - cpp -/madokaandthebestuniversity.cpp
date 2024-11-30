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
typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1717E

//just need to reduce the given summation using mobius inversion and euler totient. 
//my soln actually went the long way around, the editorial has a much more straightforwards
//(but much more insightful) derivation

vector<ll> totient;
void calc_totient(int n) {
    totient = vector<ll>(n + 1, 0);
    for (int i = 0; i <= n; i++)
        totient[i] = i;

    for (int i = 2; i <= n; i++) {
        if (totient[i] == i) {
            for (int j = i; j <= n; j += i)
                totient[j] -= totient[j] / i;
        }
    }
}

vector<ll> mobius;
void calc_mobius(int n) {
    mobius = vector<ll>(n + 1, 0);
    mobius[1] = 1;
    vector<bool> c(n + 1, false);
    vector<ll> p(0);
    for(int i = 2; i <= n; i++){
        if(!c[i]) {
            p.push_back(i);
            mobius[i] = -1;
        }
        for(int j = 0; j < p.size() && i * p[j] <= n; j++){
            c[i * p[j]] = true;
            if(i % p[j] == 0){
                mobius[i * p[j]] = 0;
                break;
            }
            else {
                mobius[i * p[j]] = mobius[i] * mobius[p[j]];
            }
        }
    }
}

struct mint;
typedef vector<mint> vm;
typedef vector<vector<mint>> vvm;
typedef pair<mint, mint> pmm;
vector<mint> fac;
map<pair<mint, mint>, mint> nckdp;

const ll mod = 1e9 + 7;
struct mint {
    ll val; //this should always be in range [0, mod)
    mint(ll _val = 0) {val = _val; if(val < 0) val = mod + (val % mod);}
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    calc_totient(1e5 + 5);
    calc_mobius(1e5 + 5);
    vvl div(1e5 + 5);
    for(int i = 1; i < div.size(); i++){
        for(int j = i; j < div.size(); j += i){
            div[j].push_back(i);
        }
    }
    int n;
    cin >> n;
    //precompute f(n) = \sum_{i = 1}^{n - 1} gcd(i, n - i)
    vl f(n + 1, 0);
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < div[i].size(); j++){
            f[i] += totient[div[i][j]] * i / div[i][j];
        }
        f[i] -= i;
    }
    mint ans = 0;
    for(int _k = 0; _k < div[n].size(); _k++){
        ll k = div[n][_k];
        for(int _d = 0; _d < div[n / k].size(); _d++){
            ll d = div[n / k][_d];
            for(ll a = 1; a <= n / (k * d) - 2; a++){
                ans += mint(k) * mobius[d] * d * d * a * f[n / (k * d) - a];
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}