#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1844B

//if n = 1, then return 1
//if n = 2, then return 1 2

//otherwise, n >= 3. 
//note that since all primes are greater than 1, we probably want 1 to be in the most subarrays, thus we want 
//it to be in the center of the permutation. Any subarray that doesn't contain 1 cannot contribute to the primality value. 

//similar but opposite reasoning for putting 2 and 3 at opposite ends of the permutation; as long as the permutation contains
//1 and not both 2 and 3, then it is contributing to the primality. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        if(n == 1){
            cout << "1\n";
            continue;
        }
        if(n == 2){
            cout << "1 2\n";
            continue;
        }
        vector<int> ans(n, -1);
        ans[0] = 2;
        ans[n - 1] = 3;
        ans[n / 2] = 1;
        int ptr = 4;
        for(int i = 0; i < n; i++){
            if(ans[i] != -1){
                continue;
            }
            ans[i] = ptr ++;
        }
        for(int i = 0; i < n; i++){
            cout << ans[i] << " \n"[i == n - 1];
        }
    }
    
    return 0;
}
