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

//Codeforces - 2084E

//after cycling through a few ideas, I landed on this one:
//fix the subarray, and count over all possible permutations, the sum of mex from the subarray. 

//observe that the sum of mex is equal to counting the number of ways to get {0} in the subarray, plus
//the amount of ways to get {0, 1} in the subarray, plus ways to get {0, 1, 2} and so on. So how many ways
//are there to get the first x elements?

//suppose that there are b -1s in [l, r), and there are totb -1s in the entire array. Lets say that we need
//to use ucnt of them to fit the first x elements into [l, r). Then, there are 
//b * (b - 1) * ... * (b - ucnt + 1) * (totb - ucnt)! 
//permutations that have {0, ..., x} in [l, r). 

//Remember, the total mex is just the sum of x from 0 to max mex. Observe that this sum actually only is
//a function of the max mex and b, so for each max mex and b pair, we can precompute the sum in O(n^2) 

struct mint;
typedef vector<mint> vm;
typedef vector<vector<mint>> vvm;
typedef pair<mint, mint> pmm;

const ll mod = 1e9 + 7;
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
    mint pow(const mint& other) const {
        mint ans(1), p(val);
        ll b = other.val;
        while(b != 0) {if(b % 2 == 1) {ans *= p;} p *= p; b /= 2;}
        return ans;
    }
    mint pow(ll other) const {return this->pow(mint(other));}

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

//given a bunch of stars, how many ways are there to partition the stars using bars. 
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
    
    fac_init(1e5);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        mint ans = 0;
        int totb = 0;
        vb f(n, false);
        for(int i = 0; i < n; i++) if(a[i] != -1) f[a[i]] = true;
        for(int i = 0; i < n; i++) totb += a[i] == -1;
        vvm lut(n + 1, vm(n + 1, 0));   //lut[b][mmex] = ans
        for(int b = 0; b <= n; b++){
            mint mult = 1;
            int ucnt = 0;
            for(int mmex = 1; mmex <= n; mmex++){
                if(!f[mmex - 1]) {
                    if(b - ucnt == 0) break;
                    mult *= b - ucnt;
                    ucnt ++;
                }
                lut[b][mmex] = lut[b][mmex - 1] + mult * fac[totb - ucnt];
            }
        }
        for(int l = 0; l < n; l++){
            vb excl(n, false);
            for(int i = 0; i < n; i++) if(i != l && a[i] != -1) excl[a[i]] = true;
            int b = a[l] == -1;
            int mmex = 0;
            int mmexbcnt = a[l] == -1;
            vb cv(n, false);
            if(a[l] >= 0) cv[a[l]] = true;
            for(int r = l + 1; r <= n; r++){
                //on [l, r), what's the sum of mex over all possible permutations?
                //upd mmex
                while(mmex != n && !excl[mmex] && (cv[mmex] || (!f[mmex] && mmexbcnt != 0))) {
                    if(!f[mmex]) mmexbcnt --;
                    mmex ++;
                }
                // cout << "MMEX : " << l << " " << r << " " << mmex << " " << b << "\n";
                ans += lut[b][mmex];
                // mint mult = 1;
                // int ucnt = 0;
                // for(int i = 1; i <= mmex; i++){
                //     if(!f[i - 1]) {
                //         mult *= b - ucnt;
                //         ucnt ++;
                //     }
                //     ans += mult * fac[totb - ucnt];
                //     // cout << "TOTB UCNT : " << totb << " " << ucnt << "\n";
                //     cout << "UPD ANS : " << l << " " << r << " " << i << " " << mult << " " << fac[totb - ucnt] << "\n";
                // }
                //upd mmex, b, excl
                if(r != n) {
                    if(a[r] == -1) b ++, mmexbcnt ++;
                    else excl[a[r]] = false, cv[a[r]] = true;
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}