#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1987B

//for each element, you can first identify how many operations are required for it to be equal to
//the maximum element to it's left. 

//then, just compute the cost. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<ll> inc(0);
        for(int i = 1; i < n; i++){
            if(a[i] < a[i - 1]) {
                ll diff = a[i - 1] - a[i];
                a[i] += diff;
                inc.push_back(diff);
            }
        }
        sort(inc.begin(), inc.end());
        ll ans = 0;
        for(int i = 0; i < inc.size(); i++){
            ll amt = inc.size() - i;
            ll ops = inc[i];
            if(i != 0){
                ops -= inc[i - 1];
            }
            ans += (amt + 1) * ops;
        }
        cout << ans << "\n";
    }
    
    return 0;
}