#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//AtCoder - ARC179A

//we can solve this using casework. 

//if k > 0, then it's always possible, as you can just put the numbers in ascending order. 
//if k <= 0, then we need to make sure that the prefix sum is always above k, as the first element is 0. 
//it's as simple as putting all the numbers in descending order, then noticing that the minimum element of the prefix sum
//is just the sum of the entire array (apart from the leading 0 that is).

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, k;
    cin >> n >> k;
    ll sum = 0;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        sum += a[i];
    }
    if(k > 0){
        sort(a.begin(), a.end());
    }
    else {
        if(sum < k) {
            cout << "No\n";
            return 0;
        }
        sort(a.begin(), a.end());
        reverse(a.begin(), a.end());
    }
    cout << "Yes\n";
    for(int i = 0; i < n; i++){
        cout << a[i] << " \n"[i == n - 1];
    }
    
    return 0;
}