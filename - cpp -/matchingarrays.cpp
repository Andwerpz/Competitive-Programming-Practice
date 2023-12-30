#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1896C

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, x;
        cin >> n >> x;
        vector<int> a(n), b(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        for(int i = 0; i < n; i++){
            cin >> b[i];
        }
        vector<pair<int, int>> ord_a(n, {0, 0});
        for(int i = 0; i < n; i++){
            ord_a[i] = {a[i], i};
        }
        sort(ord_a.begin(), ord_a.end());
        sort(b.begin(), b.end());
        vector<int> ans(n);
        for(int i = 0; i < n; i++){
            ans[ord_a[i].second] = b[(i + x) % n];
        }
        int cnt = 0;
        for(int i = 0; i < n; i++){
            cnt += a[i] > ans[i];
        }
        cout << (cnt == x? "YES" : "NO") << "\n";
        if(cnt == x){
            for(int i = 0; i < n; i++){
                cout << ans[i] << " \n"[i == n - 1];
            }
        }
    }
    
    return 0;
}
