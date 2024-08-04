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

//Codeforces - 1830C

//if we replace '(' with 1 and ')' with -1, then the following must be true about any RBS:
//1. the sum of elements must be 0
//2. all prefixes must have sum >= 0
//3. all suffixes must have sum <= 0

//note that if two segments intersect (not completely containing), then the intersection must 
//itself be a RBS. For example, we have two segments A and B intersecting like so:
//(the intersection is denoted by C)

//    |------A------|
//             |------B------|
//             |--C-|

//since C is a suffix of A, all of it's suffixes must have sum <= 0, and since it is a prefix of 
//B, all it's prefixes must have sum >= 0. These two conditions are enough to show that C must
//be a RBS. 

//Next, consider when A fully contains B:
//(X and Y are the leftover portions of A)

//   |--------A--------|
//   |---X---|--B--|-Y-|

//since the sum of B is 0, we can safely remove it without affecting any prefix or suffix sums. 
//Therefore, the concatenation of X and Y must be a RBS. 

//From here, I guessed that if the multiset of segments that cover some range is the same, then
//they should always form a RBS upon concatenation. We can use XOR hashing to identify all such 
//multisets, and a formula to quickly compute the number of RBS for a given length n. 

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

mint gcd(mint a, mint b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

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

//given that we choose n / 2 left brackets and n / 2 right brackets, 
//nck(n, n / 2) is the total amount of bracket sequences, and nck(n, n / 2 + 1) is the amount of bad sequences.
mint nr_rbs(int n){
    if(n == 0){
        return 1;
    }
    if(n % 2){
        return 0;
    }
    return nck(n, n / 2) - nck(n, n / 2 + 1);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    fac_init(1e6);
    int t;
    cin >> t;
    while(t--){
        srand(time(0));
        int n, k;
        cin >> n >> k;
        vector<pii> seg(k + 1);
        priority_queue<pii> q;
        for(int i = 0; i < k; i++){
            cin >> seg[i].first >> seg[i].second;
            seg[i].first --;
        }
        seg[k].first = 0;
        seg[k].second = n;
        vl hash(k + 1);
        for(int i = 0; i <= k; i++){
            hash[i] = rand() + (rand() << 16) + ((ll) rand() << 32) + ((ll) rand() << 48);
        }
        map<ll, int> m;
        for(int i = 0; i <= k; i++){
            q.push({-seg[i].first, i});
            q.push({-seg[i].second, i});
        }
        int prev = 0;
        ll hsum = 0;
        while(q.size() != 0){
            int next = -q.top().first;
            int ind = q.top().second;
            q.pop();
            int diff = next - prev;
            prev = next;
            m[hsum] += diff;
            hsum ^= hash[ind];
        }
        mint ans = 1;
        for(auto i = m.begin(); i != m.end(); i++){
            ans *= nr_rbs(i->second);
        }
        cout << ans << "\n";
    }
    
    return 0;
}