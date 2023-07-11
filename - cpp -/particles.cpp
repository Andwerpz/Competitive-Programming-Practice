#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1844C

//consider trying to maximize the value of one particle. Note that we can only combine with that particle
//every other particle starting with the target particle. 

//observe that we don't have to take a subarray of every other particle, we can just take any selection, so
//we can just choose all positive particles from the odd and even index sets. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<ll> a(n);
        ll ans = -1e18;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            ans = max(ans, a[i]);
        }
        ll sum = 0;
        for(int i = 0; i < n; i += 2){
            if(a[i] >= 0){
                sum += a[i];
                ans = max(ans, sum);
            }
        }
        sum = 0;
        for(int i = 1; i < n; i += 2){
            if(a[i] >= 0){
                sum += a[i];
                ans = max(ans, sum);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
