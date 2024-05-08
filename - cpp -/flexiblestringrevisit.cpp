#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Codeforces - 1778D

//note that the only thing we care about is the number of characters that differ between A and B. 
//E[i] is simply the expected value given that i characters differ. 

//note that E[i] = (i / n) * E[i - 1] + ((n - i) / n) * E[i + 1] + 1. I also claim that 
//E[i] in the form a[i] * E[i + 1] + b[i]. Below is a derivation. 

//E[i] = a[i] * E[i + 1] + b[i]
//E[i] = (i / n) * E[i - 1] + ((n - i) / n) * E[i + 1] + 1
//E[i] = (i / n) * (a[i - 1] * E[i] + b[i - 1]) + ((n - i) / n) * E[i + 1] + 1
//(1 - (i / n) * a[i - 1]) * E[i] = (i / n) * b[i - 1] + ((n - i) / n) * E[i + 1] + 1
//E[i] = ((n - i) / n) / (1 - (i / n) * a[i - 1]) * E[i + 1] + (1 + (i / n) * b[i - 1]) / (1 - (i / n) * a[i - 1])
//a[i] = ((n - i) / n) / (1 - (i / n) * a[i - 1])
//b[i] = (1 + (i / n) * b[i - 1]) / (1 - (i / n) * a[i - 1])

//our base case is a[1] = (n - 1) / n, b[1] = 1.

//once we have all the a and b coefficients, we can then figure out E[n - 1]:
//E[n] = E[n - 1] + 1
//E[n - 1] = a[n - 1] * E[n] + b[n - 1]
//E[n - 1] = a[n - 1] * (E[n - 1] + 1) + b[n - 1]
//(1 - a[n - 1]) * E[n - 1] = a[n - 1] + b[n - 1]
//E[n - 1] = (a[n - 1] + b[n - 1]) / (1 - a[n - 1])

//and then use E[n - 1] to compute all E. 

//Note that the way i derived it leads to a much slower computation than the other way around; expressing E[i]
//in terms of E[i - 1]. 

ll mod = 998244353;
struct mint {
    ll val;
    mint(ll _val = 0) {val = _val;}
    mint(const mint& other) {val = other.val;}
    bool operator ==(const mint& other) const {return val == other.val;}
    bool operator ==(ll other) const {return val == other;}
    bool operator !=(const mint& other) const {return val != other.val;}
    bool operator !=(ll other) const {return val != other;}
    mint& operator =(const mint& other) {val = other.val; return *this;}
    mint& operator =(ll other) {val = other; return *this;}
    mint operator +(const mint& other) const {ll ret = val + other.val; while(ret >= mod) {ret -= mod;} return mint(ret);}
    mint operator +(ll other) const {ll ret = val + other; while(ret >= mod) {ret -= mod;} return mint(ret);}
    mint& operator +=(const mint& other) {*this = *this + other; return *this;}
    mint& operator +=(ll other) {*this = *this + other; return *this;}
    mint operator -() const {return mint((mod - val) % mod);};
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
    
    mint pow(const mint& other) const {
        mint ans(1), p(val);
        ll b = other.val;
        while(b) {if(b % 2 == 1) {ans *= p;} p *= p; b /= 2;}
        return ans;
    }
    mint pow(ll other) const {
        mint ans(1), p(val);
        ll b = other;
        while(b) {if(b % 2 == 1) {ans *= p;} p *= p; b /= 2;}
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
mint operator +(ll a, const mint& b) {ll ret = a + b.val; while(ret >= mod) {ret -= mod;} return mint(ret);}
mint operator -(ll a, const mint& b) {ll ret = a - b.val; while(ret < 0) {ret += mod;} return mint(ret);}
mint operator *(ll a, const mint& b) {return mint((a * b.val) % mod);}
mint operator /(ll a, const mint& b) {return mint((a / b.val) % mod);}
mint operator %(ll a, const mint& b) {return mint(a % b.val);}

const int N = 1e6 + 1;
mint e[N], a[N], b[N], i_inv[N], ni_inv[N]; 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        if(n == 1){
            string a, b;
            cin >> a >> b;
            cout << (a != b) << "\n";
            continue;
        }
        //precalc some stuff
        for(int i = 0; i <= n; i++){
            i_inv[i] = mint(i).inv_divide(n);
            ni_inv[i] = 1 - i_inv[i];
        }
        //compute probabilities
        e[0] = 0;
        a[1] = mint(n - 1).inv_divide(n);
        b[1] = 1;
        for(int i = 2; i < n; i++){
            a[i] = ni_inv[i].inv_divide(1 - i_inv[i] * a[i - 1]);
            b[i] = (1 + i_inv[i] * b[i - 1]).inv_divide(1 - i_inv[i] * a[i - 1]);
        }
        //use this to figure out E[n - 1], and from there, we can figure out everything
        e[n - 1] = (a[n - 1] + b[n - 1]).inv_divide(1 - a[n - 1]);
        e[n] = e[n - 1] + 1;
        string a_str, b_str;
        cin >> a_str >> b_str;
        int b_cnt = 0;
        for(int i = 0; i < n; i++){
            b_cnt += a_str[i] != b_str[i];
        }
        for(int i = n - 2; i >= b_cnt; i--){
            e[i] = a[i] * e[i + 1] + b[i];
        }
        cout << e[b_cnt] << "\n";
    }
    
    return 0;
}