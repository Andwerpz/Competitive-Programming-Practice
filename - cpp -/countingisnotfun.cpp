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

//Codeforces - 2063 F1 F2

//catalan(n) = number of balanced bracket sequences of length 2n. 

//if you're asked how many ways to construct a valid bracket sequence given the position of two balanced brackets
//somewhere in the sequence, something like '????(????)????', where you can fill the '?' with brackets, then the answer
//is just catalan(inside / 2) * catalan(outside / 2) where inside and outside are the number of '?' on the inside and outside
//of the given brackets respectively. 

//Since we're given that the brackets are balanced, we can insert them anywhere inside another balanced bracket sequence, 
//therefore the ways to assign the outer brackets are given by catalan(outside / 2). Likewise with the inner brackets. 

//With many balanced brackets, we just look at the number of '?' on each 'level'. So given some fixed balanced brackets,
//we can easily compute the number of bracket sequences that satisfy it. 

//Now, to answer the problem, we can simply work backwards. Start with all the hints, and take them away one at a time. Each
//time you take a hint away, you increase the amount of '?' belonging to your parent hint by 2 + the amount of '?' currently
//contained by the removed hint. 

//However, how to determine what is your parent hint? Since brackets can get removed all the time, we can use path 
//compression to quickly get the next existing parent hint. 

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

//given that we choose n / 2 left brackets and n / 2 right brackets, 
//nck(n, n / 2) is the total amount of bracket sequences, and nck(n, n / 2 + 1) is the amount of bad sequences.
mint nr_rbs(int n){
    if(n == 0){
        return 1;
    }
    if(n % 2){
        return 0;
    }
    return nck(n, n / 2) - nck(n, n / 2 + 1);
}

//true if odd, false if even. 
bool nck_parity(mint n, mint k) {   
    return (k & (n - k)) == 0;
}

//gives the nth catalan number. 
//c_n = \sum_{i = 1}^{n} c_{i - 1} c{n - i}, c_0 = 1
//c_n = number of regular bracket sequences of size 2n (n pairs of brackets)
mint catalan(mint n){
    if(n == 0) return 1;
    return nck(2 * n, n) - nck(2 * n, n + 1);
}

int find(vi& p, vb& v, int cur) {
    if(v[cur]) return cur;
    return p[cur] = find(p, v, p[cur]);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    fac_init(3e6);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<pii> seg(n);
        vi b(2 * n, -1);
        for(int i = 0; i < n; i++){
            int l, r;
            cin >> l >> r;
            l --, r --;
            b[l] = 1, b[r] = -1;
            seg[i] = {l, r};
        }
        vi id(2 * n, -1);
        int idptr = 1;
        vi p(1, -1), a(1, 0);
        vb v(1, true);
        stack<int> s;
        s.push(0);
        for(int i = 0; i < 2 * n; i++){
            if(b[i] == 1){
                int cid = idptr ++;
                id[i] = cid;
                p.push_back(s.top());
                a.push_back(0);
                v.push_back(true);
                s.push(cid);
            }
            else {
                s.pop();
            }
        }
        vm ans(n + 1, 1);
        mint cans = 1;
        for(int i = n - 1; i >= 0; i--){
            //remove the ith hint
            int cid = id[seg[i].first];
            v[cid] = false;
            //find valid parent
            int pid = find(p, v, cid);
            //upd ans
            cans /= catalan(a[cid]) * catalan(a[pid]);
            a[pid] += a[cid] + 1;
            cans *= catalan(a[pid]);
            ans[i] = cans;
        }
        for(int i = 0; i <= n; i++) cout << ans[i] << " ";
        cout << "\n";
    }
    
    return 0;
}