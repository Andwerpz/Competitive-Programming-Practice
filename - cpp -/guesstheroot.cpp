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

//Codeforces - 1155E

//If we know the polynomial, then we can just try all values in range [0, mod) and guarantee to find a root
//if it exists. 

//How can we find the polynomial? We can treat the coefficients as variables in a system of linear equations 
//and apply gaussian elimination. We just need to query K + 1 unique x. 

struct mint;
typedef vector<mint> vm;
typedef vector<vector<mint>> vvm;
typedef pair<mint, mint> pmm;

const ll mod = 1e6 + 3;
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

const int K = 10;
vm jval = {1000002, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0};
mint query(mint x) {
    mint tmp = 0;
    cout << "? " << x << endl;
    cin >> tmp;
    return tmp;

    // for(int i = 0; i <= K; i++) tmp += jval[i] * x.pow(i);
    // return tmp;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    
    vvm mat(K + 1, vm(K + 1));
    vm val(K + 1);
    for(int i = 0; i <= K; i++){
        for(int j = 0; j <= K; j++){
            mat[i][j] = mint(i).pow(j);
        }
    }
    for(int i = 0; i <= K; i++){
        val[i] = query(i);
    }
    //run gaussian elimination to figure out the coefficients
    for(int i = 0; i <= K; i++){
        val[i] /= mat[i][i];
        for(int j = i + 1; j <= K; j++) mat[i][j] /= mat[i][i];
        mat[i][i] = 1;
        for(int j = i + 1; j <= K; j++){
            mint mult = mat[j][i];
            val[j] -= val[i] * mult;
            for(int k = i; k <= K; k++) mat[j][k] -= mat[i][k] * mult;
        }
    }
    for(int i = K; i >= 0; i--){
        for(int j = 0; j < i; j++){
            val[j] -= val[i] * mat[j][i];
            mat[j][i] = 0;
        }
    }
    //now we know the coefficients, just brute force test all values from 0 to mod 
    //and we're guaranteed to find the answer if it exists
    int ans = -1;
    for(int i = 0; i < mod; i++){
        mint cval = 0;
        for(int j = 0; j <= K; j++){
            cval += val[j] * mint(i).pow(j);
        }
        if(cval == 0) ans = i;
    }
    cout << "! " << ans << endl;
    
    return 0;
}