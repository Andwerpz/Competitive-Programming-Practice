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

//Codeforces - 1930E

//lets try to solve for k = 1
// what arrays are reachable? what conditions are necessary and sufficient?
//  - number of elements === n (mod 2)
//  - must have at least 2 'connected components' of removed elements
// are these two conditions necessary and sufficient? try to come up with a counterexample
// for k = 1, these conditions are necessary and sufficient. 

// now, consider k = 2
//  - number of elements === n (mod 4)
//  - if you remove the first and last 2 removed elements, then there must be a gap within the remaining removed elements 
//    (by gap I mean the remaining removed elements cannot form a connected component)

// so in general,
//  - number of elements === n (mod 2k)
//  - if you remove the first and last k removed elements, then there must be a gap within the remaining removed elements 
//    (by gap I mean the remaining removed elements cannot form a connected component)

// suppose we fix the first condition to be true, how many ways are there to not satisfy the second condition? If you don't 
// satisfy the second condition, it must be the case that all the removed elements (except for the first k - 1 and last k - 1) 
// form a connected component. So we can just scroll this connected component across the array and count?

//naively, we get something like this for a given k
// for(int mid = 2; mid <= n; mid += 2 * k) {
//     for(int l = k - 1; n - (mid + l) >= k - 1; l++) {
//         bcnt += nck(l, k - 1) * nck(n - mid - l, k - 1);
//     }
// }

//observe that if we can somehow get rid of the inner loop, then the entire solution will be n * log(n). The inner loop is just
//computing \sum_{i = k - 1}^{n - (k - 1)} \binom{i}{k - 1} \binom{(n - mid) - i}{k - 1}

//lets get rid of some of the offsets, so we want to find a closed form formula for
// \sum_{i = k}^{n - k} \binom{i}{k} \binom{n - i}{k}

//this looks like we have n elements, and we're somehow choosing 2k elements. Imagine that we have an extra element, and we fix the
//position of the extra element to be at position i. Then, we choose k elements from the stuff that come before and k from the stuff
//that comes after. This is literally just counting the number of ways to choose 2k + 1 elements from n + 1 elements, so
// \sum_{i = k}^{n - k} \binom{i}{k} \binom{n - i}{k} = \binom{n + 1, 2k + 1}

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    fac_init(1e6 + 100);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        for(int k = 1; k <= (n - 1) / 2; k++){
            mint ans = 0;
            //how many ways to satisfy first condition
            for(int i = 0; i <= n; i += 2 * k) ans += nck(n, i);
            // cout << "INIT ANS : " << k << " " << ans << "\n";
            //how many ways to not satisfy the second condition while satisfying the first condition
            // for(int l = k - 1; l <= n; l++){
            //     for(int mid = 2; mid + l + (k - 1) <= n; mid += 2 * k){
            //         // cout << "NOT SATISFY : " << l << " " << mid << "\n";
            //         ans -= nck(l, k - 1) * nck(n - (mid + l), k - 1);
            //     }
            // }
            // cout << "TOT : " << ans << "\n";
            // mint bcnt = 0;
            // for(int mid = 2; mid <= n; mid += 2 * k) {
            //     for(int l = k - 1; n - (mid + l) >= k - 1; l++) {
            //         bcnt += nck(l, k - 1) * nck(n - mid - l, k - 1);
            //     }
            // }
            mint ccnt = 0;
            for(int mid = 2; 2 * (k - 1) <= n - mid; mid += 2 * k) {
                ccnt += nck((n - mid) + 1, (2 * (k - 1)) + 1);
            }
            // cout << "BCNT, CCNT : " << bcnt << " " << ccnt << " " << k << "\n";
            ans -= ccnt;
            cout << ans << " ";
        }
        cout << "\n";
    }
    
    return 0;
}