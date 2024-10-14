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

//Codeforces - 1943 D1 D2

//we can build any good array using the following operation:
//select some subarray [l, r], l < r, and add 1 to all elements in that range. Note that any operation that we can
//perform can be split into size 2 and 3 subarrays, so we can further refine it to: select any subarray of size 2 or 3, 
//and add 1 to all elements. 

//following this, we can find a necessary and sufficient condition for a good array:
//for any element a[i], a[i] <= a[i - 1] + a[i + 1]. Note that when we add 1 to a[i], then we must add 1 to at least 
//a[i - 1] or a[i + 1]. This shows that it's at least necessary, but I couldn't figure out how to prove that
//it's sufficient. Read the editorial for that. 

//for the easy version, it's sufficient to do some sort of naive dp to compute all arrays that satisfy the above
//condition. dp[i][j][k] = nr ways where
//i = amount of elements decided on
//j = a[i], k = a[i - 1]
//we'll just have to make sure that the first and last elements are both 0
//this should run in O(n^3). 

//for the hard version, we need to be more clever. Denote some index x as bad if a[x] > a[x - 1] + a[x + 1]. 
//Next, f(x) = set of all arrays such that x is bad. Then, the amount of bad arrays is simply
//|f(1) U f(2) U ... U f(n)|. Then, we can just subtract it from the total amount of arrays, (k + 1)^n, to get
//the number of good arrays. 

//To compute |f(1) U f(2) U ... U f(n)|, we need to use inclusion exclusion. We can actually use dp:
//dp[i][j][k] = nr ways where
//i = amount of elements decided on
//j = amount of sets currently unioned
//k = a[i]

//transitions will look like:
//dp[i][j][cur] += dp[i - 1][j][prev]. for all 0 <= prev <= k. This may create new bad elements, but for inclusion
//  exclusion, we don't really care. Note that |f(x) U f(y)| only must have x and y as bad elements, for every other 
//  element there is no restriction. 
//dp[i][j + 1][cur] += dp[i - 2][j][prev] * max(0, k - (cur + prev)). This will forcefully create a bad element
//  and we'll consider it as a union in our inclusion exclusion. 

//finally, we can optimize this down to O(n^2). First, note that we only really care about the parity of j, 
//so we can reduce the space down to n^2. Second, we can use prefix sums to handle the first and second type of
//transition, leading to O(1) average processing time per state. 

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
        //f(x, y, z) just means that a[x], a[y], and a[z] have to be bad. There are no restrictions placed
        //on any other element. 
        //i, nr bad elements unioned, cur element
        vector dp(n + 2, vvm(2, vm(k + 1, 0)));
        dp[0][0][0] = 1;
        for(int i = 1; i <= n + 1; i++){
            vvm pfx(2, vm(k + 2, 0));
            for(int ucnt = 0; ucnt <= 1; ucnt++){
                for(int cur = 1; cur <= k + 1; cur++){
                    pfx[ucnt][cur] = pfx[ucnt][cur - 1] + dp[i - 1][ucnt][cur - 1];
                }
            }
            //force next element
            if(i >= 2){
                for(int ucnt = 0; ucnt <= 1; ucnt++){
                    for(int prev = 0; prev <= k; prev++){
                        int amt = k - prev;
                        if(amt != 0){
                            dp[i][ucnt][amt - 1] += dp[i - 2][ucnt ^ 1][prev];
                        }
                    }
                    //first sum
                    for(int j = k - 1; j >= 0; j--){
                        dp[i][ucnt][j] += dp[i][ucnt][j + 1];
                    }
                    //second sum
                    for(int j = k - 1; j >= 0; j--){
                        dp[i][ucnt][j] += dp[i][ucnt][j + 1];
                    }
                }
            }
            //don't force next element
            for(int ucnt = 0; ucnt <= 1; ucnt++){
                for(int cur = 0; cur <= k; cur++){
                    dp[i][ucnt][cur] += pfx[ucnt][k + 1];
                }
            }
        }
        //consider inclusion exclusion
        mint ans = dp[n + 1][0][0] - dp[n + 1][1][0];
        cout << ans << "\n";


        //easy version sol. 
        // //i, cur elem, prev elem
        // vector dp(2, vvm(k + 1, vm(k + 1, 0)));
        // for(int i = 0; i <= k; i++){
        //     dp[0][i][0] = 1;
        // }
        // for(int i = 0; i < n; i++){
        //     for(int c = 0; c <= k; c++){
        //         for(int p = 0; p <= k; p++){
        //             dp[1][c][p] = 0;
        //         }
        //     }
        //     for(int c = 0; c <= k; c++){
        //         for(int p = 0; p <= k; p++){
        //             //have to maintain that prev + next >= cur
        //             int next = max(0, c - p);
        //             dp[1][next][c] += dp[0][c][p];
        //         }
        //     }
        //     for(int c = 0; c < k; c++){
        //         for(int p = 0; p <= k; p++){
        //             dp[1][c + 1][p] += dp[1][c][p];
        //         }
        //     }
        //     swap(dp[0], dp[1]);
        // }
        // mint ans = 0;
        // for(int i = 0; i <= k; i++){
        //     ans += dp[0][0][i];
        // }
        // cout << ans << "\n";
    }
    
    return 0;
}