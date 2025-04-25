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

//Codeforces - 2084A

//for odd n, you can print 
//n, 1, 2, 3, ..., n - 1
//note that this works for odd n as (n mod 2) = 1

//for even n, I guessed that this can never work. Intuition is that there is nowhere to place n. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        if(n % 2 == 0) {
            cout << "-1\n";
            continue;
        }
        cout << n << " ";
        for(int i = 1; i < n; i++) cout << i << " ";
        cout << "\n";
    }
    
    return 0;
}