#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces 1669H

//just greedily make the max bit 1. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        vector<int> bits(32);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            for(int j = 0; j < 32; j++){
                if(a[i] % 2 == 1){
                    bits[j] ++;
                }
                a[i] /= 2;
            }
        }
        ll ans = 0;
        for(int i = 30; i >= 0; i--){
            int req = n - bits[i];
            if(k >= req){
                k -= req;
                ans += ((ll)1 << i);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
