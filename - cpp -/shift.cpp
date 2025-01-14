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

//AtCoder - AGC46C

//somehow this solution gets AC with 50ms, but by my analysis it's around n^4. Even removing the check for
//dp[i][j][k] == 0 and it only slows down to 130ms. 

//We can understand the operation better if we view the '1's as being separated by '0's into buckets. Then, the
//operation is pretty much: select some bucket, subtract 1 from it, and add 1 to any bucket to the left. 
//With this interpretation, it's pretty obvious that we'll need to use dp to solve this problem. 

//We can use this dp definition to solve the problem: dp[i][j][k] = number of ways to populate the first i buckets given
//that we have j '1's in debt, and k total operations performed. By '1' debt, I mean that we're able to place extra '1's 
//when we want, we just have to 'return' the '1's that we owe later by placing fewer '1's. 

//Transitions are as follows:
//dp[i][j][k] -> dp[i + 1][j][k] : do nothing
//dp[i][j][k] -> dp[i + 1][j + p][k + p] : 'borrow' p '1's from position i
//dp[i][j][k] -> dp[i + 1][j - p][k] : 'return' p '1's to position i

//We also have some other restrictions: for some i, we cannot return more than b[i] '1's, where b[i] is the amount of '1's 
//originally in the ith bucket. And, we cannot be borrowing more than sfx[i + 1] '1's at position i, where sfx[i + 1] is the 
//amount of '1's originally in buckets to the right of i. 

//Note that we have around n^3 states, and each transition looks like it will cost linear time, since we have to iterate 
//through all valid values of p. However, I believe that the constant factor will be so small that this solution will
//not TLE. 

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
    
    string s;
    cin >> s;
    int _k;
    cin >> _k;
    int n = 1;
    for(int i = 0; i < s.size(); i++){
        n += s[i] == '0';
    }
    vi a(n, 0), sfx(n + 1, 0);
    int ptr = 0;
    for(int i = 0; i < s.size(); i++){
        a[ptr] += s[i] == '1';
        ptr += s[i] == '0';
    }
    for(int i = n - 1; i >= 0; i--){
        sfx[i] = sfx[i + 1] + a[i];
    }
    int sum = s.size() - (n - 1);
    _k = min(_k, sum);
    vector<vvm> dp(n + 1, vvm(sum + 1, vm(_k + 1, 0)));
    dp[0][0][0] = 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= sum; j++){
            for(int k = 0; k <= _k; k++){
                if(dp[i][j][k] == 0) continue;
                //borrow. Can only have the next sfx amount borrowed
                for(int p = 1; j + p <= sfx[i + 1] && k + p <= _k; p++) {
                    dp[i + 1][j + p][k + p] += dp[i][j][k];
                }
                //return. Can only return as much as is in the current node
                for(int p = 1; j - p >= 0 && p <= a[i]; p++) {
                    dp[i + 1][j - p][k] += dp[i][j][k];
                }
                //do nothing
                dp[i + 1][j][k] += dp[i][j][k];
            }
        }
    }
    mint ans = 0;
    for(int i = 0; i <= _k; i++){
        ans += dp[n][0][i];
    }
    cout << ans << "\n";
    
    return 0;
}