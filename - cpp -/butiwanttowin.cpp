#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vl;

//ICPC ECNA 2025 - D

//readforces
//literally just implement the problem statement. 

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    vl a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    int ans = -1;
    ll sum = 0;
    for(int i = 0; i < n; i++) sum += a[i];
    for(int i = n - 1; i > 1; i--) {
        a[1] += a[i];
        if(a[1] > sum - a[1]) {
            ans = n - i;
            break;
        }
    }
    if(ans == -1) cout << "IMPOSSIBLE TO WIN\n";
    else cout << ans << "\n";

    return 0;
}