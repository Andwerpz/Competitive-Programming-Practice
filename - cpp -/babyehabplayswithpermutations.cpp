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

//Codeforces - 1516E

//solved it in a better (?) way than editorial, and can probably make it work in O(k^2). 

//by experimentation, i figured out the minimum number of swaps to sort a permutation of size n with k cycles
//is n - k (we use c - 1 swaps per cycle, if c is the size of the cycle). 

//consider for a given amount of operations j, how many permutations can we sort using exactly j moves.
//the only two requirements is that j be >= to the minimum required moves, and that j have the same parity 
//as the minimum (so we can waste moves if j is too large). 

//so given a j, we can count the number of permutations by iterating over first the number of misplaced
//elements, and second the number of cycles. To do this, we first need to compute d(n, k), where
//d(n, k) = number of derangements of size n with exactly k cycles. Then, when considering a permutation of
//size N (different than n) with exactly n misplaced elements and k cycles (excluding fixed points), 
//the number of permutations that fits is nck(N, n) * d(n, k)

//note that n <= 2k, as if n > 2k, then the number of moves required to sort the derangement is too large.
//so if implemented properly, this solution can be O(k^2). 

struct mint;
typedef vector<mint> vm;
typedef vector<vector<mint>> vvm;
typedef pair<mint, mint> pmm;
vector<mint> fac;
map<pair<mint, mint>, mint> nckdp;

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

int n;
vm rfac;    //rfac[i] = n! / (n - i)!
void fac_init(int N) {
    fac = vector<mint>(N);
    fac[0] = 1;
    for(int i = 1; i < N; i++){
        fac[i] = fac[i - 1] * i;
    }
    rfac = vector<mint>(N);
    rfac[0] = 1;
    for(int i = 1; i < N; i++){
        rfac[i] = rfac[i - 1] * (n - i + 1);
    }
}

//n >= k
mint nck(mint k) {
    return rfac[k].inv_divide(fac[k]);
}

//a derangement is a permutation with no fixed points
//d[n][k] = number of derangements of size n with exactly k cycles
//d[n][k] = (n - 1) (d[n - 2][k - 1] + d[n - 1][k])
vvm d;
void calc_d(int N) {
    d = vvm(N, vm(N, 0));
    d[0][0] = 1;
    for(int n = 2; n < d.size(); n++){
        for(int k = 1; k <= n / 2; k++){
            d[n][k] = mint(n - 1) * (d[n - 2][k - 1] + d[n - 1][k]);
        }
    }
}

void solve(int k){
    //iterate over count of misplaced elements
    mint ans = 0;
    for(int i = 0; i <= min(n, 2 * k); i++){
        //iterate over number of cycles
        for(int j = 0; j <= i / 2; j++){
            //checks
            if((i - j) % 2 != k % 2 || i - j > k) continue;
            // cout << "VALID : " << i << " " << j << " " << nck(i) << " " << d[i][j] << "\n";
            ans += nck(i) * d[i][j];
        }
    }
    cout << ans << " ";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    calc_d(500);
    int k;
    cin >> n >> k;
    fac_init(500);
    for(int i = 1; i <= k; i++){
        solve(i);
    }
    cout << "\n";
    
    return 0;
}