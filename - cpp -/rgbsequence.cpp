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

//AtCoder - ARC74E

//dp[i][j][k] = nr ways where
//placed first i characters
//first character different from last placed is j characters away
//second character different from both others is k characters away
//so k > j

//to enforce constraints, we can just check them when they end. For different types of constraints, 
//(x = 1, 2, 3), we'll have to check them differently. 

//for x = 1, we only care about the smallest l for any r
//this is because any larger l will automatically be satisfied by the smaller l

//for x = 2, we care about both the smallest and largest l for a given r
//Since we want the range between the smaller and larger l to have exactly 2 unique elements, 
//we have to check against both

//for x = 3, we only care about the largest l for any r
//any smaller l will automatically be satisfied by the largest l. 

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
    
    int n, m;
    cin >> n >> m;
    vi ar(n + 1, -1), br(n + 1, 1e9), cr(n + 1, 1e9);
    vi br_mx(n + 1, -1), cr_mx(n + 1, -1);
    for(int i = 0; i < m; i++){
        int l, r, x;
        cin >> l >> r >> x;
        l --;
        if(x == 1) {
            ar[r] = max(ar[r], r - l);
        }
        else if(x == 2) {
            br[r] = min(br[r], r - l);
            br_mx[r] = max(br_mx[r], r - l);
        }
        else {
            cr[r] = min(cr[r], r - l);
            cr_mx[r] = max(cr_mx[r], r - l);
        }
    }
    //dp[i][j][k] = nr ways where
    //placed first i characters
    //first character different from last placed is j characters away
    //second character different from both others is k characters away
    //so k > j
    vector<vvm> dp(n + 1, vvm(n + 2, vm(n + 2, 0)));
    //base case. Can start with any character
    dp[1][n + 1][n + 1] = 3;
    for(int i = 1; i <= n; i++){
        //zero out any states that are invalid
        for(int j = 0; j < n + 2; j++){
            for(int k = 0; k < n + 2; k++){
                bool is_valid = true;
                if(ar[i] != -1) {
                    if(ar[i] >= j) is_valid = false;
                }
                if(br[i] != 1e9) { 
                    if(br_mx[i] >= k || br[i] < j) is_valid = false;
                }
                if(cr[i] != 1e9) {
                    if(cr[i] < k) is_valid = false;
                }
                if(!is_valid) {
                    dp[i][j][k] = 0;
                }
            }
        }
        if(i == n) break;
        //transitions
        for(int j = 0; j < n + 2; j++){
            for(int k = 0; k < n + 2; k++){
                if(j == n + 1) {
                    if(k == n + 1){ //only have 1 character so far
                        //continue using current character
                        dp[i + 1][n + 1][n + 1] += dp[i][j][k];
                        //use other character
                        dp[i + 1][2][n + 1] += dp[i][j][k];
                        //use second other character
                        dp[i + 1][2][n + 1] += dp[i][j][k];
                    }
                    continue;
                }
                if(k == n + 1){ //have two characters so far
                    //continue using current character
                    dp[i + 1][j + 1][n + 1] += dp[i][j][k];
                    //use first closest character
                    dp[i + 1][2][n + 1] += dp[i][j][k];
                    //use other character
                    dp[i + 1][2][j + 1] += dp[i][j][k];
                    continue;
                }
                if(k <= j) continue;    //second character cannot be farther away than first one
                //continue using current character
                dp[i + 1][j + 1][k + 1] += dp[i][j][k];
                //use first closest character
                dp[i + 1][2][k + 1] += dp[i][j][k];
                //use second closest character
                dp[i + 1][2][j + 1] += dp[i][j][k];
            }
        }
    }
    mint ans = 0;
    for(int i = 0; i < n + 2; i++){
        for(int j = 0; j < n + 2; j++){
            ans += dp[n][i][j];
        }
    }
    cout << ans << "\n";
    
    return 0;
}