#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//Codeforces - 1418E

//we can handle monsters with d >= b differently than monsters with d < b. Call these type 1 and type 2 
//monsters respectively. 

//notice that the durability only decreases when there is a type 1 monster, so let's first count for each type
//1 monster, how many times does it actually deal damage. Note that the number of times to deal damage should be
//the same across all type 1 monsters. 

//Let's build the permutation like this: we'll start with an empty array, and insert the elements into the 
//array one by one. When we insert an element, if there are n elements so far, there are n + 1 possible spots 
//to put it. The order in which we choose the elements will be predetermined. 

//WLOG, we can put all the type 1 elements before the type 2 elements. Consider how many times the last type 1 
//element will deal damage (equivalent to how many times it will be placed after a or more other type 1 elements).
//if there are A type 1 elements and B type 2 elements, we first place all type 1 elements excluding it 
//((A - 1)! ways), then place the last type 1 element (A - a ways), then place all the type 2 elements ((B + A)! / A! ways) 

//we can handle type 2 elements very similarly, just consider how many ways there are for the first type 2 element
//to deal damage (we don't use the last as then we don't know how many spots we can place it in where it'll deal damage). 

//since the number of ways within the type 1 and type 2 elements are the same, we can just sort d and multiply the ways 
//by the prefix and suffix sums respectively to get the total amount of damage over all permutations. 

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
    
    fac_init(2e6);
    int n, m;
    cin >> n >> m;
    vi d(n);
    for(int i = 0; i < n; i++) cin >> d[i];
    sort(d.begin(), d.end());
    vm pfx(n + 1, 0);
    for(int i = 1; i <= n; i++) pfx[i] = pfx[i - 1] + d[i - 1];
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        //find how many monsters have d under b
        int lcnt = 0;
        {
            int low = 1, high = n;
            while(low <= high) {
                int mid = low + (high - low) / 2;
                if(d[mid - 1] < b) lcnt = mid, low = mid + 1;
                else high = mid - 1;
            }
        }
        int hcnt = n - lcnt;
        if(a > hcnt) {  //no matter how we rearrange, we'll take no damage. 
            cout << "0\n";
            continue;
        }
        mint ans = 0;
        //account for monsters with d >= b
        ans += (pfx[n] - pfx[lcnt]) * fac[hcnt - 1] * (hcnt - a) * (fac[n] * invfac[hcnt]);
        //account for monsters with d < b
        ans += pfx[lcnt] * fac[hcnt] * (hcnt - a + 1) * (fac[n] * invfac[hcnt + 1]);
        ans *= invfac[n];
        cout << ans << "\n";
    }
    
    return 0;
}