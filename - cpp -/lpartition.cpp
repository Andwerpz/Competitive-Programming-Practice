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

//AtCoder - ARC190B

//pretty annoying implementation, and N = 1e7 means that we need good constant factor. 

//how does building an L-partition work? We can place the Ls from large to small. For the largest L, there are 4
//ways to place it, and after placing it there are 4 ways to place the next L. So in total, there are 4^{N - 1} 
//L-partitions in total. 

//let's first try to solve the problem if k = 1. In this case, we just want to count the number of partitions 
//that place the k = 1 L on position (r, c). Observe that there is some space to the top, right, bottom, left, 
//of the target tile. Each L placed will decrement one space from the (top or bottom) and (left or right). 
//So if there are A, B, C, D, units of space respectively, then there are \binom{A + C}{A} * \binom{B + D}{B} 
//partitions that put the k = 1 L on (r, c). 

//Actually in general, if we want to leave a square (of any size) blank, and want to compute the number of 
//L-partitions that can do that, we can use the above conclusion to do so. 

//So to compute the answer for arbitrary k, we just need to see how many ways there are to generate a partition 
//with (r, c) being on the edge of a blank square of size k. Let's consider the number of ways for (r, c) to be 
//on one side (we can consider each side seperately). We can 'slide' the square, and notice that one binomial
//coefficient stays the same, and the other one changes. Note that when we increment k by 1, the range on which 
//this binomial coefficient sums over changes slowly and predictably. Therefore, we can just keep track of the 
//prefix and suffix across k. 

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

mint gcd(mint a, mint b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

const int N = 1e7 + 100;
vm fac, invfac;
void fac_init(int N) {
    fac = vm(N + 1), invfac = vm(N + 1);
    fac[0] = 1;
    for(int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i;
    invfac[N] = mint(1).inv_divide(fac[N]);
    for(int i = N; i > 0; i--) invfac[i - 1] = invfac[i] * i;
}

//n >= k
mint nck(mint n, mint k) {
    return fac[n] * invfac[k] * invfac[n - k];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, r, c;
    cin >> n >> r >> c;
    r --, c --;
    fac_init(N);
    mint inv2 = mint(1).inv_divide(2);
    vm pow2(N + 1);
    pow2[0] = 1;
    for(int i = 1; i <= N; i++) pow2[i] = pow2[i - 1] * 2;
    //precalc all answers
    vm a(n + 1, 0);
    a[1] = nck(n - 1, r) * nck(n - 1, c);
    for(int _ = 0; _ < 4; _++){
        if(_ < 2){
            int low = c - 1, high = c;
            mint pfx = 0, sfx = 0;
            for(int i = 0; i <= low; i++) pfx += nck(n - 1, i);
            for(int i = c + 1; i <= n - 1; i++) sfx += nck(n - 1, i);
            for(int i = 2; i <= n; i++){    //check top and bottom
                int clow = max(0, c + 1 - i), chigh = min(n - i, c);
                int tot = n - i;
                if(low != -1) pfx = (pfx - nck(tot, low)) * inv2, low --;
                if(chigh == high) sfx = (sfx - nck(tot, high)) * inv2;
                if(r + 1 - i >= 0) a[i] += (pow2[tot] - pfx - sfx) * nck(n - i, r + 1 - i) * 2;
                if(n - r >= i) a[i] += (pow2[tot] - pfx - sfx) * nck(n - i, r) * 2;
            }
        }
        int nr = c, nc = n - r - 1;
        c = nc, r = nr;
    }
    for(int i = 2; i <= n; i++){    //subtract off corners
        if(r - i + 1 >= 0 && c - i + 1 >= 0) a[i] -= nck(n - i, r - i + 1) * nck(n - i, c - i + 1);
        if(r - i + 1 >= 0 && c + i <= n) a[i] -= nck(n - i, r - i + 1) * nck(n - i, c);
        if(r + i <= n && c - i + 1 >= 0) a[i] -= nck(n - i, r) * nck(n - i, c - i + 1);
        if(r + i <= n && c + i <= n) a[i] -= nck(n - i, r) * nck(n - i, c);
    }
    for(int i = 2; i <= n; i++){    //mult by inner square ways
        a[i] *= pow2[i - 2] * pow2[i - 2];
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        int k;
        cin >> k;
        cout << a[k] << "\n";
    }
    
    return 0;
}