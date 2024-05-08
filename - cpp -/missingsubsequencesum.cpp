#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1965B

//powers of 2 or smth until you reach k - 1. Then patch in the holes. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<int> ans(0);
        int sum = 0;
        int pow2 = 1;
        while(sum != k - 1){
            int diff = k - 1 - sum;
            if(pow2 <= diff) {
                ans.push_back(pow2);
                sum += pow2;
                pow2 *= 2;
                continue;
            }
            else {
                ans.push_back(diff);
                sum += diff;
            }
        }
        sum += k + 1;
        ans.push_back(k + 1);
        if(k == 1){
            sum += k + 2;
            ans.push_back(k + 2);
        }
        while(sum - k <= n){
            int next = sum - k;
            if(next == k){
                next = sum;
            }
            ans.push_back(next);
            sum += next;
        }
        cout << ans.size() << "\n";
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
