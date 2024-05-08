#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Codeforces - 1924C

//most important observation is to note that any fold beyond the first one is going to add
//equally to the valley and mountain lengths. 

//to show that this is true, we can shade one side of the paper. If we 
//fold the paper in a way that we fold two shaded sections together, we're creating a valley
//fold, otherwise we're creating a mountain fold. Notice that since the first fold will 'double up'
//all the portions of paper, from the second fold onwards, any fold we do is going to have equal
//parts 'shaded together' and 'unshaded together'. 

//let's define V(n) as the length of valley creases after n folds. V(1) = 4 / sqrt(2), and
//V(n), where n > 1 is V(n - 1) + 2^(n - 2) * 4 / sqrt(2)^n
//next, due to the doubling up property mentioned above, M(n) = V(n) - 4 / sqrt(2). 

//notice that the question is asking us to compute the coefficient for the irrational portion of 
//M(n) / V(n), which is equivalent to (V(n) - 4 / sqrt(2)) / V(n). From here, we can do some geometric
//series analysis to represent V(n) in closed form, then rationalize the denominator to get 
//our answer. 

ll mod = 999999893;

//modular int
struct mint {
    ll val;
    mint(ll _val = 0) {val = _val;}
    mint(const mint& other) {val = other.val;}
    bool operator ==(const mint& other) {return val == other.val;}
    bool operator ==(ll other) {return val == other;}
    bool operator !=(const mint& other) {return val != other.val;}
    bool operator !=(ll other) {return val != other;}
    mint& operator =(const mint& other) {val = other.val; return *this;}
    mint& operator =(ll other) {val = other; return *this;}
    mint operator +(const mint& other) {ll ret = val + other.val; while(ret >= mod) {ret -= mod;} return mint(ret);}
    mint operator +(ll other) {ll ret = val + other; while(ret >= mod) {ret -= mod;} return mint(ret);}
    mint& operator +=(const mint& other) {*this = *this + other; return *this;}
    mint& operator +=(ll other) {*this = *this + other; return *this;}
    mint operator -(const mint& other) {ll ret = val - other.val; while(ret < 0) {ret += mod;} return mint(ret);}
    mint operator -(ll other) {ll ret = val - other; while(ret < 0) {ret += mod;} return mint(ret);}
    mint& operator -=(const mint& other) {*this = *this - other; return *this;}
    mint& operator -=(ll other) {*this = *this - other; return *this;}
    mint operator *(const mint& other) {return mint((val * other.val) % mod);}
    mint operator *(ll other) {return mint((val * other) % mod);}
    mint& operator *=(const mint& other) {*this = *this * other; return *this;}
    mint& operator *=(ll other) {*this = *this * other; return *this;}
    mint operator /(const mint& other) {return mint((val / other.val) % mod);}
    mint operator /(ll other) {return mint((val / other) % mod);}
    mint& operator /=(const mint& other) {*this = *this / other; return *this;}
    mint& operator /=(ll other) {*this = *this / other; return *this;}
    mint operator %(const mint& other) {return mint(val % other.val);}
    mint operator %(ll other) {return mint(val % other);}
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
    mint inv_divide(const mint& other){
        return *this * other.pow(mod - 2);
    }

    friend std::ostream& operator<<(std::ostream& os, const mint& m) {os << m.val; return os;}
    friend std::istream& operator>>(std::istream& is, mint& m) {is >> m.val; return is;}
};
bool operator ==(ll a, const mint& b) {return a == b.val;}
bool operator !=(ll a, const mint& b) {return a != b.val;}
mint operator +(ll a, const mint& b) {ll ret = a + b.val; while(ret >= mod) {ret -= mod;} return mint(ret);}
mint operator -(ll a, const mint& b) {ll ret = a - b.val; while(ret < 0) {ret += mod;} return mint(ret);}
mint operator *(ll a, const mint& b) {return mint((a * b.val) % mod);}
mint operator /(ll a, const mint& b) {return mint((a / b.val) % mod);}
mint operator %(ll a, const mint& b) {return mint(a % b.val);}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        ll n;
        cin >> n;
        if(n == 1){
            cout << "0\n";
            continue;
        }
        mint d_rat, d_irrat, n_rat, n_irrat;
        if(n % 2 == 0){
            n_rat = mint(2 * mint(2).pow(n / 2) - 2);
            n_irrat = mint(mint(2).pow(n / 2) - 2);
            d_rat = mint(2 * mint(2).pow(n / 2) - 2);
            d_irrat = mint(mint(2).pow(n / 2));
        }
        else {
            n_rat = mint(mint(2).pow((n + 1) / 2) - 2);
            n_irrat = mint(2 * mint(2).pow((n - 1) / 2) - 2);
            d_rat = mint(mint(2).pow((n + 1) / 2) - 2);
            d_irrat = mint(2 * mint(2).pow((n - 1) / 2));
        }
        //rationalize denominator
        mint n_f(n_irrat * d_rat - n_rat * d_irrat);
        mint d_f(d_rat * d_rat - 2 * d_irrat * d_irrat);
        cout << n_f.inv_divide(d_f) << "\n";
    }
    
    return 0;
}
