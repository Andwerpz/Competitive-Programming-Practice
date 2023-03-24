#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        ll ans = INT32_MAX;
        for(int i = 1; i < a.size() - 1; i++){
            ll next = a[i + 1] - a[i] + a[i] - a[i - 1];
            ans = min(ans, next);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
