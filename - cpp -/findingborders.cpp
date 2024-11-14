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

//CSES - 1732

//string hashing. 

const ll mod = 1e9 + 7;
ll binexp(ll a, ll b) {
    ll res = 1;
    ll p = a;
    while(b != 0){
        if(b % 2){
            res = (res * p) % mod;
        }
        p = (p * p) % mod;
        b /= 2;
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s;
    cin >> s;
    ll p = 31;
    ll pfx = 0;
    ll sfx = 0;
    int n = s.size();
    for(int i = 0; i < n - 1; i++){
        pfx = (pfx * p) % mod;
        pfx = (pfx + s[i] - 'a') % mod;
        sfx = (sfx + ((s[n - i - 1] - 'a') * binexp(p, i)) % mod) % mod;
        if(pfx == sfx){
            cout << i + 1 << " ";
        }
    }
    cout << "\n";
    
    return 0;
}