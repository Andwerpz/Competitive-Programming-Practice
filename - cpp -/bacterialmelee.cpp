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

//Codeforces - 756D

//observe that any string that can be created by the operations, can also be created using the following method:
//1. choose any subsequence, c_1, c_2, ..., c_k. I'll put an extra requirement that c_i != c_{i + 1}. 
//2. assign a positive integer to each character in the subsequence, x_1, x_2, ..., x_k, s.t. sum(x_i) = n
//3. repeat c_i x_i times to construct the final string. 

//note that given the length of the subsequence, we can compute the amount of assignments of x_i using stars
//and bars. 

//so the process reduces to counting the number of unique subsequences of the string that don't have two adjacent
//characters that are the same, indexed by length. 
//we can solve this problem using DP. However, when solving, you need to avoid adding the x26 constant factor
//as n = 5000. 

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

mint gcd(mint a, mint b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

vector<mint> fac;
map<pair<mint, mint>, mint> nckdp;
void fac_init(int N) {
    fac = vector<mint>(N);
    fac[0] = 1;
    for(int i = 1; i < N; i++){
        fac[i] = fac[i - 1] * i;
    }
}

//n >= k
mint nck(mint n, mint k) {
    if(nckdp.find({n, k}) != nckdp.end()) {
        return nckdp.find({n, k}) -> second;
    }
    mint ans = fac[n].inv_divide(fac[k] * fac[n - k]);
    nckdp.insert({{n, k}, ans});
    return ans;
}

mint stars_bars(ll stars, ll bars, bool allow_zero = false) {
    if(allow_zero) {
        //zero group is group with nothing inside
        return stars_bars(stars + bars + 1, bars, false);
    }
    return nck(stars - 1, bars);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    fac_init(1e4);
    int n;
    cin >> n;
    string s;
    cin >> s;
    //compute number of unique subsequences indexed by length
    vvm dp(n + 1, vm(n + 1, 0));
    vvm sum(n + 1, vm(26, 0));  
    vm rsum(n + 1, 0);  
    rsum[0] = 1;    //empty subsequence
    vvm psum(26, vm(n + 1, 0));
    for(int i = 1; i <= n; i++){
        int cc = s[i - 1] - 'a';
        for(int j = 1; j <= n; j++){
            dp[i][j] = (rsum[j - 1] - sum[j - 1][cc]);
        }
        //subtract out doublecounting
        for(int j = 1; j <= n; j++){
            dp[i][j] -= psum[cc][j];
            psum[cc][j] = (rsum[j - 1] - sum[j - 1][cc]);
        }
        //update sum, rsum
        for(int j = 0; j <= n; j++){
            rsum[j] += dp[i][j];
            sum[j][cc] += dp[i][j];
        }
    }
    mint ans = 0;
    for(int i = 1; i <= n; i++){
        mint sum = rsum[i];
        ans += sum * stars_bars(n, i - 1);
    }
    cout << ans << "\n";
    
    return 0;
}