#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1543 D1, D2

//easy version:
//for the easy version we are dealing with normal bitwise xor, so x ^ z = y can be turned into x ^ y = z. 
//then, we can just try all numbers from 0 to n - 1 in order starting from 0. So, when we try y = 0, x := x ^ 0
//then, y = 1 will do x := x ^ 1. The problem happens when we test if x was initially 2, since if x was initially
//2, then x would be 3 at this point. We can account for this though, and test y = 3. 

//in general, we can always account for our previous queries by xoring them into y before we query. 

//hard version:
//for the hard version, we cannot transform x ^ z = y into x ^ y = z because x ^ x = 0 does not always hold for k != 2. 
//so instead we get inv(x) ^ y = z, where x ^ inv(x) = 0. 

//The idea of testing each possible value of initial x, and accounting for the previous queries still works here, but 
//accounting for the previous queries is now more involved. 
    
int inverse(int a, int k) {
    int p = 1;
    int ans = 0;
    while(a != 0){
        int d = a % k;
        a /= k;
        d = (k - d) % k;
        ans += d * p;
        p *= k;
    }
    return ans;
}
    
int _xor(int a, int b, int k) {
    int ans = 0;
    int p = 1;
    while(a != 0 || b != 0){
        int da = a % k;
        int db = b % k;
        a /= k;
        b /= k;
        ans += ((da + db) % k) * p;
        p *= k;
    }
    return ans;
}
    
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<int> e(n, 0);
        int e_pfx = 0;
        for(int i = 0; i < n; i++){
            if(i % 2 == 1){
                e[i] = _xor(e_pfx, inverse(i, k), k);
            }
            else {
                e[i] = _xor(e_pfx, i, k);
            }
            cout << e[i] << endl;
            int r;
            cin >> r;
            if(r == 1){
                break;
            }
            e_pfx = inverse(e_pfx, k);
            e_pfx = _xor(e_pfx, e[i], k);
        }
    }
    
    return 0;
}