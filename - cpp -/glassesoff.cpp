#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//ACPC 2024 Spring Contest - G

//for each color that is under the maximum, take as many as you can. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int ans = 0;
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    for(int i = 0; i < n; i++){
        if(a[i] == a[0]) {
            continue;
        }
        ans += a[0] - 1 - a[i];
    }
    cout << ans << "\n";
    
    return 0;
}
