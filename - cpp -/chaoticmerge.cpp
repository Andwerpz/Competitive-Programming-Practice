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

//Codeforces - 1499E

//how can we compute f(0, n, 0, m)? We can easily come up with an O(n^2) dp solution: dp[i][j][k] = number of ways to 
//create a chaotic merge of the first i characters of x, first j characters of y and k denotes the last character to be inserted. 
//Then, the answer is just dp[n][m][0] + dp[n][m][1]. Observe that this dp doesn't only give us one answer, it actually gives us all 
//the answers to all combinations of prefixes of x and y. 

//So if we iterate through all pairs of suffixes, this gives us an O(n^4) solution. However, we need O(n^2) to not TLE. This is where 
//inserting extra base cases everywhere comes in. Observe that if we insert some extra base case somewhere in the middle of our dp table,
//it'll propogate like normal, and the answers will describe the sum of the number of ways to merge starting from all base cases. 
//We just need to figure out a way to eliminate counting empty strings. 

//this is where we add an extra dimension, dp[i][j][k][b] = blah blah blah, b represents whether or not we've inserted elements from x
//and y. Initially, we'll set dp[i][j][2][0] = 1 for all i, j, these all represent the base cases where we haven't merged anything yet. 
//Then, we just need to check the values of dp[i][j][0][3] + dp[i][j][1][3] to extract the answers, guaranteeing that we haven't merged 
//any empty strings. 

struct mint;
typedef vector<mint> vm;
typedef vector<vector<mint>> vvm;
typedef pair<mint, mint> pmm;

const ll mod = 998244353;
struct mint {
    ll val; //this should always be in range [0, mod)
    mint(ll _val = 0) {val = _val; if(val < 0) val = mod + (val % mod); val %= mod;}
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
    mint operator /(const mint& other) const {return *this * other.pow(mod - 2);}
    mint operator /(ll other) const {return *this / mint(other);}
    mint& operator /=(const mint& other) {*this = *this / other; return *this;}
    mint& operator /=(ll other) {*this = *this / other; return *this;}
    mint operator %(const mint& other) const {return mint(val % other.val);}
    mint operator %(ll other) const {return *this % mint(other);}
    mint& operator %=(const mint& other) {*this = *this % other; return *this;}
    mint& operator %=(ll other) {*this = *this % other; return *this;}

    //don't forget about fermat's little theorem, 
    //a^(m-1) % m = 1. This means that a^(p % m) % m != a^(p) % m, rather a^(p % (m-1)) % m = a^(p) % m. 
    mint pow(ll b) const {
        mint ans(1), p(val);
        while(b != 0) {if(b % 2 == 1) {ans *= p;} p *= p; b /= 2;}
        return ans;
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

mint gcd(mint a, mint b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

vm fac, invfac;
void fac_init(int N) {
    fac = vm(N + 1), invfac = vm(N + 1);
    fac[0] = 1;
    for(int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i;
    invfac[N] = mint(1) / fac[N];
    for(int i = N; i > 0; i--) invfac[i - 1] = invfac[i] * i;
}

//n >= k
mint nck(mint n, mint k) {
    return fac[n] * invfac[k] * invfac[n - k];
}

mint calcf(string a, string b) {
    int n = a.size(), m = b.size();
    vector<vvm> dp(n + 1, vvm(m + 1, vm(26, 0)));
    dp[1][0][a[0] - 'a'] = 1;
    dp[0][1][b[0] - 'a'] = 1;
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= m; j++){
            for(int k = 0; k < 26; k++){
                //insert something from a
                if(i != n && a[i] - 'a' != k) dp[i + 1][j][a[i] - 'a'] += dp[i][j][k];
                //insert something from b
                if(j != m && b[j] - 'a' != k) dp[i][j + 1][b[j] - 'a'] += dp[i][j][k];
            }
        }
    }
    mint all = nck(n + m, n);
    mint ans = 0;
    for(int i = 0; i < 26; i++) ans += dp[n][m][i];
    cout << "ANS : " << a << " " << b << " " << ans << " " << all - ans << "\n";
    return ans;
}

mint calcf2(string a, string b) {
    int n = a.size(), m = b.size();
    vector<vector<vvm>> dp(n + 1, vector<vvm>(m + 1, vvm(3, vm(4, 0))));
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= m; j++){
            dp[i][j][2][0] = 1;
        }
    }
    mint ans = 0;
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= m; j++){
            for(int k = 0; k < 3; k++){
                char pc = 'A';
                if(k == 0) {
                    if(i == 0) continue;
                    pc = a[i - 1];
                }
                if(k == 1){
                    if(j == 0) continue;
                    pc = b[j - 1];
                }
                for(int bits = 0; bits < 4; bits++){
                    //insert something from a
                    if(i != n && a[i] != pc) dp[i + 1][j][0][bits | 1] += dp[i][j][k][bits];
                    //insert something from b
                    if(j != m && b[j] != pc) dp[i][j + 1][1][bits | 2] += dp[i][j][k][bits];
                }
            }
            ans += dp[i][j][0][3] + dp[i][j][1][3];
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    fac_init(1e5);
    mint ans = 0;
    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size();
    // calcf(a, b);
    // for(int la = 0; la < n; la++) for(int ra = la + 1; ra <= n; ra++){
    //     for(int lb = 0; lb < m; lb++) for(int rb = lb + 1; rb <= m; rb++){
    //         ans += calcf(a.substr(la, ra - la), b.substr(lb, rb - lb));
    //     }
    // }
    ans = calcf2(a, b);
    cout << ans << "\n";
    
    return 0;
}