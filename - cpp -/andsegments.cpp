#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//Codeforces - 1327F

//2ptr dp

//first thing to observe is that we can actually handle each bit seperately. Just compute the amount of ways to set each 
//bit for all numbers, and then multiply everything together. 

//for some specific bit, consider some restriction [l, r], x. If x contains the bit, then all numbers in [l, r] must also 
//contain it. If x does not contain it, then at least one number in [l, r] has to not contain it. I'll call these
//type A and type B restrictions respectively. 

//we can actually solve this in linear time using dp. dp[i] = nr sequences of length i that end on '0'. For any i that's covered
//by a type A restriction, we can automatically set dp[i] = 0. Otherwise, we can consider all j < i to transition to dp[i].

//Transition from j -> i will be placing '1's until you get to i, then you place a '0'. 
//What j can transition to i? As long as [j, i] doesn't completely contain a type B restriction, then you can transition. 
//Notice that the minimum valid j will monotonically increase as i increases, so we can keep track of the sum of states that
//can transition to i using a second pointer. 

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m, k;
    cin >> n >> k >> m;
    //1 indexed
    vvi fix(k, vi(n + 2, 0)), minl(k, vi(n + 2, 0));
    for(int i = 0; i < m; i++){
        int l, r, x;
        cin >> l >> r >> x;
        r ++;
        for(int j = 0; j < k; j++) {
            if(x & (1 << j)) fix[j][l] ++, fix[j][r] --;
            else minl[j][r] = max(minl[j][r], l);
        }
    }
    for(int i = 0; i < k; i++){
        for(int j = 1; j <= n + 1; j++) fix[i][j] += fix[i][j - 1], minl[i][j] = max(minl[i][j], minl[i][j - 1]);
    }
    mint ans = 1;
    for(int i = 0; i < k; i++){
        //dp[i] = nr sequences of length i that end on a '0'
        vm dp(n + 2, 0);
        dp[0] = 1;
        int lptr = 0;
        mint psum = 1;
        for(int j = 1; j <= n + 1; j++){
            while(lptr < minl[i][j]) psum -= dp[lptr ++];
            if(!fix[i][j]) dp[j] = psum, psum *= 2;
        }
        ans *= dp[n + 1];
    }
    cout << ans << "\n";
    
    return 0;
}