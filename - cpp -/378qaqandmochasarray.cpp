#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1975B

//x can only divide y if x <= y. Therefore, the first number we should choose is the smallest number in the array. 
//as for the second number, it should be the smallest number that cannot be divided by the first number. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        int x1 = a[0];
        int x2 = -1;
        bool is_valid = true;
        for(int i = 0; i < n; i++){
            if(a[i] % x1 == 0){
                continue;
            }
            else {
                if(x2 == -1){
                    x2 = a[i];
                }
                if(a[i] % x2 == 0){
                    continue;
                }
                else {
                    is_valid = false;
                }
            }
        }
        cout << (is_valid? "Yes" : "No") << "\n";
    }
    
    return 0;
}