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

//AtCoder - AGC45A

//since it seems relatively easy for player 1 compared to player 0, let's analyze from
//player 0's perspective. 

//if the last player to move is player 1, then player 0 always loses. If player 0
//is the last player to move, then when coming into the last move, player 0 wants
//x to be either 0 or a[n]. Then, if player 0 has a suffix of last moves, then
//player 0 will want the value of x going into the suffix to be representable by 
//the xor sum of some subset of values in the suffix. 

//actually, this pattern continues. Maintain a xor basis and iterate from the last to
//first move. When we see a player 0 move, add to the xor basis, and when we see a 
//player 1 move, check if it's representable by the xor basis. 

bool insertBasis(vector<ll>& basis, ll x){
    for(int i = 0; i < basis.size(); i++){
        if((x & 1ll << i) == 0) continue;
        if(!basis[i]) {basis[i] = x; return true;}
        x ^= basis[i];
    }
    return false;
}

bool inBasis(vector<ll>& basis, ll x){
    for(int i = 0; i < basis.size(); i++)
        if(x & 1ll << i) x ^= basis[i];
    return x == 0;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vl b(60, 0), a(n);
        for(ll& x : a) cin >> x;
        string s;
        cin >> s;
        bool is_valid = true;
        for(int i = n - 1; i >= 0; i--){
            if(s[i] - '0') {if(!inBasis(b, a[i])) is_valid = false;}
            else insertBasis(b, a[i]);
        }
        cout << !is_valid << "\n";
    }
    
    return 0;
}