#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1042E

//we can sort the cells in ascending order by value, and determine each of their EVs. 
//the EV of a cell is simply the average of the EVs + squared distances of cells with lower values. 
//it can be written as sum(EV + (R - r)^2 + (C - c)^2) / cnt, where R, C is the coordinates of other cells, 
//and r, c is coordinates of the cell we're currently calculating. cnt is the number of such cells. 

//we can of course expand the sum, and we get sum(EV) + sum(R^2 + r^2 - 2Rr) + sum(C^2 + c^2 - 2Cc). 
//it's relatively easy to keep track of the sum of row and column indexes. Note that when processing cells of 
//equal value, we must process them all at the same time, and update the sums last. 

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<mint>> a(n * m, vector<mint>(3)); //{val, row, col}
    for(int i = 0; i < n * m; i++){
        cin >> a[i][0];
        a[i][1] = i / m;
        a[i][2] = i % m;
    }
    int r_t, c_t;
    cin >> r_t >> c_t;
    r_t --;
    c_t --;
    sort(a.begin(), a.end());
    mint R2_sum = 0, R_sum = 0;
    mint C2_sum = 0, C_sum = 0;
    mint EV_sum = 0;
    mint cnt = 0;
    vector<mint> ev(a.size(), 0);
    for(int i = 0; i < a.size();){
        mint val = a[i][0];
        int r_b = i;
        while(r_b != a.size() && a[r_b][0] == a[i][0]) {
            r_b ++;
        }
        for(int j = i; j < r_b; j++){
            mint r = a[j][1];
            mint c = a[j][2];
            ev[j] = EV_sum + R2_sum + C2_sum + (r * r * cnt) + (c * c * cnt) - (2 * R_sum * r) - (2 * C_sum * c);
            ev[j] = ev[j].inv_divide(cnt);
        }
        for(int j = i; j < r_b; j++){
            mint r = a[j][1];
            mint c = a[j][2];
            R2_sum += r * r;
            R_sum += r;
            C2_sum += c * c;
            C_sum += c;
            EV_sum += ev[j];
            cnt += 1;
        }
        i = r_b;
    }
    mint ans = 0;
    for(int i = 0; i < a.size(); i++){
        if(a[i][1] == r_t && a[i][2] == c_t) {
            ans = ev[i];
            break;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
