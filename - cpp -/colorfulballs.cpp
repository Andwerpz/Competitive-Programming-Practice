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

//AtCoder - AGC12D

//Build a graph with n nodes, the ith node representing the ith ball. Let there be an edge (u, v) if we are able
//to swap balls u and v. Observe that if some node S is connected to T, then through some sequence of swaps, we 
//are able to swap just S and T with no side effects. Therefore, we can freely permute every connected component
//and counting the number of ways just boils down to counting the number of ways for each component, then 
//multiplying them together. 

//The issue lies in finding the connected components, as there can potentially be around n^2 edges. However
//note that we only are interested in the connected components, so we potentially only need to evaulate around
//order n edges. 

//First of all, edges between nodes of the same color are easy. We just need to consider the ball with minimum 
//weight for each color against all other balls. If two balls of the same color can swap, and the minimum is not
//among them, then we can always replace one of them with the minimum. 

//Edges between nodes of different colors are trickier. We can first consider the minimum overall weight ball
//against all other balls of different colors, but then that won't capture edges from other balls to the 
//minimum weight balls color. We actually only need to consider one more ball, the minimum weight ball that is
//not of the color of the actual overall minimum weight ball. 

struct DSU {
    int N;
    vector<int> dsu, sz;

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
        dsu[rb] = ra;
        sz[ra] += sz[rb];
        return true;
    }
};

struct mint;
typedef vector<mint> vm;
typedef vector<vector<mint>> vvm;
typedef pair<mint, mint> pmm;

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

vector<mint> fac;
void fac_init(int N) {
    fac = vector<mint>(N);
    fac[0] = 1;
    for(int i = 1; i < N; i++){
        fac[i] = fac[i - 1] * i;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, x, y;
    cin >> n >> x >> y;
    vector<pii> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].second >> a[i].first;
        a[i].second --;
    }
    sort(a.begin(), a.end());
    DSU dsu(n);
    vi cmin(n, -1), cind(n, -1);
    for(int i = 0; i < n; i++){
        if(cind[a[i].second] == -1) cind[a[i].second] = i, cmin[a[i].second] = a[i].first;
        if(cmin[a[i].second] + a[i].first <= x) dsu.unify(cind[a[i].second], i);
    }
    int smin = -1;
    for(int i = 0; i < n; i++){
        if(smin == -1 && a[i].second != a[0].second) smin = i;
        if(a[i].second != a[0].second && a[i].first + a[0].first <= y) dsu.unify(0, i);
        if(smin != -1 && a[i].second != a[smin].second && a[i].first + a[smin].first <= y) dsu.unify(smin, i);
    }
    for(int i = 0; i < n; i++){
        if(smin != -1 && a[i].second != a[smin].second && a[i].first + a[smin].first <= y) dsu.unify(smin, i);
    }
    fac_init(1e6);
    mint ans = 1;
    vvi g(n);
    for(int i = 0; i < n; i++) g[dsu.find(i)].push_back(i);
    for(int i = 0; i < g.size(); i++){
        map<int, int> f;
        int tot = 0;
        for(int _x : g[i]) f[a[_x].second] ++, tot ++;
        ans *= fac[tot];
        for(auto j = f.begin(); j != f.end(); j++){
            ans = ans.inv_divide(fac[j->second]);
        }
    }
    cout << ans << "\n";
    
    return 0;
}