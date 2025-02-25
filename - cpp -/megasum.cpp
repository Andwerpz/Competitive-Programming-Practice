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

//Topcoder - 10710

//kinda annoying impl problem. Be careful about overflow. 

//first, given some N, how can we find the coordinates? Consider the 'rings' of increasing values. Within the ith
//ring (0-indexed), there are (i + 1)^2 values, so N will fall within around the first sqrt(N) rings. Therefore
//we can just brute force check them all. 

//This also means that the maximum coordinate is sqrt(N), which is around 10^5, which is pretty nice. 

//To compute the sum, we can split it into 3 parts, the rectangle, the square, and the effect of the rectangle
//on the square. WLOG, i'll assume that c >= r, but the process for r >= c is very similar. 

//For the rectangle, observe that the contribution from each row can be computed with knowledge of the contribution
//from the row below. So we just have to go through the bottom row, and then the remaining row contributions can
//be computed in O(1) time. 

//For the effect of the rectangle on the square, we can adopt the same row-by-row technique as the rectangle, and 
//since the sums all start from the rectangle, it's pretty easy. We just have to compute for each row the sum. 

//For the square, we can consider all the cells to the left, above, and on the diagonal seperately. To make 
//implementation easier, we can simply double count the diagonal, then uncount it when we consider the diagonal. 

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
    mint operator +(const mint& other) const {ll ret = val + other.val; while(ret < 0) {ret += mod;} while(ret >= mod) {ret -= mod;} return mint(ret);}
    mint operator +(ll other) const {return *this + mint(other);}
    mint& operator +=(const mint& other) {*this = *this + other; return *this;}
    mint& operator +=(ll other) {*this = *this + other; return *this;}
    mint operator -(const mint& other) const {ll ret = val - other.val; while(ret < 0) {ret += mod;} while(ret >= mod) {ret -= mod;} return mint(ret);}
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

//sum of elements in arithmetic sequence from start to start + (nr_elem - 1) * inc
mint arith_sum(ll start, ll nr_elem, ll inc) {
    mint ans = start * nr_elem;
    ans += mint(inc) * mint(nr_elem) * mint(nr_elem - 1) / 2;
    return ans;
}

//relative to top left corner, so query_val(0, 0) = 1, query_val(0, 1) = 2
mint query_val(ll r, ll c) {
    //find where it is relative to diagonal, determine value that way
    if(max(r, c) % 2) swap(r, c);
    ll ring = max(r, c);
    ll val = ring * ring + ring + 1;
    if(r < ring) val += ring - r;
    else val -= ring - c;
    return val;
}

class MegaSum {
public:
    int calculate(ll N) {
        //find coordinates of N
        ll r = -1, c = -1;
        {
            ll ring = -1;
            for(ll i = 1; i <= N; i++) if(N <= i * i) {ring = i - 1; break;}
            ll mid = ring * ring + ring + 1;
            if(N < mid) r = ring, c = ring - mid + N;
            else r = ring - N + mid, c = ring;
            if(ring % 2) swap(r, c);
        }
        //split into two parts, the square and rectangle
        mint ans = 0;
        //square
        {   
            ll s = min(r, c);
            // - left of diagonal
            {
                mint csum = 0, add = 0;
                for(ll i = s; i >= 0; i--){
                    csum += add;
                    csum += mint(i * i + i + 1) * (s - i + 1);
                    add += (i % 2? 1 : -1) * (s - i + 1);
                    ans += csum * (s - i + 1);
                }
            }
            // - top of diagonal
            {
                mint rsum = 0, add = 0;
                for(ll i = s; i >= 0; i--){
                    rsum += add;
                    rsum += mint(i * i + i + 1) * (s - i + 1);
                    add += (i % 2? -1 : 1) * (s - i + 1);
                    ans += rsum * (s - i + 1);
                }
            }
            // - on diagonal, account for doublecounting
            for(ll i = 0; i <= s; i++){
                ans -= mint(i * i + i + 1) * mint(s - i + 1) * mint(s - i + 1);
            }
        }
        //rectangle
        {   
            //generate first row/col sum, and compute differences.
            if(r >= c){ //rectangle is on bottom of square
                mint csum = 0, add = 0;
                for(int i = 0; r - i > c; i++){
                    csum += query_val(r - i, c) * (i + 1);
                    add += (i + 1) * ((r - i) % 2? 1 : -1);
                }
                for(int i = c; i >= 0; i--){
                    ans += csum * (c - i + 1);
                    csum += add;
                }
            }
            else {  //rectangle is to the right of square
                mint rsum = 0, add = 0;
                for(int i = 0; c - i > r; i++){
                    rsum += query_val(r, c - i) * (i + 1);
                    add += (i + 1) * ((c - i) % 2? -1 : 1);
                }
                for(int i = r; i >= 0; i--){
                    ans += rsum * (r - i + 1);
                    rsum += add;
                }
            }
        }
        //rectangle -> square
        {
            if(r >= c){ //rectangle is on bottom of square
                vm csum(c + 1);
                for(ll i = 0; i <= c; i++){
                    ll l = i * i + i + 1;
                    if(i % 2 == 1) l -= i;
                    csum[i] += arith_sum(l, i + 1, 1); 
                }
                mint sum = 0, add = 0;
                for(ll i = c; i >= 0; i--){
                    csum[i] += sum;
                    if(i != 0){
                        sum += add;
                        sum += query_val(i, i - 1);
                        add += (i % 2? 1 : -1);
                    }
                }
                for(int i = 0; i <= c; i++){
                    ans += csum[i] * (r - c) * (c - i + 1);
                }
            }
            else {  //rectangle is to the right of square
                vm rsum(r + 1);
                for(ll i = 0; i <= r; i++){
                    ll l = i * i + i + 1;
                    if(i % 2 == 0) l -= i;
                    rsum[i] += arith_sum(l, i + 1, 1); 
                }
                mint sum = 0, add = 0;
                for(ll i = r; i >= 0; i--){
                    rsum[i] += sum;
                    if(i != 0){
                        sum += add;
                        sum += query_val(i - 1, i);
                        add += (i % 2? -1 : 1);
                    }
                }
                for(int i = 0; i <= r; i++){
                    ans += rsum[i] * (c - r) * (r - i + 1);
                }
            }
        }
        return (int) ans.val;
    }
};

signed main() {
    long long arg0;
    cin >> arg0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    auto c = MegaSum();
    int ret = c.calculate(arg0);
    cout << ret;
}