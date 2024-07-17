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

//Codeforces - 1977D

//my thoughts on solving the problem: 

// - have a 'target' pattern, and see what modifications are required for each column to match the target. 
//   Answer is the modification with the highest amount of columns agreeing among all target patterns.  

// - how to quickly compute answer across all columns and target patterns? Use hashing. For a given target 
//   pattern and column, you can come up with a hash for the required modification in constant time with some precalculation. 

// - to reverse engineer the modification from the hash, for each hash we can store the target pattern 
//   and the column that created the hash. 

//had to use 2 primes since there were some nasty testcases breaking my hash D:

ll mod = 1e9 + 7;
ll pr1 = 2, pr2 = 71;
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
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vvi g(n, vi(m));
        for(int i = 0; i < n; i++){
            string line;
            cin >> line;
            for(int j = 0; j < m; j++){
                g[i][j] = line[j] - '0';
            }
        }
        //for each column, generate prefix hash
        vector<vector<mint>> h1(n + 1, vector<mint>(m, 0)), h2(n + 1, vector<mint>(m, 0));
        for(int i = 0; i < m; i++){
            for(int j = 1; j <= n; j++){
                h1[j][i] = h1[j - 1][i] * pr1 + g[j - 1][i];
                h2[j][i] = h2[j - 1][i] * pr2 + g[j - 1][i];
            }
        }
        map<pll, int> cnt;
        map<pll, pii> rev;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                //testing pattern i on column j
                mint hash1 = h1[n][j];
                if(g[i][j]){
                    hash1 -= mint(pr1).pow(n - i - 1);
                }
                else {
                    hash1 += mint(pr1).pow(n - i - 1);
                }
                mint hash2 = h2[n][j];
                if(g[i][j]){
                    hash2 -= mint(pr2).pow(n - i - 1);
                }
                else {
                    hash2 += mint(pr2).pow(n - i - 1);
                }
                cnt[{hash1, hash2}] ++;
                rev[{hash1, hash2}] = {i, j};
            }
        }
        pll ans; int mxcnt = 0;
        for(auto i = cnt.begin(); i != cnt.end(); i++){
            if(i->second > mxcnt) {
                mxcnt = i->second;
                ans = i->first;
            }
        }
        cout << mxcnt << "\n";
        int pat = rev[ans].first;
        int col = rev[ans].second;
        for(int i = 0; i < n; i++){
            cout << (g[i][col] ^ (i == pat));
        }
        cout << "\n";
    }
    
    
    return 0;
}