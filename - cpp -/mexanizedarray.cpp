#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1870A

//just allocate enough numbers to get the mex equal to k, then make all the other numbers
//as high as possible. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k, x;
        cin >> n >> k >> x;
        if(n < k) {
            cout << "-1\n";
            continue;
        }
        if(x + 1 < k) {
            cout << "-1\n";
            continue;
        }
        int ans = k * (k - 1) / 2;
        if(x == k){
            ans += (x - 1) * (n - k);
        }
        else {
            ans += x * (n - k);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
