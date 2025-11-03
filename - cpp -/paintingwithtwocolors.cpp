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

//Codeforces - 2134A

//if a > b, then both segments need to be centered.
//otherwise, the blue segment can completely cover the red one, and just the blue one has to be centered. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, a, b;
        cin >> n >> a >> b;
        bool ans = true;
        if(b < a) ans &= (n % 2) == (a % 2);
        ans &= (n % 2) == (b % 2);
        cout << (ans? "YES" : "NO") << "\n";
    }
    
    return 0;
}