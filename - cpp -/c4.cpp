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

//AtCoder - AGC51D

//let's classify paths by how many times they go around the cycle CCW. Actually, if we fix the amount of times
//it goes around, then we know exactly how many times each edge (ST, TS, TU, UT, UV, VU, VS, SV) is used, so this reduces
//to counting the number of eulerian circuits in this directed graph with multiedges. 

//for each vertex, let's use S as an example, we can arbitrarily order its going to T and going to V edges. This means on the
//ith time visiting S, we'll take the ith edge in the ordering. For S, there are nck(ST + SV, SV) ways to do this, and in
//total we can just multiply all the ways for each node together. 

//the idea is that we hope for all paths constructed this way to visit each edge and return to S, but of course not all paths
//will do this. 

//since the graph we generate is guaranteed to be eulerian, we know that all edges connected to S should be visited. So it's
//only edges indicent to U that might not be visited. 

//there are two cases in which some ordering doesn't correspond to an eulerian cycle:
// - the last edge in U points to T, and the last edge in T points to U
// - the last edge in U points to V, and the last edge in V points to U
//consider the last time that the cycle leaves U. Whatever node it leaves towards must point towards S as its next edge, otherwise
//the cycle will end on U. 

//if an ordering doesn't follow one of these two, then it corresponds to an eulerian cycle. We can easily count these cases 
//using binomials similar to the one counting the total amount of cases. 

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
    
    fac_init(2e6);
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    mint ans = 0;
    //iterate over how many times going around CCW
    for(int i = -max({a, b, c, d}); i <= max({a, b, c, d}); i++) {
        int ca = a, cb = b, cc = c, cd = d;
        int ST = 0, TS = 0, TU = 0, UT = 0, UV = 0, VU = 0, VS = 0, SV = 0;
        if(i < 0) TS -= i, UT -= i, VU -= i, SV -= i;
        else ST += i, TU += i, UV += i, VS += i;
        ca -= abs(i), cb -= abs(i), cc -= abs(i), cd -= abs(i);
        if(min({ca, cb, cc, cd}) < 0) continue;
        if(ca % 2 || cb % 2 || cc % 2 || cd % 2) continue;
        ST += ca / 2, TS += ca / 2, TU += cb / 2, UT += cb / 2;
        UV += cc / 2, VU += cc / 2, VS += cd / 2, SV += cd / 2;
        int dS = SV + ST, dT = TS + TU, dU = UT + UV, dV = VU + VS;
        mint cans = nck(dS, ST) * nck(dT, TU) * nck(dU, UV) * nck(dV, VS);
        if(dU != 0 && dT != 0 && UT != 0 && TU != 0) cans -= nck(dS, ST) * nck(dT - 1, TU - 1) * nck(dU - 1, UV) * nck(dV, VS);
        if(dU != 0 && dV != 0 && UV != 0 && VU != 0) cans -= nck(dS, ST) * nck(dT, TU) * nck(dU - 1, UV - 1) * nck(dV - 1, VS);
        ans += cans;
    }
    cout << ans << "\n";
    
    return 0;
}