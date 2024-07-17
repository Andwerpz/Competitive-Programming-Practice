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
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1794E

//If we can compute for a node, some hash of the distances to all other nodes, then we can easily check if the tree
//can be labeled from that node by comparing the hash to the hash of the array. 

//Let p be some prime number, and c[i] be the count of nodes of distance i from node x. Then, our hash for x is 
//going to be sum(c[i] * p^i) for all i. 

//we can compute the hash for all nodes in O(n) time. First, root the tree arbitrarily and compute the hash for every
//subtree. It should be pretty obvious how to do this in O(n) time. Next, to compute the rest of the hash for each node,
//we can simply do a second pass. 

//note that the problem says that we get 1 wildcard label. All we have to do to check a node is see if the difference
//between the node hash and array hash correspond to a power of p less than n - 1. If it does, then the node is good. 

ll mod = 1e9 + 7;
ll pr1 = 71, pr2 = 2;
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
typedef pair<mint, mint> pmm;

void calc_subt_hash(int cur, int p, vvi& c, vector<pmm>& subt) {
    subt[cur] = {1, 1};
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        calc_subt_hash(next, cur, c, subt);
        subt[cur].first += subt[next].first * pr1;
        subt[cur].second += subt[next].second * pr2;
    }
}

void calc_ans(int cur, int p, vvi& c, vector<pmm>& subt, set<pmm>& ppow, pmm arr_hash, pmm par_hash, vi& ans) {
    pmm tree_hash = subt[cur];
    if(p != -1){
        tree_hash.first += (par_hash.first - subt[cur].first * pr1) * pr1;
        tree_hash.second += (par_hash.second - subt[cur].second * pr2) * pr2;
    }
    pmm diff = {tree_hash.first - arr_hash.first, tree_hash.second - arr_hash.second};
    if(ppow.count(diff)) {
        ans.push_back(cur);
    }
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        calc_ans(next, cur, c, subt, ppow, arr_hash, tree_hash, ans);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi a(n - 1);
    for(int i = 0; i < n - 1; i++){
        cin >> a[i];
    }
    vvi c(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    pmm ahash = {0, 0};
    for(int i = 0; i < a.size(); i++){
        ahash.first += mint(pr1).pow(a[i]);
        ahash.second += mint(pr2).pow(a[i]);
    }
    set<pair<mint, mint>> ppow;
    for(int i = 0; i < n; i++){
        ppow.insert({mint(pr1).pow(i), mint(pr2).pow(i)});
    }
    vector<pmm> subt(n);
    calc_subt_hash(0, -1, c, subt);
    vi ans(0);
    calc_ans(0, -1, c, subt, ppow, ahash, {0, 0}, ans);
    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] + 1 << " \n"[i == n - 1];
    }
    
    return 0;
}