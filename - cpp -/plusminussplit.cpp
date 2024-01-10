#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1919B

//note that at worst, we can have a penalty of n by just grouping each element individually. 

//to decrease our penalty, we must group subarrays of absolute sum 0. I claim that the optimal penalty
//is equal to the absolute value of the sum of the entire array. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        int sum = 0;
        for(int i = 0; i < n; i++){
            sum += s[i] == '+'? 1 : -1;
        }
        cout << abs(sum) << "\n";
    }
    
    return 0;
}
