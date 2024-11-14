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

//Codeforces - 2035B

//for small n, just hardcode. 

//note that if something is divisible by 66, then it's also divisible by 33, so we only have to 
//worry about 2, 3, and 11 divisibility. 

//3 is automatically good, because we can only use 3 and 6. 
//for 2, the last digit has to be 6. 
//for 11, the sums of odd and even digits have to be the same, so we can do some hardcoding
//there. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        if(n == 1){
            cout << "-1\n";
            continue;
        }
        else if(n == 2){
            cout << "66\n";
            continue;
        }
        else if(n == 3){
            cout << "-1\n";
            continue;
        }
        string ans(n, '3');
        if(n % 2 == 0){
            ans[n - 1] = '6';
            ans[n - 2] = '6';
        }
        else {  
            ans[n - 1] = '6';
            ans[n - 2] = '6';
            ans[n - 4] = '6';
        }
        cout << ans << "\n";
    }
    
    return 0;
}