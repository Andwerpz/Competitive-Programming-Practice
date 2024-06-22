#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1508B

//so for an almost sorted permutation, each successive element can either 
//1. increase
//2. decrease by exactly 1

//we can use a binary string to describe some almost sorted permutation, with 0 meaning that we've increased, and
//1 meaning we've decreased by exactly one. For example:

// 0 1 1 0 1
//1 4 3 2 6 5

//I claim that for a given binary string of length n - 1, there is only one corresponding almost sorted permutation of
//length n. 

//Let's denote the value of some permutation as the decimal value of it's binary string representation. My second claim is 
//that if permutation A has less value than permutation B, then A is lexicographically less than B. 

//this second fact actually makes this problem really easy to solve. The binary representation of the permutation
//we want is just the binary representation of k - 1. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, k;
        cin >> n >> k;
        k --;
        if(n <= 60) {
            ll pcnt = 1;
            for(int i = 0; i < n - 1; i++){
                pcnt *= 2;
            }
            if(k >= pcnt) {
                cout << "-1\n";
                continue;
            }
        }
        vector<int> ans(n);
        for(int i = 0; i < n; i++){
            ans[i] = i + 1;
        }
        vector<bool> bits(n - 1, false);
        for(int i = 0; i < min(60ll, n - 1); i++){
            bits[i] = k & (1ll << (ll) i);
        }
        reverse(bits.begin(), bits.end());
        for(int i = 0; i < n - 1;) {
            if(!bits[i]) {
                i ++;
                continue;
            }
            int r = i;
            while(r != n - 1 && bits[r]) {
                r ++;
            }
            r ++;
            reverse(ans.begin() + i, ans.begin() + r);
            i = r;
        }
        for(int i = 0; i < n; i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}