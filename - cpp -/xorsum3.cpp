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

//AtCoder - ABC141F

//let A and B be the xor sum of the red and blue integers respectively, and X = A ^ B, or otherwise X is the xor sum
//of all the integers. 

//any bit that is on in X, exactly one of A or B must have it on (definition of xor). This leaves the bits that are
//off in X that we can actually maximize. 

//first, go through all integers and use X as a mask to turn any bits that are on in X, off. Since we want to maximize 
//the remaining bits, we can just construct an xor basis and construct the maximum value of the remaining bits we can
//get by choosing a subset of integers. Note that we automatically are not considering choosing the entire array or 
//no elements, as that would give us a result of 0. 

const int B = 60;
bool basisInsert(vl& b, ll x){
    for(int i = B - 1; i >= 0; i--){
        if((x & (1ll << i)) == 0) continue;
        if(!b[i]) {b[i] = x; return true;}
        x ^= b[i];
    }
    return false;
}

bool inBasis(vl& b, ll x){
    for(int i = B - 1; i >= 0; i--)
        if(x & (1ll << i)) x ^= b[i];
    return x == 0;
}

ll basisMax(vl& b) {
    ll ans = 0;
    for(int i = B - 1; i >= 0; i--) if(b[i] && !(ans & (1ll << i))) ans ^= b[i];
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vl a(n);
    for(ll& x : a) cin >> x;
    ll xsum = 0;
    for(ll x : a) xsum ^= x;
    vl b(B, 0);
    for(ll x : a) {
        for(int j = 0; j < B; j++){
            if(x & (1ll << j) && xsum & (1ll << j)) x ^= (1ll << j);
        }
        basisInsert(b, x);
    }
    ll ans = xsum + basisMax(b) * 2;
    cout << ans << "\n";
    
    return 0;
}