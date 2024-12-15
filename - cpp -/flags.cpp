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

//Codeforces - 93D

//pattern recognition forces

//compute the first 20 or so elements of the sequence using dp: dp[i][j][k] = number of flags of length i ending in
//colors j and k. 

//then, remove duplicates due to symmetry. To do so, note that palindromes are not double counted, so we want to
//add them back in so we can divide everything by 2. Flags of even length cannot be palindromes, so we can go ahead
//and divide them by 2, but flags of odd length can be palindromes. We can construct any palindrome by taking a flag and
//reversing then appending it onto itself. 

//you'll notice a pattern: all even length flags just multiply by 3 from the previous even length flag, and the uncorrected
//counts for odd length flags also exhibit the same pattern, except for length 1. 

//just replicate the pattern seen, and you'll get AC

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

//first n even sizes
mint calc_even(ll n){
    return (mint(3).pow(n) - 1).inv_divide(2) * 4;
}

//first n odd sizes
mint calc_odd(ll n){
    if(n == 0) return 0;
    mint ans = (mint(3).pow(n - 1) - 1).inv_divide(2) * 14;
    // cout << "S1 : " << ans << "\n";
    //account for doublecounting
    ans += calc_even(n / 2) * 2;    //3, 7, 11, ...
    ans += (mint(3).pow((n - 1) / 2) - 1).inv_divide(2) * 14;   //5, 9, 13, ...
    // cout << "S2 : " << ans << "\n";
    ans = ans.inv_divide(2);
    ans += 4;   //length = 1
    // cout << "CALC ODD : " << n << " " << ans << "\n";
    return ans;
}

mint solve(ll l, ll r) {    //[l, r)
    mint ans = 0;
    //evens
    ans += calc_even((r - 1) / 2) - calc_even((l - 1) / 2); 
    //odds
    ans += calc_odd(r / 2) - calc_odd(l / 2);
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll l, r;
    cin >> l >> r;
    r ++;
    cout << solve(l, r) << "\n";

    // int n;
    // cin >> n;
    // //W : 0, B : 1, Y : 2, R : 3
    // int W = 0, B = 1, Y = 2, R = 3;
    // vector<vvl> dp(n + 1, vvl(4, vl(4, 0)));
    // dp[2][W][B] = 1;
    // dp[2][B][W] = 1;
    // dp[2][W][R] = 1;
    // dp[2][R][W] = 1;
    // dp[2][Y][B] = 1;
    // dp[2][B][Y] = 1;
    // dp[2][Y][R] = 1;
    // dp[2][R][Y] = 1;
    // for(int i = 2; i < n; i++){
    //     for(int j = 0; j < 4; j++){
    //         for(int k = 0; k < 4; k++){
    //             for(int l = 0; l < 4; l++){
    //                 if(l == k) continue;
    //                 if((l == W && k == Y) || (l == Y && k == W)) continue;
    //                 if((l == B && k == R) || (l == R && k == B)) continue;
    //                 if(j == B && k == W && l == R) continue;
    //                 if(j == R && k == W && l == B) continue;
    //                 dp[i + 1][k][l] += dp[i][j][k];
    //             }
    //         }
    //     }
    // }
    // vl dps(n + 1, 0), odps(n + 1, 0);
    // dps[1] = 4;
    // for(int i = 2; i <= n; i++){
    //     for(int j = 0; j < 4; j++){
    //         for(int k = 0; k < 4; k++){
    //             dps[i] += dp[i][j][k];
    //         }
    //     }
    //     odps[i] = dps[i];
    //     cout << "OLD DPS : " << i << " " << odps[i] << "\n";
    //     if(i % 2 == 1){
    //         dps[i] += odps[i / 2 + 1];   //doublecount symmetrical flags
    //     }
    //     dps[i] /= 2;
    // }
    // for(int i = 1; i <= n; i++){
    //     cout << "DPS : " << i << " " << dps[i] << "\n";
    // }    
    // for(int i = 2; i <= n; i += 2){
    //     cout << "DIFF : " << dps[i] - dps[i - 1] << "\n";
    // }
    
    return 0;
}