#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1856A

//note that the answer is either 0, or an element of the array. 

//since n is so small, we can just try all elements of the array. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n + 1);
        a[0] = 0;
        for(int i = 1; i <= n; i++){
            cin >> a[i];
        }
        n ++;
        int ans = 1e9;
        for(int i = 0; i < n; i++){
            vector<int> b(n, 0);
            int next = a[i];
            for(int j = 0; j < n; j++){
                b[j] = max(0, a[j] - next);
            }
            bool isValid = true;
            for(int i = 1; i < n; i++){
                if(b[i] < b[i - 1]){
                    isValid = false;
                    break;
                }
            }
            if(isValid) {
                ans = min(ans, next);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
