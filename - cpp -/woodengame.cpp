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
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1994E

//literally just observation then greedy.

//we actually don't care about the exact structure of each tree, only the number of nodes in the tree. 
//note that for any tree, we can always reduce the number of nodes by 1 via removing a leaf. Therefore, if the initial
//size is n, we can contribute any value from 0 - n to our bitwise or sum. 

//So, first sort the trees in descending order by size, then we can just brute force try all values from 0 - n for each 
//tree and take the one that maximizes the current or sum. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int k;
        cin >> k;
        vi a(k);
        for(int i = 0; i < k; i++){
            cin >> a[i];
            for(int j = 0; j < a[i] - 1; j++){
                int p;
                cin >> p;
            }
        }
        sort(a.begin(), a.end());
        reverse(a.begin(), a.end());
        int ans = 0;
        for(int i = 0; i < k; i++){
            int nans = 0;
            for(int j = 0; j <= a[i]; j++){
                nans = max(ans | j, nans);
            }
            ans = nans;
        }
        cout << ans << "\n";
    }
    
    return 0;
}