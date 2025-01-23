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

struct mint;
typedef vector<mint> vm;
typedef vector<vector<mint>> vvm;
typedef pair<mint, mint> pmm;

const ll mod = 998244353;
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
    mint operator /(const mint& other) const {return mint((val / other.val) % mod);}
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

    //returns X such that A = (B * X) % mod
    mint inv_divide(const mint& other) const {
        return *this * other.pow(mod - 2);
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

vm fac, invfac;
void fac_init(int N) {
    fac = vm(N + 1), invfac = vm(N + 1);
    fac[0] = 1;
    for(int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i;
    invfac[N] = mint(1) / fac[N];
    for(int i = N; i > 0; i--) invfac[i - 1] = invfac[i] * i;
}

template <typename T>
struct matrix {
    int n, m;
    vector<vector<T>> mat;
    matrix(int _n, int _m) {n = _n, m = _m; mat = vector(n, vector<T>(m, 0));}
    matrix(const matrix& other) {n = other.n, m = other.m, mat = other.mat;}
    vector<T>& operator [](size_t i) {return mat[i];};
    bool operator ==(const matrix& other) const {
        if(n != other.n || m != other.m) return false;
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) if(*this[i][j] != other[i][j]) return false;
        return true;
    }
    matrix<T>& operator +=(const matrix& other) {
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) *this[i][j] += other[i][j];
        return *this;
    }
    matrix<T> operator +(const matrix& other) const {matrix<T> ret(*this); ret += other; return ret;}
    matrix<T>& operator -=(const matrix& other) {
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) *this[i][j] -= other[i][j];
        return *this;
    }
    matrix<T> operator -(const matrix& other) const {matrix<T> ret(*this); ret -= other; return ret;}
    matrix<T>& operator *=(const T& other) {
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) *this[i][j] *= other;
        return *this;
    }
    matrix<T> operator *(const T& other) const {matrix<T> ret(*this); ret *= other; return ret;}
    matrix<T>& operator /=(const T& other) {
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) *this[i][j] /= other;
        return *this;
    }
    matrix<T> operator /(const T& other) const {matrix<T> ret(*this); ret /= other; return ret;}

    bool to_upper_triangular() {
        for(int i = 0; i < n; ++i) {
            // Pivot element (ensure it's non-zero)
            if(mat[i][i] == 0) {
                bool pivot_found = false;
                for(int k = i + 1; k < n; ++k) {
                    if(mat[k][i] != 0) {
                        swap(mat[i], mat[k]);
                        pivot_found = true;
                        break;
                    }
                }
                if(!pivot_found) return false;
            }
            // Eliminate all elements below the pivot
            for (int j = i + 1; j < n; ++j) {
                T factor = mat[j][i] / mat[i][i];
                for (int k = i; k < m; ++k) {
                    mat[j][k] -= factor * mat[i][k];
                }
            }
        }
        return true;
    }

    T determinant() {
        assert(n == m);
        matrix tmp(*this);
        if(!tmp.to_upper_triangular()) return 0;
        T ans = 1;
        for(int i = 0; i < n; i++) ans *= tmp[i][i];
        return ans;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    fac_init(2e6);
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    mint ans = 0;
    //iterate over how many times going around CCW
    for(int i = -max({a, b, c, d}); i <= max({a, b, c, d}); i++) {
        int ST = 0, TS = 0, TU = 0, UT = 0, UV = 0, VU = 0, VS = 0, SV = 0;
        if(i < 0) TS -= i, UT -= i, VU -= i, SV -= i;
        else ST += i, TU += i, UV += i, VS += i;
        a -= abs(i), b -= abs(i), c -= abs(i), d -= abs(i);
        if(min({a, b, c, d}) < 0) continue;
        if(a % 2 || b % 2 || c % 2 || d % 2) continue;
        ST += a / 2, TS += a / 2, TU += b / 2, UT += b / 2;
        UV += c / 2, VU += c / 2, VS += d / 2, SV += d / 2;
        matrix<mint> mat(4, 4);
        mat[0][0] = SV + ST, mat[1][1] = TS + TU, mat[2][2] = UT + UV, mat[3][3] = VU + VS;
        if(ST != 0) mat[0][1] = -1;
        if(TS != 0) mat[1][0] = -1;
        if(TU != 0) mat[1][2] = -1;
        if(UT != 0) mat[2][1] = -1;
        if(UV != 0) mat[2][3] = -1;
        if(VU != 0) mat[3][2] = -1;
        if(VS != 0) mat[3][0] = -1;
        if(SV != 0) mat[0][3] = -1;
        matrix<mint> mat3(3, 3);
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++) {
                mat3[j][k] = mat[j][k];
            }
        }
        int dS = SV + ST, dT = TS + TU, dU = UT + UV, dV = VU + VS;
        cout << "DETERMINANT : " << mat3.determinant() << "\n";
        ans += mat3.determinant() * fac[dS] * fac[dT] * fac[dU] * fac[dV];
    }
    cout << ans << "\n";
    
    return 0;
}