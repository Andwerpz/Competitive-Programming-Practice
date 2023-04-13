#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1690E

//notice that you can express the cost of an item as xk + r, where x is an arbitrary positive integer. 
//notice that the x part will always be included in the final value sum, but the r, or remainder, depends
//on which other item you add it to. 

//once you get all the remainders, try to create as many pairs as possible where the sum is greater than or equal to k. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, k;
        cin >> n >> k;
        ll ans = 0;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            ans += a[i] / k;
            a[i] %= k;
        }
        sort(a.begin(), a.end());
        int l = 0;
        int r = n - 1;
        while(l < r){
            if(a[l] + a[r] >= k){
                ans ++;
                l ++;
                r --;
            }
            else {
                l ++;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
