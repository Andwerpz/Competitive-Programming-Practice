#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Kattis - cocktail

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, t;
    cin >> n >> t;
    vector<int> a(n);    //{drink time, duration}
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int dline = 1e9;
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    int cur = 0;
    for(int i = 0; i < n; i++){
        cur += t;
        dline = min(dline, cur + a[i] - 1);
    }
    cout << (cur > dline? "NO" : "YES") << "\n";
    
    return 0;
}
