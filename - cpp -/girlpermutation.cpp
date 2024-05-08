#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1946E

//first observe that the location of the maximum element is given, as it should be the only index that is common between the
//prefix and suffix. 

//in the case that the first element of the prefix or suffix is not the ends of the array, or the maximum element isn't common
//then the answer should be 0. 

//otherwise, we can solve the problem to the left and right independently. First note that depending on the location
//of the maximum element, there will be a different amount of numbers to the left and to the right. We can initially choose
//the set of values to the left, and the values to the right will be determined. 

//next, to solve the left side (the right side is similar), notice that the second greatest element, the one that is just to
//the left of the greatest element, is already determined. It has to be the largest element smaller than the greatest
//element. We can choose how many elements go between it and the largest element, and the rest of the elements will
//go to the left. Note that we should consider that we can permute these elements that we've just placed. 

//now if we consider the second most maximum value, once we choose the set, the second maximum value is determined as well,
//so we can just repeat the process until we get to the last 'maximum' element, which should be the first element in the array.

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
    
    fac_init(1e6);
    int t;
    cin >> t;
    while(t--){
        int n, m1, m2;
        cin >> n >> m1 >> m2;
        vector<int> p(m1), s(m2);
        for(int i = 0; i < m1; i++){
            cin >> p[i];
        }
        for(int i = 0; i < m2; i++){
            cin >> s[i];
        }
        if(p[0] != 1 || s[m2 - 1] != n || p[m1 - 1] != s[0]) {
            cout << "0\n";
            continue;
        }
        mint ans = 1;
        mint l_amt = p[m1 - 1] - 1;
        mint r_amt = n - 1 - l_amt;
        ans *= nck(n - 1, l_amt);
        for(int i = m1 - 2; i >= 0; i--){
            mint tot = p[i + 1] - 2;
            mint amt = tot - p[i] + 1;
            ans *= nck(tot, amt);
            ans *= fac[amt];
        }
        for(int i = 1; i < m2; i++){
            mint tot = n - s[i - 1] - 1;
            mint amt = s[i] - s[i - 1] - 1;
            ans *= nck(tot, amt);
            ans *= fac[amt];
        }
        cout << ans << "\n";
    }
    
    return 0;
}
