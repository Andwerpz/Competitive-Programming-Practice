#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1973D

//first, note that m must be a multiple of the maximum element of the array, mx. Second, m cannot be greater than
//mx * n, as f(1, n) = mx * n. 

//so first, we can try to find mx. If we query l = 1, and x = n, 2n, 3n, and so on, the first time they return r = n 
//is when we've found the maximum, mx = x / n. So, we can find the maximum in n queries. 

//Now that we have the maximum, we can try values of m. Given a value of m, we can test if it works in k queries, 
//but we only have n queries left, and this requires n * k queries. 

//but here, we can make another observation. If m = i * mx, then the subarray sizes will be at least i. Since we 
//are required to split the array into k subarrays, k * i <= n, or i <= n / k. Since there are only n / k valid
//values of m, and for each we need to use k queries to verify, this works out to be perfectly n queries required. 

//therefore, we can just use k queries to check each of the n / k valid values of m. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        //first, find maximum element
        int mx;
        for(int i = 1; i <= n; i++){
            cout << "? 1 " << i * n << endl;
            int r;
            cin >> r;
            if(r == n) {
                mx = i;
                break;
            }
        }
        //next, compute minimum m. 
        int ans = -1;
        for(int i = 1; i <= n / k; i++){
            int m = i * mx;
            int ptr = 1;
            bool is_valid = true;
            for(int j = 0; j < k; j++){
                if(ptr >= n + 1){
                    is_valid = false;
                    break;
                }
                cout << "? " << ptr << " " << m << endl;
                cin >> ptr;
                ptr ++;
            }
            if(ptr != n + 1){
                is_valid = false;
            }
            if(is_valid){
                ans = m;
                break;
            }
        }
        int tmp;
        cout << "! " << ans << endl;
        cin >> tmp;
    }
    
    return 0;
}
