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

struct mint;
typedef vector<mint> vm;
typedef vector<vector<mint>> vvm;
typedef pair<mint, mint> pmm;

const ll mod = 998244353;
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

mint gcd(mint a, mint b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

vector<mint> fac;
map<pair<mint, mint>, mint> nckdp;
void fac_init(int N) {
    fac = vector<mint>(N);
    fac[0] = 1;
    for(int i = 1; i < N; i++){
        fac[i] = fac[i - 1] * i;
    }
}

//n >= k
mint nck(mint n, mint k) {
    if(nckdp.find({n, k}) != nckdp.end()) {
        return nckdp.find({n, k}) -> second;
    }
    mint ans = fac[n].inv_divide(fac[k] * fac[n - k]);
    nckdp.insert({{n, k}, ans});
    return ans;
}

//a to b
mint calc_lattice(pii a, pii b) {
    if(a.first > b.first || a.second > b.second) return 0;
    return nck(b.first - a.first + b.second - a.second, b.first - a.first);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    fac_init(1e6);
    int t;
    cin >> t;
    while(t--) {
        ll n, m, _k;
        cin >> n >> m >> _k;
        vector<pii> a(_k);
        for(int i = 0; i < _k; i++){
            cin >> a[i].first >> a[i].second;
            a[i].first = n - a[i].first;
            a[i].second = m - a[i].second;
        }
        //figure out number of pairwise paths between points without touching any other points
        sort(a.begin(), a.end(), [](pii a, pii b) -> bool {
            return a.first + a.second < b.first + b.second;
        });
        vvm lp(_k, vm(_k, 0));
        for(int i = 0; i < _k; i++){
            for(int j = 0; j < _k; j++){
                lp[i][j] = calc_lattice(a[i], a[j]);
            }
        }
        vvm c(_k, vm(_k, 0));
        for(int i = 0; i < _k; i++){
            for(int j = i - 1; j >= 0; j--){
                if(a[j].first > a[i].first || a[j].second > a[i].second) continue;
                c[j][i] = lp[j][i];
                for(int k = j + 1; k < i; k++){
                    c[j][i] -= c[j][k] * lp[k][i];
                }
            }
        }
        vm c0(_k, 0);   //from 0
        vm cn(_k, 0);   //to n
        for(int i = 0; i < _k; i++){
            c0[i] = calc_lattice({0, 0}, a[i]);
            for(int j = 0; j < i; j++){
                c0[i] -= c0[j] * lp[j][i];
            }
        }
        for(int i = _k - 1; i >= 0; i--){
            cn[i] = calc_lattice(a[i], {n, m});
            for(int j = i + 1; j < _k; j++){
                cn[i] -= c[i][j] * calc_lattice(a[j], {n, m});
            }
        }
        vm dp(_k, 0);   //sum over all paths leading to this point
        for(int i = 0; i < _k; i++){
            dp[i] = c0[i] * (2 * a[i].first + a[i].second);
            for(int j = 0; j < i; j++){
                int dr = a[i].first - a[j].first;
                int dc = a[i].second - a[j].second;
                dp[i] += c[j][i] * (dp[j] * 2 + (dr * 2 + dc) * calc_lattice({0, 0}, a[j]));
            }
        }
        //compute number of paths that touch no royal decrees
        mint ans = nck(n + m, n);
        for(int i = 0; i < _k; i++){
            ans -= c0[i] * calc_lattice(a[i], {n, m});
        }
        ans *= (2 * n + m);
        for(int i = 0; i < _k; i++){
            int dr = n - a[i].first;
            int dc = m - a[i].second;
            ans += cn[i] * (dp[i] * 2 + (dr * 2 + dc) * calc_lattice({0, 0}, a[i]));
        }
        // cout << "INIT ANS : " << ans << "\n";
        ans = ans.inv_divide(calc_lattice({0, 0}, {n, m}));
        cout << ans << "\n";
    }
    
    return 0;
}