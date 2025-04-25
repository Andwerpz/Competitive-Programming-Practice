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

//Kattis - allcolourings

//note that n, m <= 20. This implies that we can iterate over all subsets, which implies some sort of 
//inclusion-exclusion solution. 

//lets say that each edge can be bad if it's monochoromatic or good if it's not. We can classify graphs by the set of
//edges that are bad. lets say we fix some edges to be monochromatic, we can easily compute the number of graphs such
//that at least this set is monochromatic. Then, using basic inclusion exclusion, we can immediately get the answer for
//the number of graphs with no monochromatic edges. 

//to get the answer for any amount of monochromatic edges, we need to generalize the inclusion exclusion formula. 
//(i should probably know this general formula, or at least know how to derive it)
//let g(t) be the amount of colorings such that there are exactly t monochromatic edges. Let f(S) be the count 
//of colorings such that at least the edges in S are monochromatic, and F(t) be \sum_{|S| = t} f(S). Then,
//g(t) = \sum_{k = t}^{m} (-1)^{k - t} \binom{k}{t} F(k)

struct mint;
typedef vector<mint> vm;
typedef vector<vector<mint>> vvm;
typedef pair<mint, mint> pmm;

const ll mod = 1e9 + 9;
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

struct DSU {
    int N;
    vector<int> dsu, sz;

    DSU() {}
    DSU(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        this->sz = vector<int>(n, 1);
        for(int i = 0; i < n; i++){ //initialize roots
            dsu[i] = i;
        }
    }

    int find(int a) {
        if(dsu[a] == a) {
            return a;
        }
        return dsu[a] = find(dsu[a]);
    }

    int get_sz(int a){
        return sz[find(a)];
    }

    //ret true if updated something
    bool unify(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if(ra == rb) {
            return false;
        }
        if(sz[rb] > sz[ra]) swap(ra, rb);
        //merge rb into ra
        dsu[rb] = ra;
        sz[ra] += sz[rb];
        return true;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    fac_init(1e5);
    ll n, m, k;
    cin >> n >> m >> k;
    vector<pii> e(m);
    vm f(m + 1, 0);    //f[i] = sum of colorings s.t. has i or more bad edges
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u --, v --;
        e[i] = {u, v};
    }
    //fix which edges have to be bad: they must connect two nodes of the same color
    for(int i = 0; i < (1 << m); i++){
        // cout << "I : " << i << endl;
        int bcnt = 0;
        DSU dsu(n);
        int ncnt = n;
        for(int j = 0; j < m; j++) {
            if(!(i & (1 << j))) continue;
            // cout << "UNIFY : " << e[j].first << " " << e[j].second << endl;
            bcnt ++;
            ncnt -= dsu.unify(e[j].first, e[j].second);
        }
        // cout << "DONE DSU" << endl;
        f[bcnt] += mint(k).pow(ncnt);
        // cout << "FIX BAD : " << i << " " << ncnt << endl;
    }
    // cout << "F : ";
    // for(int i = 0; i <= m; i++) cout << f[i] << " ";
    // cout << "\n";
    //do inclusion exclusion
    vm ans(m + 1, 0);
    for(int i = 0; i <= m; i++){
        for(int j = 0; i + j <= m; j++) ans[i] += f[i + j] * nck(i + j, i) * (j % 2? -1 : 1);
    }
    for(int i = 0; i <= m; i++) cout << ans[i] << " ";
    cout << "\n";
    
    return 0;
}