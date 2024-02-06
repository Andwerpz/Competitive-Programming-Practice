#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//NWERC 2020 - H

//there is always a solution. 

//just sort the array, and we can do a zig-zag starting from the center. This ensures that the 
//difference is at least non-decreasing. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int l = n / 2;
    int r = l + 1;
    if(n % 2 == 0){
        l --;
        r --;
    }
    vector<int> ans(n);
    for(int i = 0; i < n; i++){
        if(i % 2 == 0){
            ans[i] = a[l --];
        }
        else {
            ans[i] = a[r ++];
        }
    }
    for(int i = 0; i < n; i++){
        cout << ans[i] << " \n"[i == n - 1];
    }
    
    return 0;
}
