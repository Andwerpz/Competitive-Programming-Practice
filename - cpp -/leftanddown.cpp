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

//Codeforces - 2125B

//observe that you can always get a cost of at most 2. Just pick (0, 1) and (1, 0). 

//when can you get a cost of 1? it's when you can use one type of move to go directly to (0, 0). 
//to find the minimum step you can take directly towards (0, 0), just take the gcd between a and b. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll a, b, k;
        cin >> a >> b >> k;
        ll g = gcd(a, b);
        a /= g, b /= g;
        if(max(a, b) <= k) cout << "1\n";
        else cout << "2\n";
    }
    
    return 0;
}