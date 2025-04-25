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

//Kattis - chasingsubs

//imagine sliding t against s in some sort of sliding window. We just need to check that there is a one-to-one relationship between
//letters in t and s at the current position. 

//we can check a weak form of the one to one relationship, and then confirm it using hashing. First, for each unique letter in t, 
//find some occurrence of it. Then, for each of these occurrences, make sure that they all map to unique letters in s. Then, compute
//the hash value of the substring of s as if we replaced those letters with their matches in t. 

//how can we compute the hash value? Well first I'll clarify that i'm using polynomial rolling hash. It looks something like
//s[0] * p^{n - 1} + s[1] * p^{n - 2} + \cdots + s[n - 1] * p^{0}
//so for each unique letter, find the sum of it's coefficients, and maintain that sum as we slide t against s. 
//this can be done in O(26) time. 

//finally we can compute the hash value of the substring of s using the coefficient lookup table, and check whether that hash matches
//with the actual hash of t. 

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    const ll p = 67;
    string s, t;
    cin >> s >> t;
    if(t.size() > s.size()) {
        cout << "0\n";
        return 0;
    }
    //keep track of some occurrence of each letter in t to make matches
    vi tocc(26, -1);
    for(int i = 0; i < t.size(); i++) tocc[t[i] - 'a'] = i;
    //sliding window + hashing
    vm scoeff(26, 0);
    vi ans(0);
    mint thash = 0;
    for(int i = 0; i < t.size(); i++){
        thash *= p;
        for(int j = 0; j < 26; j++) scoeff[j] *= p;
        thash += t[i] - 'a';
        scoeff[s[i] - 'a'] += 1;
    }
    for(int i = t.size(); i <= s.size(); i++){
        mint shash = 0;
        bool is_valid = true;
        vb v(26, false);
        for(int j = 0; j < 26; j++) {
            if(tocc[j] == -1) continue;
            int ind = (i - t.size()) + tocc[j];
            if(v[s[ind] - 'a']) is_valid = false;
            v[s[ind] - 'a'] = true;
            shash += scoeff[s[ind] - 'a'] * j;
        }
        if(is_valid && shash == thash) ans.push_back(i - t.size());
        if(i != s.size()) {
            for(int j = 0; j < 26; j++) scoeff[j] *= p;
            scoeff[s[i] - 'a'] += 1;
            scoeff[s[i - t.size()] - 'a'] -= mint(p).pow(t.size());
        }
    }
    if(ans.size() == 1) cout << s.substr(ans[0], t.size()) << "\n";
    else cout << ans.size() << "\n";    
    
    return 0;
}