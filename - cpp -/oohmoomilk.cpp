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

//USACO 2025 US Open - Gold P3

//since the selling price is M^2, farmer john always wants to increase the bottles with the most milk, and
//farmer nhoj likewise wants to decrease the bottles with the most milk. Actually, farmer john's actions will 
//not change: he will always try to increase the top a bottles. Then with farmer nhoj, the greatest a bottles
//will be increase in the way that they are as equal as possible. 

//we can simulate this in O(n) using some weird sliding window. 

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
    mint pow(const ll other) const {
        mint ans(1), p(val);
        ll b = other;
        while(b != 0) {if(b % 2 == 1) {ans *= p;} p *= p; b /= 2;}
        return ans;
    }
    // mint pow(ll other) const {return this->pow(mint(other));}

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, d, a, b;
    cin >> n >> d >> a >> b;
    vl m(n);
    for(int i = 0; i < n; i++){
        cin >> m[i];
    }
    sort(m.begin(), m.end());
    reverse(m.begin(), m.end());
    vl inc(n + 1, 0);
    ll bud = d * (a - b);
    ll rinc = 0;
    int r = a;
    for(int i = a - 1; i >= 0; i--){
        // cout << "I : " << i << " " << r << endl;
        if(i != 0){
            ll cinc = m[i - 1] - m[i];
            while(cinc != 0){
                ll amt = r - i;
                if(amt == 0) break;
                ll mult = min({cinc, bud / amt, d - rinc});
                if(rinc == d){
                    //move r to left
                    r --;
                    rinc -= inc[r];
                    continue;
                }
                if(mult == 0){
                    //put remaining budget here
                    inc[r - bud] += 1;
                    inc[r] -= 1;
                    bud -= bud;
                    break;
                }
                cinc -= mult;
                inc[i] += mult;
                inc[r] -= mult;
                bud -= mult * amt;
                rinc += mult;
            }
        }
        else {
            //just try to increase as much as possible
            while(bud != 0){
                ll amt = r - i;
                if(amt == 0) break;
                ll mult = min(bud / amt, d - rinc);
                if(rinc == d){
                    //move r to left
                    r --;
                    rinc -= inc[r];
                    continue;
                }
                if(mult == 0){
                    inc[r - bud] += 1;
                    inc[r] -= 1;
                    bud -= bud;
                    break;
                }
                inc[i] += mult;
                inc[r] -= mult;
                bud -= mult * amt;
                rinc += mult;
            }
        }
    }
    for(int i = 1; i < n; i++) inc[i] += inc[i - 1];
    for(int i = 0; i < n; i++) m[i] += inc[i];
    // for(int i = 0; i < n; i++) cout << m[i] << " ";
    // cout << "\n";
    mint ans = 0;
    for(int i = 0; i < n; i++){
        ans += (mint(m[i]) * mint(m[i]));
    }
    cout << ans << "\n";
    
    return 0;
}