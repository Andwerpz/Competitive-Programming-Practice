#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 547A

//reduces to a CRT problem. 
//instead of h_1 and h_2, i'll call them a and b. 

//first, we can cycle a and b around until they're both in their respective cycles. Then, we can check if at and bt
//(which are the respective target values for a and b) exists within their respective cycles. 

//If they do, then we can reduce this to a problem solvable by CRT. Denote the offset from the current a to at as 
//at_ind; bt_ind is similarly defined. The size of the two cycles are ca_size and cb_size. Then, we are simply asking
//what's the number of timesteps t such that 
//t === at_ind % ca_size
//t === bt_ind % cb_size

//note that if gcd(ca_size, cb_size) != 1, then there may be no solution. We have to check if 
//at_ind % g != bt_ind % g. If this is true, then there is indeed no solution. Otherwise, there is always a solution. 

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

ll extended_euclidean(ll a, ll b, ll& x, ll& y) {
    x = 1, y = 0;
    ll x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        ll q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

ll mod_inv(ll a, ll m) {
    ll x, y;
    ll g = extended_euclidean(a, m, x, y);
    if (g != 1) {
        return -1;
    }
    else {
        x = (x % m + m) % m;
        return x;
    }
}

ll chinese_remainder_theorem(vector<ll> modulo, vector<ll> remainder) {
    if(modulo.size() != remainder.size()) {
        return -1;
    }
    ll M = 1;
    for(int i = 0; i < modulo.size(); i++){
        M *= modulo[i];
    }
    ll solution = 0;
    for(int i = 0; i < modulo.size(); i++){
        ll a_i = remainder[i];
        ll M_i = M / modulo[i];
        ll N_i = mod_inv(M_i, modulo[i]);
        solution = (solution + a_i * M_i % M * N_i) % M;
    }
    return solution;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll mod;
    cin >> mod;
    ll a, at, ax, ay, b, bt, bx, by;
    cin >> a >> at >> ax >> ay >> b >> bt >> bx >> by;
    ll ans = 0;
    vector<bool> va(mod, false), vb(mod, false);
    while(!va[a] || !vb[b]) {
        va[a] = true;
        vb[b] = true;
        a = (a * ax + ay) % mod;
        b = (b * bx + by) % mod;
        ans ++;
        if(a == at && b == bt) {
            cout << ans << "\n";
            return 0;
        }
    }
    //ok, we know a and b have to be in their respective cycles. 
    ll at_ind = -1, bt_ind = -1;
    ll iptr = 1;
    ll ptr = (a * ax + ay) % mod;
    ll ca_size, cb_size;
    if(a == at) {
        at_ind = 0;
    }
    if(b == bt){
        bt_ind = 0;
    }
    while(ptr != a){
        if(ptr == at){
            at_ind = iptr;
        }
        iptr ++;
        ptr = (ptr * ax + ay) % mod;
    }
    ca_size = iptr;
    iptr = 1;
    ptr = (b * bx + by) % mod;
    while(ptr != b){
        if(ptr == bt) {
            bt_ind = iptr;
        }
        iptr ++;
        ptr = (ptr * bx + by) % mod;
    }
    cb_size = iptr;
    ll g = gcd(ca_size, cb_size);
    //check if it's even possible
    if(at_ind == -1 || bt_ind == -1 || at_ind % g != bt_ind % g) {
        cout << "-1\n";
        return 0;
    }
    //ok, there has to be a solution
    ll rem = at_ind % g;
    ans += rem;
    at_ind -= rem;
    bt_ind -= rem;
    at_ind /= g;
    bt_ind /= g;
    ll ma = ca_size / g;
    ll mb = cb_size / g;
    ll crt = chinese_remainder_theorem({ma, mb}, {at_ind, bt_ind});
    ans += crt * g;
    cout << ans << "\n";
    
    return 0;
}
