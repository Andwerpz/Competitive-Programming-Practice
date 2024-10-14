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

//Codeforces - 2025E

//for p1 to win, they need to win when only considering the trump suit (suit 1). Then, the extra
//cards from the trump suit can supplement the other suits. 

//so, for the trump suit, we'll generate the ways for p1 to win indexed by the amount of extra cards left over,
//and for the other suits, we'll count ways indexed by total amount of trump cards needed. 

//first part can be done with dp. Can consider cards from highest to lowest rank, and essentially counting 
//number of assignments such that every prefix has at least as many cards for p1 compared to p2. 

//second part can also be done with dp. First can consider 1 suit independently:
//dp[i][j][k] = nr ways given
//i = number of ranks considered
//j = amount of extra cards p1 has
//k = amount of trump cards needed

//at the end, the valid states are where j = 0, because we can't have any leftover cards from a non-trump suit.
//finally, we'll do dp using the values dp[m][0][k] generated.

struct mint;
typedef vector<mint> vm;
typedef vector<vector<mint>> vvm;
typedef pair<mint, mint> pmm;
vector<mint> fac;
map<pair<mint, mint>, mint> nckdp;

const ll mod = 998244353;
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
    
    int n, m;
    cin >> n >> m;
    vector<vvm> dp(2, vvm(m + 1, vm(m + 1, 0)));
    dp[0][0][0] = 1;
    //consider cards from highest to lowest rank
    for(int i = 0; i < m; i++){
        for(int j = 0; j <= m; j++){
            for(int k = 0; k <= m; k++){
                dp[1][j][k] = 0;
            }
        }
        for(int j = 0; j <= m; j++){
            for(int k = 0; k <= m; k++){
                //assign to p1
                if(j != m) {    //increase number of extra cards for p1
                    dp[1][j + 1][k] += dp[0][j][k];
                }
                //assign to p2
                if(j == 0){ //ran out of extra cards for p1
                    if(k != m){
                        dp[1][0][k + 1] += dp[0][0][k];
                    }
                }
                else {  //need to burn a p1 card
                    dp[1][j - 1][k] += dp[0][j][k];
                }
            }
        }
        swap(dp[0], dp[1]);
    }
    vvm dp2(n, vm(m + 1, 0));
    dp2[0][0] = 1;
    //i = number suits considered. Should only consider non-trump suits
    //j = amount of extra cards required
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j <= m; j++){
            //just try everything
            for(int k = 0; j + k <= m; k++){
                dp2[i + 1][j + k] += dp2[i][j] * dp[0][0][k];
            }
        }
    }
    //finally, consider the trump suit
    mint ans = 0;
    for(int i = 0; i <= m; i++){
        // cout << "TRUMP : " << dp[m][i][0] << "\n";
        ans += dp2[n - 1][i] * dp[0][i][0];
    }
    cout << ans << "\n";
    
    return 0;
}