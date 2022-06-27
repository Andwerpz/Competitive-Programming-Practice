#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1686B

//a subarray is odd if it only has one inversion. 

//greedily split the array into minimal sized subarrays that only have one inversion. 

//minimal sized, since if a subarray only has one inversion, then decreasing it's size won't increase
//the number of inversions. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        int ans = 0;
        int max = -1e9;
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            if(next < max){
                max = -1e9;
                ans ++;
            }
            else{
                max = std::max(max, next);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
