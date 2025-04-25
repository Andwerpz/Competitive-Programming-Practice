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

//Codeforces - 98B

//this solution doesn't work due to lack of bigint, asked chat to translate it to python

//first, observe for any n that is a power of 2, we can just flip the coin log_2(n) times. 
//however, if n is not a power of 2, then there are some outcomes of ceil(log_2(n)) flips that don't 
//correspond to a knight. 

//We can actually use the excess results that don't correspond to a knight. Just flip a few more times until 
//there are at least n excess results, and assign n of them to the knights. 

//Denote E[x] as the expected number of flips required given we start with x excess results. Note that E[1] 
//is the answer to the original problem. Then, denote k as the minimum integer such that x * 2^k >= n. Then,
//E[x] = k + (1 - n / (x * 2^k)) E[(x * 2^k) % n]
//so we need to spend k flips, and there is (1 - n / (x * 2^k)) probability that we result in a sequence that
//doesn't correspond to a knight, so we need to flip again. 

//we can solve the system of equations involving E in O(n) time. 

struct frac {
    ll num, denom;
    frac(ll _num = 0, ll _denom = 1) {num = _num, denom = _denom; reduce();}
    frac(const frac& other) {num = other.num, denom = other.denom;}
    void reduce() {ll g = gcd(num, denom); if(g != 0) {num /= g, denom /= g;}}
    frac& operator =(const frac& other) {num = other.num, denom = other.denom; return *this;}
    frac& operator +=(const frac& other) {
        ll lcm = abs(denom * other.denom) / gcd(denom, other.denom);
        num = num * (lcm / denom) + other.num * (lcm / other.denom);
        denom = lcm;
        reduce();
        return *this;
    }
    frac& operator -=(const frac& other) {*this += frac(-other.num, other.denom); return *this;}
    frac& operator *=(const frac& other) {num *= other.num, denom *= other.denom; reduce(); return *this;}
    frac& operator /=(const frac& other) {num *= other.denom, denom *= other.num; reduce(); return *this;}
    
    frac operator +(const frac& other) {return frac(*this) += other;}
    frac operator -(const frac& other) {return frac(*this) -= other;}
    frac operator *(const frac& other) {return frac(*this) *= other;}
    frac operator /(const frac& other) {return frac(*this) /= other;}

    friend std::ostream& operator<<(std::ostream& os, const frac& m) {os << m.num << "/" << m.denom; return os;}
};
frac operator +(ll a, const frac& b) {return frac(a) + b;}
frac operator -(ll a, const frac& b) {return frac(a) - b;}
frac operator *(ll a, const frac& b) {return frac(a) * b;}
frac operator /(ll a, const frac& b) {return frac(a) / b;}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    //find cycle  
    set<int> s;
    vi S(1, 1), ST(0), C(0);
    //E[i] = (n / ST[i]) * C[i] + (1 - n / ST[i]) * (C[i] + E[i + 1])
    //E[i] = (1 - n / ST[i]) * E[i + 1] + C[i] 
    //E[i] = A[i] * E[i + 1] + B[i]
    //A[i] = (1 - n / ST[i])
    //B[i] = (n / ST[i]) * C[i] + (1 - n / ST[i]) * C[i] = C[i]
    vector<frac> A(0), B(0), E(0);  
    while(true) {
        int cur = *S.rbegin(), cnt = 0;
        s.insert(cur);
        while(cur < n) cur *= 2, cnt ++;
        ST.push_back(cur);
        C.push_back(cnt);
        cur %= n;
        S.push_back(cur);
        A.push_back(1 - frac(n, *ST.rbegin()));
        B.push_back(*C.rbegin());
        E.push_back({0});
        if(s.count(cur) || cur == 0) break;
    }
    for(int i = 0; i < ST.size(); i++){
        cout << S[i] << " " << C[i] << " " << ST[i] << "\n";
    }
    for(int i = 0; i < ST.size(); i++){
        cout << "E[" << S[i] << "] = " << A[i] << " E[" << S[i + 1] << "] + " << B[i] << "\n";
    }
    //close the cycle
    if(*S.rbegin() != 0){
        int last = *S.rbegin();
        S.pop_back();
        while(*S.rbegin() != last) {
            //E[i - 1] = A[i - 1] * (A[i] * E[i + 1] + B[i]) + B[i - 1]
            //E[i - 1] = A[i - 1] * A[i] * E[i + 1] + A[i - 1] * B[i] + B[i - 1]
            int i = S.size() - 1;
            frac na = A[i - 1] * A[i];
            frac nb = A[i - 1] * B[i] + B[i - 1];
            A[i - 1] = na, B[i - 1] = nb;
            S.pop_back();
            ST.pop_back();
            C.pop_back();
            A.pop_back();
            B.pop_back();
            E.pop_back();
        }
        //E[i] = A[i] * E[i] + B[i]
        //E[i] = B[i] / (1 - A[i])
        cout << "CLOSE CYCLE : " << *B.rbegin() / (1 - *A.rbegin()) << "\n";
        *E.rbegin() = *B.rbegin() / (1 - *A.rbegin());
    }
    else {
        *E.rbegin() = *C.rbegin();  //E[0] = 0, E[2^C] = C
    }
    //everything else
    for(int i = (int) E.size() - 2; i >= 0; i--){
        E[i] = A[i] * E[i + 1] + B[i];
    }
    cout << E[0] << "\n";
    
    return 0;
}