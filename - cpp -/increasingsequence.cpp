#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1882A

//implementation. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int ans = 0;
        for(int i = 0; i < n; i++){
            ans ++;
            int a;
            cin >> a;
            if(a == ans){
                ans ++;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
