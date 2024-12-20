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

//AtCoder - ARC124E

//first, how can we count the total amount of unique `x`? Let `c_i` be the amount of balls that the `i`th 
//person is handing to the `i + 1`th person. If `min(c_i) != 0`, then we can create an identical result by 
//subtracting 1 from every element. So the amount of unique results `x` is `\prod (a_i + 1) - \prod a_i`

//`\prod_{i = 1}^{N} x_i` is simply the number of ways to choose a ball from every person after all the 
//exchanges are done. So if we can enumerate the number of ways to choose over all sequences `c` where the minimum
//is `0`, then we can solve the problem. 

//to enumerate, we can do a dp that will run in linear time. The idea is that we'll consider how many ways
//are there to pick balls from the first `i` people. When picking the ball from the `i`th person, we'll have
//to consider that the ball can come from either person `i` originally, or person `i - 1`. So, we'll have
//to have another state keeping track of where the ball came from. Finally, we'll have to have a state
//keeping track of where the ball from the first person came from, either from person `1` or person `n`.

//so dp[i][j][k] = number of ways to pick balls that originally came from the first `i` people where
//j = whether or not the ball belonging to person `i` came from person `i - 1`
//k = whether or not the ball belonging to person `1` came from person `n`
//the final answer is dp[n][0][0] + dp[n][1][1]. dp[n][0][1] and dp[n][1][0] are contradictory states.

//Transitions are quite tricky. There are 4 of them:
//dp[i][j][0] -> dp[i + 1][j][0] : 
//i -> i and i + 1 -> i + 1. This means that we only need to pick the ball for person i. For given c[i], there are
//a[i] - c[i] ways to do this. Since we try all values of c[i], we can just multiply by sum 
//(a[i] - 0) + (a[i] - 1) + (a[i] - 2) + ... + (a[i] - a[i]), or a[i] * (a[i] + 1) - a[i] * (a[i] + 1) / 2

//dp[i][j][0] -> dp[i + 1][j][1] : 
//i -> i and i -> i + 1. This means that both i and i + 1 balls come originally from person i, so there are 
//(a[i] - c[i]) * c[i] ways to do this. Once again, we can derive a sequence, 
//a[i] * (a[i] + 1) * a[i] / 2 - a[i] * (a[i] + 1) * (2 * a[i] + 1) / 6

//dp[i][j][1] -> dp[i + 1][j][0] : 
//i - 1 -> i and i + 1 -> i + 1. Since we're choosing balls to go to i, we don't have any choices to make right
//now, so there is only 1 way to assign for a given c[i]. So there are a[i] + 1 ways to assign in total. 

//dp[i][j][1] -> dp[i + 1][j][1] : 
//i - 1 -> i and i -> i + 1. The only ball we need to assign right now is the one going to i + 1, and there
//are c[i] ways to do so, so in total there are a[i] * (a[i] + 1) / 2 ways. 

//in the end, since we want to fix the min value of c[i] to be 0, we can solve for both ranges of c being 
//[0, a[i]] and [1, a[i]], and take the difference. 

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

mint solve(int n, vm& a, int m) {
    //dp[i][j][k] = number of ways to choose from the first i buckets where
    //j tells us if the 0th ball has been taken from bucket 0 or n - 1
    //k tells us if the ith ball has been taken from bucket i or i - 1 
    //m is the minimum value of c[i]
    vector<vvm> dp(n + 1, vvm(2, vm(2, 0)));
    dp[0][0][0] = 1;
    dp[0][1][1] = 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 2; j++){
            dp[i + 1][j][0] += dp[i][j][0] * (a[i] * (a[i] + 1 - m) - a[i] * (a[i] + 1).inv_divide(2));
            dp[i + 1][j][1] += dp[i][j][0] * (a[i] * (a[i] + 1) * a[i].inv_divide(2) - a[i] * (a[i] + 1) * (2 * a[i] + 1).inv_divide(6));
            dp[i + 1][j][0] += dp[i][j][1] * (a[i] + 1 - m);
            dp[i + 1][j][1] += dp[i][j][1] * (a[i] * (a[i] + 1).inv_divide(2));
        }
    }
    return dp[n][0][0] + dp[n][1][1];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vm a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    mint ans = solve(n, a, 0) - solve(n, a, 1);
    cout << ans << "\n";
    
    return 0;
}