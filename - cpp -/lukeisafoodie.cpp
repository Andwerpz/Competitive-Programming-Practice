#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1704B

//we want to partition the array into the minimum number of segments such that each segment has a range no
//greater than 2 * x + 1. 

//notice that we can do this greedily, here is my attempt at a proof:
//the first element has to be a part of a segment, so why not extend that segment as far right as you can. 
//once you can't extend it anymore, the element right after that needs to be part of a segment, so likewise, extend
//that one as far right as possible as well. 
//you can just keep doing this until you reach the end of the array. 

//(i know this is not a very rigorous proof, but i think it gets the idea across)

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, x;
        cin >> n >> x;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int mn = a[0];
        int mx = a[0];
        int ans = 0;
        for(int i = 1; i < n; i++){
            mn = min(mn, a[i]);
            mx = max(mx, a[i]);
            if(mx - mn + 1 > 2 * x + 1){
                ans ++;
                mn = a[i];
                mx = a[i];
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}