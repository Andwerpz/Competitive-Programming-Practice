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

//Codeforces - 2134B

//notice that we don't need to minimize the amount of operations. 
//We can always make all numbers a multiple of k + 1 in at most k moves. Each move can
//adjust a[i] % (k + 1) by exactly 1. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, k;
        cin >> n >> k;
        vl a(n);
        ll g = k + 1;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            ll amt = a[i] % g;
            a[i] += amt * k;
            cout << a[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}