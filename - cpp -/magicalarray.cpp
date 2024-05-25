#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1704D

//let's take a look at the prefix sum of an array after performing a type 1 operation on it:
//a      : [0, 1, 1, 0, 0] -> [1, 0, 0, 1, 0]
//pfx(a) : [0, 1, 2, 2, 2] -> [1, 1, 1, 2, 2]
//notice that if you sum all the elements in pfx(a) before and after the operation, the sum does not change. 
//(proof is left to the reader)

//now, let's take a look at what happens during a type 2 operation:
//a      : [0, 1, 1, 0, 0] -> [1, 0, 0, 0, 1]
//pfx(a) : [0, 1, 2, 2, 2] -> [1, 1, 1, 1, 2]
//notice that now, the sum goes down by exactly 1 (if you proved the above, this one should be pretty obvious). 

//So, we just have to identify the array that has the minimum prefix sum-sum, and the difference between the small
//sum and the actual sum is exactly the amount of type 2 operations. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<vector<ll>> a(n, vector<ll>(m));
        vector<ll> sums(n, 0);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cin >> a[i][j];
            }
            //take pfx sum
            for(int j = 1; j < m; j++){
                a[i][j] += a[i][j - 1];
            }
            for(int j = 0; j < m; j++){
                sums[i] += a[i][j];
            }
        }
        ll mn = sums[0];
        ll mx = sums[0];
        int mn_ind = 0;
        for(int i = 0; i < n; i++){
            mx = max(mx, sums[i]);
            if(sums[i] < mn) {
                mn = sums[i];
                mn_ind = i;
            }
        }
        cout << mn_ind + 1 << " " << mx - mn << "\n";
    }
    
    return 0;
}