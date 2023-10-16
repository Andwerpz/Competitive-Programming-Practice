#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//2023 Columbia University Local Contest A

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    int k;
    cin >> k;
    vector<int> a(n);
    int ans = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        ans += a[i];
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    for(int i = 0; i < k; i++){
        ans += a[i];
    }
    cout << ans << "\n";
    
    return 0;
}
