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

//AtCoder - ARC108F

//got right idea, just took a while to figure out the details I was missing. 

//Let A and B be the endpoints of some diameter in the tree. If A and B are the same color, then the 
//niceness will always be equal to the diameter, so there are 2^(n - 1) ways for this to happen. 

//Otherwise, we can fix A and B to be different colors (i'll fix A to be white and B to be black). 
//Consider counting the number of ways to paint the tree with niceness at most d. Any node with greater than 
//d distance from A must be black, and any node with greater than d distance away from B must be white. 
//The remaining nodes can be colored arbitrarily, so if there are k of them, that's 2^k ways. 
//By taking differences, we can compute how many colorings have exactly d niceness, and therefore compute
//the sum of nicenesses. 

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

pii dfs(int cur, int p, vvi& c) {
    pii ans = {cur, -1};
    for(int x : c[cur]) {
        if(x != p) {
            pii next = dfs(x, cur, c);
            if(next.second > ans.second) ans = next;
        }
    }
    ans.second ++;
    return ans;
};

void dfs_d(int cur, int p, vvi& c, vi& d){
    for(int x : c[cur]) if(x != p) d[x] = d[cur] + 1, dfs_d(x, cur, c, d);
}

pii find_diam(vvi& c){
    int a = dfs(0, -1, c).first;
    int b = dfs(a, -1, c).first;
    return {a, b};
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vvi c(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --, v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    pii d = find_diam(c);
    mint ans = 0;
    int dlen = dfs(d.first, -1, c).second;
    //diameter endpoints are same color
    ans += mint(2).pow(n - 1) * dlen;
    //diameter endpoints are different color
    vi dw(n, 0), db(n, 0), mdc(n, 0);
    dfs_d(d.first, -1, c, dw), dfs_d(d.second, -1, c, db);
    vb eq(n, false);
    int mnn = 0;
    for(int i = 0; i < n; i++){
        if(i == d.first || i == d.second) continue;
        mdc[max(dw[i], db[i])] ++;
        if(dw[i] == db[i]) eq[dw[i]] = true;
        mnn = max(mnn, min(dw[i], db[i]));
    }
    int active = n - 2;
    mint wcnt = 0;
    for(int i = dlen; i >= dlen / 2; i--){
        int tcnt = mdc[i];
        mint inc = mint(2).pow(active); //arbitrarily color unfixed nodes
        if(!eq[i]) inc -= mint(2).pow(active - tcnt);  //disregard any combination that improperly colors
        wcnt += inc * 2;
        inc *= max(i, mnn);
        ans += inc * 2;
        active -= tcnt;
        if(eq[i]) break;   //impossible to have less niceness
    }
    //edge case
    if(dlen % 2) {
        wcnt += 2, ans += 2 * max(dlen / 2, mnn);
    }
    assert(wcnt * 2 == mint(2).pow(n));
    cout << ans << "\n";
    
    return 0;
}