#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1700C

//we can do a suf, pref, and add pass. 

//on the suffix pass, just transform a into a non-increasing array, so that on the pref pass, we can 
//make all the numbers equal. 

//then we just add the offset on the add pass. 

//i have no idea why this works, consult the tutorial for more info. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        ll sub = 0;
        ll ans = 0;
        for(int i = 0; i < n - 1; i++){
            if(a[i] < a[i + 1]){
                sub += a[i + 1] - a[i];
            }
        }
        ans = sub + a[0];
        cout << ans << "\n";
    }
    
    return 0;
}
