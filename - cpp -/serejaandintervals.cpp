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

//Codeforces - 367E

//first observe that two segments cannot share a left or right boundary, as one of the segments 
//must contain the other in that case. 

//next, consider sorting all the intervals by left bound. Since all the intervals have to be different, we 
//can just count the number of sorted interval sequences and then multiply by n!
//Note that if we sort by the left bound, then the right bounds also have to be sorted strictly ascending. 

//So, this leads to a dp solution. dp[i][j][k] = number of ways where
//i = current value
//j = number of segments completely to the left
//k = number of segments i is inside of. 

//this runs in O(n^2 m), but note that if n > m, then the answer is always 0, so the actual runtime is at
//most O((nm)^(3/2)), or around 10^(7.5). 

//we can easily enforce the condition with x by forcing to place an element at position x. 

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m, x;
    cin >> n >> m >> x;
    if(n > m) {
        cout << "0\n";
        return 0;
    }
    //j = nr segments completely to left
    //k = nr segments inside of
    //j + k <= n
    vector<vvm> dp(2, vvm(n + 1, vm(n + 1, 0)));    
    dp[0][n][0] = 1;
    for(int i = 0; i <= m; i++){
        for(int j = 0; j <= n; j++){
            for(int k = 0; k <= n; k++){
                dp[1][j][k] = 0;
            }
        }
        for(int j = 0; j <= n; j++){
            for(int k = 0; j + k <= n; k++){
                if(i + 1 == x){
                    //forced to put an element here
                    if(j == 0) continue;
                    //start an element here
                    dp[1][j - 1][k + 1] += dp[0][j][k];
                    //start and end an element here
                    if(k != 0) dp[1][j - 1][k] += dp[0][j][k];
                }
                else {
                    //do nothing
                    dp[1][j][k] += dp[0][j][k];
                    //start an element here
                    if(j != 0) dp[1][j - 1][k + 1] += dp[0][j][k];
                    //end an element here
                    if(k != 0) dp[1][j][k - 1] += dp[0][j][k];
                    //start and end an element here
                    if(j != 0 && k != 0) dp[1][j - 1][k] += dp[0][j][k];
                }
            }
        }
        swap(dp[1], dp[0]);
    }
    mint ans = dp[0][0][0];
    for(int i = 1; i <= n; i++){
        ans *= i;
    }
    cout << ans << "\n";
    
    return 0;
}