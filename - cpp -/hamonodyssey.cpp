#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1847B

//if the and sum of all the numbers is greater than 0, then taking more than 1 segment will always increase the sum. 

//else, greedily partition the array into segments of and sum = 0. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        int ans = 0;
        int sum = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        for(int i = 0; i < n; i++){
            if(sum == 0){
                ans ++;
                sum = a[i];
            }
            sum &= a[i];
        }
        if(sum != 0 && ans > 1){
            ans --;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
