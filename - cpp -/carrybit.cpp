#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1761D

//we can use a constructive approach to solve this problem. 

//let's analyze what happens when we add two binary numbers:
//  10110101
//+ 10001101
//----------
// 101000010

//note that we have two carry 'segments', one 4 long, and the other 1 long. Note that any carry segment needs to start
//with both numbers having that bit, and it will go as long as at least one number has a bit. I call the initial bit
//of the carry segment the 'spark', and the tail 'fuel'. 

//note that the sum of 'spark' and 'fuel' bits needs to equal k, and that after the last 'fuel' bit of a carry segment,
//both numbers have to have a 0 bit. 

//so, we can simply iterate over how many carry segments we split the k carries into, and compute exactly how many 
//(a, b) pairs satisfy that. 

//to see how exactly i do that, you can look at the code, i commented it pretty well i think. 

struct mint;
vector<mint> fac;
map<pair<mint, mint>, mint> nckdp;

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

mint gcd(mint a, mint b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

void fac_init(int N) {
    fac = vector<mint>(N);
    fac[0] = 1;
    for(int i = 1; i < N; i++){
        fac[i] = fac[i - 1] * i;
    }
}

//n >= k
mint nck(mint n, mint k) {
    if(nckdp.find({n, k}) != nckdp.end()) {
        return nckdp.find({n, k}) -> second;
    }
    mint ans = fac[n].inv_divide(fac[k] * fac[n - k]);
    nckdp.insert({{n, k}, ans});
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    fac_init(2e6);
    vector<mint> pow3(2e6);
    pow3[0] = 1;
    for(int i = 1; i < pow3.size(); i++){
        pow3[i] = pow3[i - 1] * 3;
    }
    mint n, k;
    cin >> n >> k;
    mint ans = 0;
    if(k == 0){
        ans = mint(3).pow(n);
        cout << ans << "\n";
        return 0;
    }
    //iterate through how many bits of 'fuel' we use
    for(int i = 1; i <= k; i++){
        mint c_ans = 1;
        //consider how many ways to distribute the 'fuel'
        //k bits of fuel in total, need to partition it to i pieces. 
        c_ans *= nck(k - 1, i - 1);
        //how many ways to permute each 'fuel' bit
        //can either be in a, b, or both. 'sparks' cannot permute, they are forced to be both. 
        c_ans *= pow3[k - i];
        //ok, we have to do a split here. It depends on whether or not the nth bit is a fuel bit or not. 
        if(n >= k + (i - 1)) {
            //nth bit is a fuel bit
            mint c_ans_f = c_ans;
            //how many ways to place the 'fuel' in the array
            //n - k bits of non-fuel, need to be partitioned into i segments
            c_ans_f *= nck(n - k, i - 1);
            //how many ways to permute each non-'fuel' bit
            //can either be in a, b, or none, except for ones that directly follow fuel, which are forced to be none.
            c_ans_f *= pow3[n - k - (i - 1)];
            ans += c_ans_f;
        }
        if(n >= k + i) {
            //nth bit is not a fuel bit
            mint c_ans_n = c_ans;
            //how many ways to place the 'fuel' in the array
            //n - k bits of non-fuel, need to be partitioned into i + 1 segments
            c_ans_n *= nck(n - k, i);
            //how many ways to permute each non-'fuel' bit
            //can either be in a, b, or none, except for ones that directly follow fuel, which are forced to be none.
            c_ans_n *= pow3[n - k - i];
            ans += c_ans_n;
        }
    }
    cout << ans << "\n";
    
    return 0;
}