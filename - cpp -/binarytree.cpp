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

//Kattis - binarytree

//First, S will determine our starting node. Then, imagine considering each move in T one by one in order, maintaining
//all the nodes that are reachable using some subsequence of the moves considered so far. This group of reachable
//nodes will always form a connected component, and there are some other properties that make the size of this group
//nicely countable. 

//denote 'ls' (left surface) as the amount of unvisitable nodes just one L move away from a visitable node, and 
//'rs' (right surface) as the amount of unvisitable nodes just one R move away from a visitable node. We'll analyze 
//what happens to them when we actually perform a L, R, or U move:
// - L move:
// This adds ls to the total size of the set. ls doesn't change, but rs increments by ls. 
// - R move:
// This adds rs to the total size of the set. rs doesn't change, but ls increments by rs
// - U move:
// If we still have nodes above us, this adds 1 to ls or rs depending on whether we move up from a right or left 
// child respectively, and adds 1 to the answer. Otherwise, it does nothing. 

struct mint;
typedef vector<mint> vm;
typedef vector<vector<mint>> vvm;
typedef pair<mint, mint> pmm;

const ll mod = 21092013;
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int casi = 0;
    int t;
    cin >> t;
    while(t--){
        casi ++;
        string a, b;
        cin >> a >> b;
        {
            string tmp = "";
            for(int i = 0; i < a.size(); i++){
                if(a[i] == 'L') tmp.push_back('L');
                else if(a[i] == 'R') tmp.push_back('R');
                else {
                    if(tmp.size() != 0) tmp.pop_back();
                }
            }
            a = tmp;
        }
        mint ls = 1, rs = 1;
        int aptr = a.size();
        mint ans = 1;
        for(int i = 0; i < b.size(); i++){
            // cout << "B[i] : " << b[i] << "\n";
            if(b[i] == 'L') {
                ans += ls;
                rs += ls;
            }
            else if(b[i] == 'R') {
                ans += rs;
                ls += rs;
            }
            else {
                //b[i] = 'U'
                if(aptr == 0) continue;
                aptr --;
                if(a[aptr] == 'L') rs += 1;
                else ls += 1;
                ans += 1;
            }
            // cout << "LS RS : " << ls << " " << rs << "\n";
        }
        cout << "Case " << casi << ": " << ans << "\n";
    }
    
    return 0;
}