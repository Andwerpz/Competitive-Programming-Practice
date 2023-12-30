#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Rocky Mountain Regional 2016 C

//greedily choose the password which has the highest likelyhood

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ld> p(n);
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        cin >> p[i];
    }
    sort(p.begin(), p.end());
    reverse(p.begin(), p.end());
    ld ans = 0;
    for(int i = 0; i < n; i++){
        ans += p[i] * (i + 1);
    }
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}
