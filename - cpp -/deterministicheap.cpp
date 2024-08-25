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

//Codeforces - 2001 E1

//this solves the easy version in O(n^3)

//my idea is to compute the number of trees via dp. However, it is not very straight forwards as
//a tree can either be a max tree, or a non-max tree. A max tree is a tree where the max path will go through,
//and non-max trees are all other trees. 

//let dp[i][j] = number of ways to build a non max subtree where
//i = height of the tree
//j = number of operations in the subtree. 
//dp_mx[i][j] is defined similarly, but for max subtrees. 
//of course, dp_mx[n - 1][k] is our answer. 

//for base cases, dp[0][j] and dp_mx[0][j] = 1, as no matter how many operations you have, you can only put it
//onto one node. 

//dp[i][j] = sum(dp[i - 1][x] * dp[i - 1][y]) over all ordered pairs (x, y) where x + y <= j. 
//dp_mx[i][j] = sum(dp_mx[i - 1][x] * dp[i - 1][y]) * 2 over all ordered pairs (x, y) where x + y <= j, and 
//y < x. * 2 because the path can go to either the left or right subtree, and y < x because the value on the
//max subtree needs to be greater than the value on the non-max subtree. 

//If we were to implement this naively, then we would get a O(n^4) algorithm. To remove a factor of n, 
//we can get rid of having to loop over y by computing prefix sums of the previous dp layer. 

struct mint;
typedef vector<mint> vm;
typedef vector<vector<mint>> vvm;
typedef pair<mint, mint> pmm;
vector<mint> fac;
map<pair<mint, mint>, mint> nckdp;

ll mod = 1e9 + 7;
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
        int n, k;
        cin >> n >> k >> mod;
        vvb v(n + 1, vb(k + 1, false));
        //dp[i][j] = nr ways to fill tree where
        //i = nr layers in tree
        //j = nr operations 
        vvm dp_mx(n, vm(k + 1, 0)), dp(n, vm(k + 1, 0));
        for(int i = 0; i <= k; i++){
            dp[0][i] = 1;
            dp_mx[0][i] = 1;
        }
        for(int i = 1; i < n; i++){
            vm pfx(k + 1, 0);
            pfx[0] = dp[i - 1][0];
            for(int j = 1; j < pfx.size(); j++){
                pfx[j] = pfx[j - 1] + dp[i - 1][j];
            }
            //solve no-mx
            for(int j = 0; j <= k; j++){    
                for(int lm = 0; lm <= j; lm++){ //we put lm moves in the left subtree
                    dp[i][j] += dp[i - 1][lm] * pfx[j - lm];
                }
            }
            //solve mx
            for(int j = 0; j <= k; j++){
                for(int lm = 1; lm <= j; lm++){
                    //(ways to do left mx subt) * (ways to do right non-mx subt)
                    dp_mx[i][j] += dp_mx[i - 1][lm] * pfx[min(lm - 1, j - lm)];
                }
                dp_mx[i][j] *= 2;   //can do it on right subtree as well. 
            }
        }
        cout << dp_mx[n - 1][k] << "\n";
    }
    
    return 0;
}