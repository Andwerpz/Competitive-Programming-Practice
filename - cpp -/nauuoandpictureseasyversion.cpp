#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 564C1

//we can solve this with dp. dp[i][j][k] = expected value of weight k, given that i seconds have passed, and
//the sum of all weights is j. 

struct mint;
vector<mint> fac;
map<pair<mint, mint>, mint> nckdp;

ll mod = 998244353;
struct mint {
    ll val;
    mint(ll _val = 0) {val = (_val + mod) % mod;}
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<int> like(n, false);
    vector<mint> w(n);
    for(int i = 0; i < n; i++){
        cin >> like[i];
    }
    ll w_total = 0;
    for(int i = 0; i < n; i++){
        cin >> w[i];
        w_total += w[i];
    }
    vector<vector<mint>> p(m + 1, vector<mint>(w_total + m + 1, 0));
    p[0][w_total] = 1;
    vector<vector<vector<mint>>> e(m + 1, vector<vector<mint>>(w_total + m + 1, vector<mint>(n, 0)));
    for(int i = 0; i < n; i++){
        e[0][w_total][i] = w[i];
    }
    for(int i = 0; i < m; i++){
        for(int j = 0; j < e[0].size(); j++){
            if(p[i][j] == 0){
                continue;
            }
            for(int ii = 0; ii < n; ii++){
                //we've selected element ii
                int csum = j + (like[ii]? 1 : -1);
                mint prob = e[i][j][ii].inv_divide(j) * p[i][j];
                if(prob == 0){
                    continue;
                }
                mint n_prob = p[i + 1][csum] + prob;
                mint inv_n_prob = mint(1).inv_divide(n_prob);
                for(int jj = 0; jj < n; jj++){
                    mint cur = e[i][j][jj];
                    if(jj == ii) {
                        if(like[ii]) {
                            cur += 1;
                        }
                        else {
                            cur -= 1;
                        }
                    }
                    e[i + 1][csum][jj] = (e[i + 1][csum][jj] * (n_prob - prob) + cur * prob) * inv_n_prob;
                }
                p[i + 1][csum] += prob;
            }
        }
    }
    vector<mint> ans(n, 0);
    mint psum = 0;
    for(int i = 0; i < e[m].size(); i++){
        psum += p[m][i];
        for(int j = 0; j < n; j++){
            ans[j] += e[m][i][j] * p[m][i];
        }
    }
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << "\n";
    }
    
    return 0;
}