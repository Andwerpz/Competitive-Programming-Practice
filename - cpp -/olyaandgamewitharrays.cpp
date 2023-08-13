#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1859B

//we can use one array as our 'dump' array, and just move all the minimum elements from all other arrays to this array. 

//we can test each array as being the 'dump' array, and take the maximum answer. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<vector<ll>> a(n, vector<ll>(0));
        ll ssum = 0;
        ll mn = 1e18;
        for(int i = 0; i < n; i++){
            int m;
            cin >> m;
            for(int j = 0; j < m; j++){
                ll next;
                cin >> next;
                a[i].push_back(next);
            }
            sort(a[i].begin(), a[i].end());
            ssum += a[i][1];
            mn = min(mn, a[i][0]);
        }
        ll ans = 0;
        for(int i = 0; i < n; i++){
            ans = max(ans, ssum - a[i][1] + mn);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
