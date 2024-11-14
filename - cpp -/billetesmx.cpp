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

//Codeforces - 2022 E1 E2

//lets say we have two arrays, X, Y. I claim that any valid grid satisfies a[i][j] = X[i] ^ Y[j] for some
//choice of X and Y. 

//intuitively this is because we can XOR any row or column with any value we wish, and the goodness
//of the grid will not be affected. This is because any rectangle affected by our operation will be
//affected exactly twice, cancelling out the effect. 

//we can also think of assigning some grid cell some value as setting the relationship between two
//elements of X and Y, so naturally we have n + m - 1 degrees of freedom, with each relationship
//taking away one degree of freedom. 

//so we can solve the problem like so: accumulate all relationships by doing one pass through the queries 
//using some sort of DSU. Then, determine the exact values in X and Y, by assigning an arbitrary value
//to one node in each component, and then doing BFS. 

//finally, we go through all the queries. If after a query the grid becomes inconsistent (we can easily
//check this by computing the XOR sum of corresponding X and Y), then the remaining answers become 0. 
//otherwise, the answer is always (2^30) ^ (nr dof). 

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
    
    int t;
    cin >> t;
    while(t--){
        int n, m, k, q;
        cin >> n >> m >> k >> q;
        DSU dsu(n + m);
        vector<vector<pii>> c(n + m);
        vector<pair<pii, int>> qu(k + q);
        vi f(k + q);
        int fcnt = n + m - 1;
        for(int i = 0; i < k + q; i++){
            int _r, _c, v;
            cin >> _r >> _c >> v;
            _r --;
            _c --;
            int a = _r;
            int b = n + _c;
            if(dsu.unify(a, b)) {
                c[a].push_back({b, v});
                c[b].push_back({a, v});
                fcnt --;
            }
            f[i] = fcnt;
            qu[i] = {{_r, _c}, v};
        }
        vi val(n + m, -1);
        for(int i = 0; i < n + m; i++){
            if(val[i] != -1){
                continue;
            }
            val[i] = 0;
            queue<int> s;
            s.push(i);
            while(s.size() != 0){
                int cur = s.front();
                s.pop();
                for(int j = 0; j < c[cur].size(); j++){
                    int next = c[cur][j].first;
                    int x = c[cur][j].second;
                    if(val[next] == -1){
                        val[next] = val[cur] ^ x;
                        s.push(next);
                    }
                }
            }
        }
        bool consistent = true;
        vm ans(k + q);
        for(int i = 0; i < k + q; i++){
            int _r = qu[i].first.first;
            int _c = qu[i].first.second;
            int v = qu[i].second;
            int a = _r;
            int b = n + _c;
            if((val[a] ^ val[b]) != v){
                consistent = false;
            }
            if(consistent){
                ans[i] = (mint(2).pow(30)).pow(f[i]);
            }
            else {
                ans[i] = 0;
            }
        }
        if(k == 0){
            cout << (mint(2).pow(30)).pow(n + m - 1) << "\n";
        }
        else {
            cout << ans[k - 1] << "\n";
        }
        for(int i = k; i < k + q; i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}