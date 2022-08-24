#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1698B

//if k >= 2, then whenever you increase a_i, you also will increase either a_(i + 1) or a_(i - 1). 
//this means that through operations, you can't cause a pile to be too tall. 

//this leaves k = 1. With k = 1, you can make any pile to be too tall. Thus, the maximum amount of piles
//in this case is always (n - 2) / 2 + n % 2. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        int ans = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        if(k == 1){
            cout << ((n - 2) / 2 + n % 2) << "\n";
            continue;
        }
        for(int i = 1; i < n - 1; i++){
            if(a[i] > a[i - 1] + a[i + 1]) {
                ans ++;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
