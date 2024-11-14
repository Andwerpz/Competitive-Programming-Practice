#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 2035C

//for n <= 7, just hardcode. 

//for n >= 8, there are two cases:
//n is even: k can be 2^p - 1 where 2^p is the smallest power of 2 greater than n. 
//n is odd: k is n. 

//solving the even case will automatically get us the odd case, as we can just put in n as
//the last element in the array. 

//to solve the even case, we can just have 1, 3, 2^(p - 1) - 2, 2^(p - 1) - 1, 2^(p - 1) 
//as the last 5 elements in the array. This guarantees that no matter what value k has before, 
//k will have value 2^p - 1 at the end. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        if(n == 5){
            cout << "5\n" << "2 1 3 4 5\n";
            continue;
        }
        if(n == 6){
            cout << "7\n" << "1 2 4 6 5 3\n";
            continue;
        }
        if(n == 7){
            cout << "7\n" << "2 4 5 1 3 6 7\n";
            continue;
        }
        bool is_odd = false;
        if(n % 2 == 1){
            is_odd = true;
            n --;
        }
        int mxpow2 = 1;
        while(mxpow2 * 2 <= n){
            mxpow2 *= 2;
        }
        // cout << "MXPOW : " << mxpow2 << "\n";
        vb v(n + 1, false);
        vi ans(n, -1);
        ans[n - 1] = mxpow2;
        ans[n - 2] = mxpow2 - 1;
        ans[n - 3] = mxpow2 - 2;
        ans[n - 4] = 3;
        ans[n - 5] = 1;
        int ptr = 1;
        for(int i = 0; i < ans.size(); i++){
            if(ans[i] != -1){
                continue;
            }
            while(ptr == 1 || ptr == 3 || ptr == mxpow2 || ptr == mxpow2 - 1 || ptr == mxpow2 - 2){
                ptr ++;
            }
            ans[i] = ptr;
            ptr ++;
        }
        int sum = mxpow2 + mxpow2 - 1;
        if(is_odd) {
            sum = n + 1;
            ans.push_back(n + 1);
            n ++;
        }
        cout << sum << "\n";
        for(int i = 0; i < n; i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}